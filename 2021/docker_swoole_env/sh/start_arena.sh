#!/bin/sh

ARENA_DIR='/data/dragonica/tags'
cd ${ARENA_DIR}
chmod +x arena-1.0
nohup ./arena > /data/log/arena.log 2>&1 &
cd /