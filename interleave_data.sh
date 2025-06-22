#!/bin/bash

touch "merged.csv"
echo "timestamp,value1" >> merged.csv

add() {
    while IFS="\n"
    do

    done << $(tail +2 $1)
}

for i in $@
do
    add $i
done