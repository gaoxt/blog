#!/bin/sh

if [ "$1" = 'redis-cluster' ]; then
    # Allow passing in cluster IP by argument or environmental variable
    IP="${2:-$IP}"

    if [ -z "$IP" ]; then # If IP is unset then discover it
        IP=$(hostname -i)
    fi

    echo " -- IP Before trim: '$IP'"
    IP=$(echo ${IP}) # trim whitespaces
    echo " -- IP Before split: '$IP'"
    IP=${IP%% *} # use the first ip
    echo " -- IP After trim: '$IP'"

    if [ -z "$INITIAL_PORT" ]; then # Default to port 7000
      INITIAL_PORT=7000
    fi

    if [ -z "$MASTERS" ]; then # Default to 3 masters
      MASTERS=3
    fi

    if [ -z "$SLAVES_PER_MASTER" ]; then # Default to 1 slave for each master
      SLAVES_PER_MASTER=1
    fi

    max_port=$(($INITIAL_PORT + $MASTERS * ( $SLAVES_PER_MASTER  + 1 ) - 1))

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

      PORT=${port} envsubst < /redis-conf/redis.tmpl > /redis-conf/${port}/redis.conf
      nodes="$nodes $IP:$port"
    done

    for port in $(seq $INITIAL_PORT $max_port); do
      redis-server /redis-conf/${port}/redis.conf
    done
      
    echo "Using redis-cli to create the cluster"
    echo "$SLAVES_PER_MASTER" 
    echo "$nodes"
    echo "yes" | eval redis-cli --cluster create --cluster-replicas "$SLAVES_PER_MASTER" "$nodes"

    tail -f /redis-logs/redis*.log
else
  exec "$@"
fi
redis-cli --cluster create --cluster-replicas "1" 