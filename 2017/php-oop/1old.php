<?php
//传统OOP写法，Foo的doSomething包含对Bar的依赖，Bar也同样依赖Bim。

class Bim
{
    public function doSomething()
    {
        echo __METHOD__, '|';
    }
}

class Bar
{
    public function doSomething()
    {
        $bim = new Bim();
        $bim->doSomething();
        echo __METHOD__, '|';
    }
}

class Foo
{
    public function doSomething()
    {
        $bar = new Bar();
        $bar->doSomething();
        echo __METHOD__;
    }
}
$foo = new Foo();
$foo->doSomething();
