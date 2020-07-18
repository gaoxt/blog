# name 
主nginx反向代理到多台从nginx进行负载均衡

# description
master nginx 分发请求到 nginx_1 和 nginx_2
过程中停止nginx_1等待片刻发现请求页面为nginx_2

# using

启动后，访问 http://localhost:7001
```c 
docker-compose up -d
```

ps查看容器名称后 停止nginx_1进行测试访问网页。
```c
docker ps 
docker stop nginx_1
```
