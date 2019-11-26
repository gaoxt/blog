#!/bin/sh
if [ -z "$INITIAL_PORT" ]; then # Default to port 7000
    INITIAL_PORT=7000
fi

if [ -z "$SLAVES_PER_MASTER" ]; then # Default to 1 SLAVES_PER_MASTER
    SLAVES_PER_MASTER=1
fi
max_port=$(($INITIAL_PORT + 1 * ( $SLAVES_PER_MASTER  + 1 ) - 1))
for port in $(seq $INITIAL_PORT $max_port); do
    mkdir -p /redis-conf/${port}
    mkdir -p /redis-data/${port}
    if [ -e /redis-data/${port}/nodes.conf ]; then
        rm /redis-data/${port}/nodes.conf
    fi

    if [ -e /redis-data/${port}/dump.rdb ]; then
        rm /redis-data/${port}/dump.rdb
    fi

    if [ -e /redis-data/${port}/appendonly.aof ]; then
        rm /redis-data/${port}/appendonly.aof
    fi
    PORT=${port} envsubst < /etc/redis/redis.tmpl > /redis-conf/${port}/redis.conf
done

for port in $(seq $INITIAL_PORT $max_port); do
    redis-server /redis-conf/${port}/redis.conf
done
tail -f /redis-logs/redis*.log