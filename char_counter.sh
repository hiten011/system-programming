#!/bin/bash

declare -A arr

while IFS= read -r -n 1 char; do
    [[ -z "$char" ]] && continue
    (( arr["$char"]++ ))
done

for i in "${!arr[@]}"; do
    echo "$i: ${arr[$i]}"
done | sort -t ':' -k2 -nr
