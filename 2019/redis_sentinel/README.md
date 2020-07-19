# name
redis多哨兵多主从环境

# description
1个master+2个slave+3个sentinel的docker测试环境，验证了单节点的故障手动移回和故障自动切换。
相比主从模式减少了人工干预自动切换主服务器。


# using
启动，对sentinel数量和slave数量进行水平扩展
```c 
docker-compose up -d --scale sentinel=3 --scale slave=2
```

查看master和slave的IP，我这分别为172.31.0.2和172.31.0.3
```c
docker inspect -f '{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' redis_sentinel_master_1
docker inspect -f '{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' redis_sentinel_slave_1
```

查看哨兵信息，显示master为172.31.0.2
```c
docker exec redis_sentinel_sentinel_1 redis-cli -p 26379 info Sentinel
docker exec redis_sentinel_sentinel_1 redis-cli -p 26379 SENTINEL get-master-addr-by-name mymaster
```

测试，停止master，等待5秒，检查slave是否切换为master，检查slave的role等级变成了master。
```c
docker pause redis_sentinel_master_1
docker exec redis_sentinel_sentinel_1 redis-cli -p 26379 info Sentinel
docker exec redis_sentinel_sentinel_1 redis-cli -p 26379 SENTINEL get-master-addr-by-name mymaster
docker exec redis_sentinel_slave_1 redis-cli info Replication
```

因为没开优先级，master降级为slave了，手动进行切换为master，检查是否故障恢复。
```c
docker unpause redis_sentinel_master_1
docker exec redis_sentinel_sentinel_1 redis-cli -p 26379 SENTINEL failover mymaster
docker exec redis_sentinel_sentinel_1 redis-cli -p 26379 info Sentinel
docker exec redis_sentinel_sentinel_1 redis-cli -p 26379 SENTINEL get-master-addr-by-name mymaster
```


# References
https://github.com/AliyunContainerService/redis-cluster