# name
tp3和tp5性能分析xdebug环境

# description
nginx1.12 + php56 的 一套环境，用于tp3和tp5的性能分析，


# using
修改：
1. docker-composer.yml 挂载的 tp3和tp5 目录
2. php56/php.ini 的 remote_host 改为本机ip。



```c
docker-compose up -d
```

启动后，访问web
 * http://localhost:8005 为 tp5 目录
 * http://localhost:8003 为 tp3 目录