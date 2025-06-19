#!/bin/bash

echo "number,prac_mark,exam_mark"

# Create temp file
file='temp.csv'
tail -n +2 "$1" > "$file"
tail -n +2 "$2" >> "$file"

# create array
mapfile -t indexes < <(cut -d',' -f1 "$file" | sort -u)

# Loop through each student
for index in "${indexes[@]}"
do
    prac_mark=$(grep "^$index," "$1" | cut -d',' -f2)
    exam_mark=$(grep "^$index," "$2" | cut -d',' -f2)

    [[ -z $prac_mark ]] && prac_mark='-'
    [[ -z $exam_mark ]] && exam_mark='-'

    echo "$index,$prac_mark,$exam_mark"
done

rm -f "$file"
