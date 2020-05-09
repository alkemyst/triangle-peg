#!/bin/bash

before=`date +%s.%N`
./flexiSearchFast.exe 5 1
after=`date +%s.%N`

echo "print 'time needed: ',$after - $before" | python

