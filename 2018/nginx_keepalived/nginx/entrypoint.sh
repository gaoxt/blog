#!/bin/sh
#清楚残留的keepalive.pid、vrrp.pid等，不然启动会daemon is already running，无法实现故障移回，坑，找了我一个下午。
rm -rf /var/run/*
/usr/sbin/keepalived -n -l -D -f /etc/keepalived/keepalived.conf --dont-fork --log-console -P &
nginx -g "daemon off;"  