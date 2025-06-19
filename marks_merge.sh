#!/bin/bash

# Remove and recreate merged.csv with header
rm merged.csv
touch merged.csv
echo "number, prac_mark, exam_mark" >> merged.csv

rm temp.csv
touch temp.csv

file='temp.csv'
tail -n +2 "$1" >> $file
echo >> $file
tail -n +2 "$2" >> $file

# storing indexes
indexes=$( cut -d',' -f1 $file | sort -u )

# Reading array
for index in ${indexes[@]}
do
    prac_mark=$(grep $index "$1" | cut -d',' -f2)
    exam_mark=$(grep $index "$2" | cut -d',' -f2)

    if [[ -z $prac_mark ]] 
    then
        prac_mark='-'
    fi

    if [[ -z $exam_mark ]] 
    then
        exam_mark='-'
    fi

    # printing to merged.csv
    echo $index,$prac_mark,$exam_mark >> merged.csv
done 

rm $file