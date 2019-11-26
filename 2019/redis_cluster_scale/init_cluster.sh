#!/bin/sh
if [ -z "$INITIAL_PORT" ]; then # Default to port 7000
    INITIAL_PORT=7000
fi

if [ -z "$SLAVES_PER_MASTER" ]; then # Default to 1 SLAVES_PER_MASTER
    SLAVES_PER_MASTER=1
fi
max_port=$(($INITIAL_PORT + 1 * ( $SLAVES_PER_MASTER  + 1 ) - 1))
nodes=""
pickNode=""
for hostname in $(docker-compose ps node | tail -n +3 | awk '{ print $1 }'); do
    #cluster对hostname不友好，得使IP。
    IP=$(docker inspect -f '{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' ${hostname})
    for port in $(seq $INITIAL_PORT $max_port); do
        nodes="$nodes${IP}:${port} "
        pickNode="${hostname}"
    done
done

echo "docker exec $pickNode redis-cli -p $INITIAL_PORT --cluster create --cluster-replicas $SLAVES_PER_MASTER $nodes--cluster-yes "