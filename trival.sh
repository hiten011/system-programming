#!/bin/bash
x=0
for i in "$@"
do
    echo "$x = $i"
    x=$((x + 1))
done