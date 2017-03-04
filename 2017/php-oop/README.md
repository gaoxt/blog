# name
理解php中的控制反转IOC、依赖注入DI、容器和后期静态绑定

# description
[xdebug分析php中的控制反转IOC、依赖注入DI、容器和后期静态绑定](https://blog.csdn.net/qq624202120/article/details/58593187)


```c
├── 1old.php        #传统OOP
├── 2DI.php         #依赖注入思想体现
├── 3DIC.php        #依赖注入通过容器管理
├── 4IOC.php        #简单的IOC容器
├── 5IOC_more.php   #IOC的自动绑定绑定实现
├── 6static.php     #后期静态绑定理解
├── Dockerfile      #xdebug测试环境
├── profiler        #profiler分析文件存放
└── README.md
```

# using

1.打包php配置，扩展等
```c
docker build -t php7-prf .
```

2.启动php7-prf容器(需要php-oop的绝对路径)
```c
docker run --name php7-prf -v /php-oop:/tmp php7-prf
```

3.运行xdebug的profiler分析
```c
docker exec php7-prf php -d xdebug.profiler_enable=On /tmp/1old.php
```

4.通过webgrind分析profiler文件。
```c 
docker run --rm -v /php-oop/profiler:/tmp -p 80:80 jokkedk/webgrind:latest
```

5.需要vscode调试请参考:[xdebug 远程调试代码 和 代码性能分析](https://blog.csdn.net/qq624202120/article/details/64124087) 的配置
修改Dockerfile，重新build，开启vscode监听，直接运行即可。
```c
docker exec php7-prf php /tmp/1old.php
```
