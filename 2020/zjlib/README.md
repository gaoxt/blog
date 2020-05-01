# name
浙图入馆预约脚本

# Description
因疫情原因每日三点需要预约才能进入,抓取接口提供方便需要的基友参考.


# using

需要修改的个人信息
```
data = {
    'name': 'your name',  #姓名
    'rdid': 'your IDcard', #身份证号
    'mobile': 'your mobile', #手机号
    'openid': 'your weixin_with_zjlib_openid', #需要charles抓包,浙江图书馆公众号openid
}
```

本脚本托管在Ubuntu服务器,通过supervisord进行管理,crontab定时运行,附上相关配置,懒得搭建的同学也可以本地运行.

   crontab配置
```
/etc/cron.d/zjlib-super

#每天14点55分开启(排除周一闭馆)
55 14 * * 1-6 root /usr/local/bin/supervisorctl restart python-zjlib 
```

   supervisord配置
```
/etc/supervisor/zjlib.conf

[program:python-zjlib]
command=python3 -u /root/zjlib.py
environment=PYTHONIOENCODING=utf-8
autostart=false
autorestart=false
stdout_logfile=/etc/supervisor/logs/python-zjlib.log
stderr_logfile=/etc/supervisor/logs/python-zjlib.error.log
```