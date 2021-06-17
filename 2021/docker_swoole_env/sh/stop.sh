#!/bin/sh
killall php
arena_pid=`ps -ef | grep arena | grep -v grep | awk '{print $2}'`
if [ -z "$arena_pid" ];
then
        echo "[ not find arena pid ]"
else
        echo "find result: $arena_pid "
        kill -9 $arena_pid
fi