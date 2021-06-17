#!/bin/sh
if [ -z "$GAME_ID" ]; then
    echo "GAME_ID 不能为空 export GAME_ID=9001"
    exit
fi
if [ -z "$GATEWAY_ID" ]; then
    echo "GATEWAY_ID 不能为空 export GATEWAY_ID=9001"
    exit
fi

ps -ef|grep "game_server.php" | grep -v "grep" | awk '{print $2}' | xargs kill -15
sleep 5
php /data/dragonica/server/php/Game/Cli/game_server.php $GATEWAY_ID > /data/log/game.log 2>&1 &