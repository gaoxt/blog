<?php
/**
 * Desc:
 * User: gaoxi
 * Date: 2021-01-14
 */

namespace App\CommonTcp;

use App\Protocal as protocal;
use Xhgui\Profiler\Profiler;
use Xhgui\Profiler\ProfilerFactory;
use Xhgui\Profiler\ProfilingData;
use Xhgui\Profiler\ProfilingFlags;
use Xhgui\Profiler\SaverFactory;
use Xhgui\Profiler\Exception\ProfilerException;

class ProfilerOverride extends Profiler
{
    private $profiler;
    private $running;
    private $config;
    private $saveHandler;
    private $flush;

    public $messageId;
    public $userId;

    static public $filterMessageNames = array(
        "System/Sync",
        "Battle/PveMapStep",
    );

    static public $filterData = array(
        'Xhgui\Profiler',
        'Google\Protobuf',
        'Composer\\',
        'GPBMetadata\\',
    );

    public static $instance = null;

    public function __construct()
    {
    }
    
    static public function getInstance(protocal\GameMsg $gameMsg)
    {
        if(IS_DEV === false || !extension_loaded('tideways_xhprof') || !extension_loaded('mongodb')){
            return new ProfilerOverride();
        }
        $profilerConfig = array(
            'save.handler' => Profiler::SAVER_MONGODB,
            'save.handler.mongodb' => array(
                'dsn' => 'mongodb://10.10.4.204:27017',
                'database' => 'tideways_xhprof',
                ),
            'profiler.exclude-env' => array(
                "GPG_KEYS",
                "PHP_SHA256"
            ),
        );
        if(is_null(self::$instance)){
            self::$instance = new ProfilerOverride();
            self::$instance->config = array_replace(self::$instance->getDefaultConfig(), $profilerConfig);
        }
        $messageId = $gameMsg->getMessageId();
        $userId = $gameMsg->getUserId();

        self::$instance->messageId = $messageId;
        self::$instance->userId = $userId;
        self::$instance->config['profiler.replace_url'] = function ($url) use ($messageId){
            $newUrl = $url;
            if(strpos($url,'game_server') !== false){
                $newUrl = $GLOBALS['for_client_game_function_list'][$messageId];
            }
            return $newUrl;
        };
        return self::$instance;
    }


    /**
     * Evaluate profiler.enable condition, and start profiling if that returned true.
     */
    public function start($flush = true)
    {
        if(!$this->checkMessageId()){
            return;
        }

        if (!$this->shouldRun()) {
            return;
        }

        $this->enable();

        $this->flush = $flush;
        // shutdown handler collects and stores the data.
        $this->registerShutdownHandler();
    }

    /**
     * Stop profiling. Get currently collected data and save it
     */
    public function stop()
    {
        if(!$this->checkMessageId()){
            return;
        }
        
        $data = $this->disable();
        $this->save($data);

        return $data;
    }

    /**
     * Enables profiling for the current request / CLI execution
     */
    public function enable($flags = null, $options = null)
    {
        $this->running = false;

        // 'REQUEST_TIME_FLOAT' isn't available before 5.4.0
        // https://www.php.net/manual/en/reserved.variables.server.php
        $_SERVER['REQUEST_TIME_FLOAT'] = microtime(true);

        $profiler = $this->getProfiler();
        if (!$profiler) {
            throw new ProfilerException('Unable to create profiler: No suitable profiler found');
        }

        $saver = $this->getSaver();
        if (!$saver) {
            throw new ProfilerException('Unable to create saver');
        }

        if ($flags === null) {
            $flags = $this->config['profiler.flags'];
        }
        if ($options === null) {
            $options = $this->config['profiler.options'];
        }

        $profiler->enable($flags, $options);
        $this->running = true;
    }

    /**
     * Stop profiling. Return currently collected data
     *
     * @return array
     */
    public function disable()
    {
        if (!$this->running) {
            return array();
        }

        $profiler = $this->getProfiler();
        if (!$profiler) {
            // error for unable to create profiler already thrown in enable() method
            // but this can also happen if methods are called out of sync
            throw new ProfilerException('Unable to create profiler: No suitable profiler found');
        }

        $profile = new ProfilingData($this->config);
        $this->running = false;

        return $this->replaceData($profile->getProfilingData($this->filterData($profiler->disable())));
    }

    /**
     * Saves collected profiling data
     *
     * @param array $data
     */
    public function save(array $data = array())
    {
        if (!$data) {
            return;
        }

        $saver = $this->getSaver();
        if (!$saver) {
            // error for unable to create saver already thrown in enable() method
            // but this can also happen if methods are called out of sync
            throw new ProfilerException('Unable to create profiler: Unable to create saver');
        }

        $saver->save($data);
    }

    /**
     * Tells, if profiler is running or not
     *
     * @return bool
     */
    public function isRunning()
    {
        return $this->running;
    }

