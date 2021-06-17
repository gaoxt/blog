#!/usr/bin/env sh
set -e
php-fpm -D
redis-server /usr/local/etc/redis/redis.conf &
nginx -g 'daemon off;'