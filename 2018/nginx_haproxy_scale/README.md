# name
使用scale对nginx进行水平扩容

# description
haproxy作为网关入口，分发请求到nginx，nginx通过docker-compose的scale进行扩容为2台，测试了双机热备(故障切换)、单点故障的情况。

# using
启动后访问 http://localhost:6301

```c 
docker-compose up --scale web=2
```

测试单机故障，ps查看容器名称
```c
docker ps 
```
停止web_1，访问 http://localhost:6301 发现能正常访问，查看日志是访问的web_2

```c
docker stop nginx_haproxy_scale_web_1
```

再次启动web_1，停止web_2，发现日志变成了访问web_1。
```c
docker start nginx_haproxy_scale_web_1
docker stop nginx_haproxy_scale_web_2
```