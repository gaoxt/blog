# name
k8s+lnmp环境本地部署


# Description
[k8s搭建一个lnmp本地环境的完整过程](https://blog.csdn.net/qq624202120/article/details/107587306)
```c
.
├── kustomization.yaml      #整合多套生产、开发的yaml文件方便管理。
├── local-storage.yaml	    #通过hostPath创建PV和PVC
├── local_storage			
│   ├── mysql			    #数据持久化目录
│   └── wordpress		    #应用代码持久化目录
├── mysql-deployment.yaml   #mysql的svc和Deployment管理的pod
├── nginx-deployment.yaml   #与上类似，多了ConfigMap管理配置和LoadBalancer直接暴露IP。
├── php-deployment.yaml		#与上类似
└── php-fpm					
    └── Dockerfile			#装了mysql扩展的php镜像
```

# Usage

生成带mysql扩展的php镜像，提供给k8s使用。
```c
docker build -t k8s-php7-fpm php-fpm/.
```

运行kustomization.yaml文件即可。
```c
kubectl apply -k .    
```

访问
http://localhost 
