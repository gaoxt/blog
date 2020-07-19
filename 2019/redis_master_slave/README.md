# name
redis主从环境

# description
master不需要配置，slave服务器使用 --slaveof 指定master的ip和端口即可，从库一般是只读权限。

# using
启动
```c 
docker-compose up
```
另起终端，查看master的connected_slaves连接数。
```c
docker exec redis_master_slave_master_1 redis-cli info Replication   
```

在master设置一个name值，在slave查询到即可。
```c
docker exec -it redis_master_slave_master_1 redis-cli set name gaoxt
docker exec -it redis_master_slave_slave_1 redis-cli get name
```