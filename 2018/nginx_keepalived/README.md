# name
haproxy+nginx/keepalive主从环境

# description
实现：双机热备(故障切换)，VIP漂移(故障移回)，测试了单点故障的情况。

# using

启动后访问 http://localhost:6301

```c 
docker-compose up -d
```
测试单机故障，ps查看容器名称
```c
docker ps 
```
停止master，访问 http://localhost:6301 发现变为slave

```c
docker stop nginx_keepalived_nginx_master_1
```

再次启动master，发现变为了主机。
```c
docker start nginx_keepalived_nginx_master_1
```