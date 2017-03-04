<?php
/*
    
    dependency injection container(依赖注入容器)
    不必自己在代码中维护对象的依赖
    容器自动根据配置，将依赖注入指定对象

    容器负责实例化，注入依赖，处理依赖关系等工作。
    管理对象的生成、资源取得、销毁等生命周期
    建立对象与对象之间的依赖关系
    启动容器后，所有对象直接取用，不用编写任何一行代码来产生对象，或是建立对象之间的依赖关系。

*/


class Bim
{
    public function doSomething()
    {
        echo __METHOD__, '|';
    }
}

class Bar
{
    private $bim;

    public function __construct(Bim $bim)
    {
        $this->bim = $bim;
    }

    public function doSomething()
    {
        $this->bim->doSomething();
        echo __METHOD__, '|';
    }
}

class Foo
{
    private $bar;

    public function __construct(Bar $bar)
    {
        $this->bar = $bar;
    }

    public function doSomething()
    {
        $this->bar->doSomething();
        echo __METHOD__;
    }
}

class Container
{
    private $s = array();

    /*
    魔术方法
    在给不可访问属性赋值时，__set() 会被调用。
    读取不可访问属性的值时，__get() 会被调用。
    */
    function __set($k, $c)
    {
        $this->s[$k] = $c;
    }

    function __get($k)
    {
        //执行函数$this->s[$k]，传入$this。
        return $this->s[$k]($this);
    }
}

$c = new Container();

//匿名函数
$c->bim = function () {
    return new Bim();
};
$c->bar = function ($c) {
    return new Bar($c->bim);
};
$c->foo = function ($c) {
    return new Foo($c->bar);
};

// 从容器中取得Foo
$foo = $c->foo;
$foo->doSomething(); // Bim::doSomething|Bar::doSomething|Foo::doSomething