# name
redis-cluster多机主从水平扩容集群环境

# description
每个node下会自动启动2个以上的redis，端口分别是7000和7001，集群分片时做master/slave。测试了新增节点、减少节点、重写分片插槽的功能。

# using
## 初始化集群
初始化集群节点，cluster建议3个以上。
```c 
docker-compose up --build --scale node=5
```

需要手动创建cluster，通过init_cluster工具生成代码，手动运行，来遍历IP。
```c
chmox +x init_cluster.sh
./init_cluster.sh
```

查看集群信息和节点状态
```c
docker exec redis_cluster_scale_node_1 redis-cli -p 7000 cluster info
docker exec redis_cluster_scale_node_1 redis-cli -p 7000 cluster nodes
docker exec redis_cluster_scale_node_1 redis-cli -p 7000 cluster nodes
```

查看数据分片槽分布情况
```c
docker exec redis_cluster_scale_node_1 redis-cli --cluster check 127.0.0.1:7000
```

## 新增和删除slave节点
查询slave节点ID，删除slave节点，清空集群缓存，再新增为集群的slave。
```c
docker exec redis_cluster_scale_node_1 redis-cli -p 7000 cluster nodes | grep slave
docker exec redis_cluster_scale_node_1 redis-cli --cluster del-node 127.0.0.1:7000 '4dbd472eb25caf63fb67617f4271827f06f9964d'
docker exec redis_cluster_scale_node_5 sh -c "rm -rf /redis-data/7001/*"
docker exec redis_cluster_scale_node_5 redis-server /redis-conf/7001/redis.conf
docker exec redis_cluster_scale_node_1 redis-cli --cluster add-node 192.168.96.5:7001 127.0.0.1:7000 --cluster-slave
```
## 新增和删除master节点
查询master节点ID，转移分片插槽，删除节点，再新增回去，分配插槽。
```c
docker exec -it redis_cluster_scale_node_5 sh 
redis-cli -p 7000 cluster nodes | grep myself       //node_5_id 9c9e14c80f5d64f5c0ba29523a161563acc3980f

redis-cli --cluster reshard 127.0.0.1:7000
How many slots do you want to move (from 1 to 16384)? 3274                  //slots: (3274 slots) 
What is the receiving node ID? 1a40a306bde5c80d76c83c6d794b96bca26ecde8     //node_1_id
Source node #1:9c9e14c80f5d64f5c0ba29523a161563acc3980f                     //node_5_id
Source node #2:done
Do you want to proceed with the proposed reshard plan (yes/no)? yes
redis-cli --cluster del-node 127.0.0.1:7000 9c9e14c80f5d64f5c0ba29523a161563acc3980f
```

新增回去
```c
rm -rf "/redis-data/7000/*"
redis-server /redis-conf/7000/redis.conf
redis-cli --cluster add-node 127.0.0.1:7000 127.0.0.1:7001
redis-cli --cluster reshard 127.0.0.1:7000
How many slots do you want to move (from 1 to 16384)? 3274                  //slots: (3274 slots) 
What is the receiving node ID? 9d31724f0846d80e2c1f13f1ef53d21cc85fb114     //new node_5_id
Source node #1:1a40a306bde5c80d76c83c6d794b96bca26ecde8                     //node_1_id
Source node #2:done
Do you want to proceed with the proposed reshard plan (yes/no)? yes  
```

检查插槽
```c
redis-cli --cluster check 127.0.0.1:7000  
```



# References
https://github.com/Grokzen/docker-redis-cluster