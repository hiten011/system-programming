#!/bin/bash

filename="merged.csv"
touch $filename
echo "timestamp,value1" > $filename

add() {
    tail -n +2 "$1" | while IFS= read -r line || [[ -n $line ]]
    do
        # echo $line
        local timestamp=$(cut -d',' -f1 <<< $line)
        [[ -z $(grep $timestamp $filename) ]] && $(echo "$line" >> "$filename")
    done
}

for i in $@
do
    add $i
done

cat $filename
rm $filename