    /**
     * Returns value of `profiler.enable` function evaluation
     *
     * @return bool
     */
    private function shouldRun()
    {
        $closure = $this->config['profiler.enable'];

        return is_callable($closure) ? $closure() : false;
    }

    /**
     * Calls register_shutdown_function .
     * Registers this class' shutDown method as the shutdown handler
     *
     * @see Profiler::shutDown
     */
    private function registerShutdownHandler()
    {
        // do not register shutdown function if the profiler isn't running
        if (!$this->running) {
            return;
        }

        register_shutdown_function(array($this, 'shutDown'));
    }

    /**
     * @internal
     */
    public function shutDown()
    {
        if ($this->flush) {
            $this->flush();
        }

        try {
            $this->stop();
        } catch (ProfilerException $e) {
            return;
        }
    }

    private function flush()
    {
        // ignore_user_abort(true) allows your PHP script to continue executing, even if the user has terminated their request.
        // Further Reading: http://blog.preinheimer.com/index.php?/archives/248-When-does-a-user-abort.html
        // flush() asks PHP to send any data remaining in the output buffers. This is normally done when the script completes, but
        // since we're delaying that a bit by dealing with the xhprof stuff, we'll do it now to avoid making the user wait.
        ignore_user_abort(true);

        if (function_exists('session_write_close')) {
            session_write_close();
        }

        flush();

        if (function_exists('fastcgi_finish_request')) {
            fastcgi_finish_request();
        }
    }

    /**
     * @return ProfilerInterface|null
     */
    private function getProfiler()
    {
        if ($this->profiler === null) {
            $this->profiler = ProfilerFactory::create($this->config) ?: false;
        }

        return $this->profiler ?: null;
    }

    /**
     * @return SaverInterface|null
     */
    private function getSaver()
    {
        if ($this->saveHandler === null) {
            $this->saveHandler = SaverFactory::create($this->config['save.handler'], $this->config) ?: false;
        }

        return $this->saveHandler ?: null;
    }

     /**
     * @return array
     */
    private function getDefaultConfig()
    {
        return array(
            'save.handler' => Profiler::SAVER_STACK,
            'save.handler.stack' => array(
                'savers' => array(
                    Profiler::SAVER_UPLOAD,
                    Profiler::SAVER_FILE,
                ),
                'saveAll' => false,
            ),
            'save.handler.file' => array(
                'filename' => sys_get_temp_dir() . '/xhgui.data.jsonl',
            ),
            'profiler.enable' => function () {
                return true;
            },
            'profiler.flags' => array(
                ProfilingFlags::CPU,
                ProfilingFlags::MEMORY,
                ProfilingFlags::NO_BUILTINS,
                ProfilingFlags::NO_SPANS,
            ),
            'profiler.options' => array(),
            'profiler.exclude-env' => array(),
            'profiler.simple_url' => function ($url) {
                return preg_replace('/=\d+/', '', $url);
            },
            'profiler.replace_url' => null,
        );
    }


    public function checkMessageId()
    {
        if(IS_DEV === false || !extension_loaded('tideways_xhprof')){
            return false;
        }

        if (!array_key_exists($this->messageId, $GLOBALS['for_client_game_function_list'])) {
            return false;
        }
        
        foreach(self::$filterMessageNames as $messageName){
            if(strpos($GLOBALS['for_client_game_function_list'][$this->messageId],$messageName) !== false){
                return false;
            }
        }
        
        return true;
    }

    private function filterData($data)
    {
        foreach(self::$filterData as $filter){
            foreach($data as $index=>$nothing){
                if(strpos($index,$filter) !== false){
                    unset($data[$index]);
                }
            }
        }
        return $data;
    }

    private function replaceData($data)
    {
        $data['_id'] = new \MongoId();
        $env_arr = array(
            "IS_DEV"=>IS_DEV,
            "SERVER_NAME"=>SERVER_NAME,
            "GAME_PREFIX"=>GAME_PREFIX,
            "GAME_DB_NAME"=>GAME_DB_NAME,
            "GAME_LOG_DB_NAME"=>GAME_LOG_DB_NAME,
            "REMOTE_ADDR"=>SELF_IP,
            "REQUEST_METHOD"=>'Proto',
            "ROOT"=>ROOT,
            "SERVER_PATH"=>SERVER_PATH,
            "ROOT_PATH"=>ROOT_PATH,
            "GAME_PATH"=>GAME_PATH,
            "REQUEST_TIME"=>time(),
        );
        if(isset($data['meta'])){
            $data['meta']['get'] = array($this->userId,$this->messageId);
            $data['meta']['userId'] = $this->userId;
            foreach($env_arr as $key=>$val){
                $data['meta']['SERVER'][$key] = $val;
                $data['meta']['env'][$key] = $val;
            }
        }

        return $data;
    }
}