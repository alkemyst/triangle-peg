#!/bin/bash

before=`date +%s.%N`
./findBestMove.exe 5 1
after=`date +%s.%N`

echo "print 'time needed: ',$after - $before" | python

