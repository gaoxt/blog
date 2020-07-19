# name
nginx+varnish负载均衡和静态缓存测试

# description
varnish作为前端，转发到2台nginx，建立round_robin的负载均衡，通过健康检查自动切换。测试了单点故障、缓存手动清除的情况。 

# using
启动
```c 
docker-compose up -d
```
访问 http://localhost:8080 可以看到第一次response header中含有
```c
X-Cache: MISS from 172.21.0.4
```
再次请求变，发现已经命中在varnish内存中的缓存了。
```c
X-Cache: HIT via 172.21.0.4
```

暂停nginx1的服务，清空varnish的缓存，再次访问，发现已经成功切换到nginx2了。
```c
docker pause nginx1
curl -X PURGE http://localhost:8080/
```