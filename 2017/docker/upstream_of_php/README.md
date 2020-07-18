# name 
单机nginx负载均衡到多台php-fpm的环境

# description
nginx 分发请求到 php56_1 和 php56_2
过程中停止php56_1发现请求正常，然后启动php56_1，再次停止php56_2，发现服务正常。

# using
启动后，访问 http://localhost:7001
```c 
docker-compose up -d
```

ps查看容器名称后 停止php56_1进行测试访问网页。
```c
docker ps 
docker stop php56_1
```
