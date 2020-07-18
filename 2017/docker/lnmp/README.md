# name
lnmp的docker-compose的基本环境

# description
nginx1.12 + mysql5.6 + php56 

其中环境变量通过 local.env 文件加载进 docker容器中，再通过php56/www.conf 配置 include<local.env>到php-fpm中，所以php中的 $_SERVER 全局变量能获取得到。

php56已经安装了xdebug扩展，php.ini里xdebug.remote_host需要修改为自己的主机ip，需要增加就修改 php56/Dockerfile

# using
避免80端口被占用，如有占用需要修改docker-compose.yml

启动后，稍等mysql初始化完，访问 http://localhost

```c 
docker-compose up -d
```