# name
swoole项目开发环境搭建

# description


## trunk主线
```
gateway_server:962 
game_server:9620
```

启动容器，从10.10.4.204:5000/dragonica_simple构建
```
docker run -it --name trunk -d \
-p 8080:80 -p 8086:8086 -p 8087:8087 -p 9505:9505 -p 9506:9506 -p 9508:9508 \
-e GATEWAY_ID='962' \
-e GAME_ID='9620' \
-v /data/dream/menghuan/trunk:/data/dragonica 10.10.4.204:5000/dragonica_simple bash 
```

正常启动流程
```
sh start.sh 
sh start_arena.sh 
```

检查gateway、game、arena是否有起来

```
ps aux | grep php
ps aux | grep arena
```