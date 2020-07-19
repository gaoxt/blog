# name
redis-cluster单机多节点集群环境

# description
使用了5个master，每个master配1个slave。
redis5版本开始自带类似redis-trib.rb的自动工具，包含了节点通信、分配槽、手动的进行主从复制等工作。

# using
启动
```c 
docker-compose up -d
```

查看集群信息和节点状态
```c
docker exec redis_cluster_redis-cluster_1 redis-cli -c -p 7000 cluster info
docker exec redis_cluster_redis-cluster_1 redis-cli -c -p 7000 cluster nodes
```

查看数据分片槽分布情况
```c
docker exec redis_cluster_redis-cluster_1 redis-cli --cluster check 127.0.0.1:7000
```

# References
https://github.com/Grokzen/docker-redis-cluster