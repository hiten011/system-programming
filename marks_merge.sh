#!/bin/bash

# 1) Build an array of all unique student IDs
mapfile -t indexes < <(
  for file in "$@"; do
    tail -n +2 "$file" | cut -d',' -f1
  done | sort -u
)

# 2) Print the merged header
header="number"
for file in "$@" 
do
  label=$(head -n1 "$file" | cut -d',' -f2)
  header+=",$label"
done
echo "$header"

# 3) For each student ID, pull in each file’s mark (or “-” if missing)
for id in "${indexes[@]}" 
do
  line="$id"
  for file in "$@"; do
    mark=$(grep "^$id," "$file" | cut -d',' -f2)
    [[ -z $mark ]] && mark="-"
    line+=",$mark"
  done
  echo "$line"
done
