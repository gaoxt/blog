<?php
/*
    后期静态绑定 之 转发调用和非转发 的Example
    Reference：https://www.kancloud.cn/martist/ma_zhao_liu/460380
*/

class A
{
    public static function foo()
    {
        static::who();
    }

    public static function who()
    {
        echo __CLASS__ . "\n";
    }
}

class B extends A
{
    public static function test()
    {
        //指定调用A的静态函数
        A::foo();
        //父级为A，A中的static运行计算到最高优先级为C(最后定义覆盖前面的)。
        parent::foo();
        //和上面一样，走到A的foo，static运行计算调用C的who，因为C重写了who方法。
        self::foo();
    }

    public static function who()
    {
        echo __CLASS__ . "\n";
    }
}
class C extends B
{
    public static function who()
    {
        echo __CLASS__ . "\n";
    }
}

C::test();
