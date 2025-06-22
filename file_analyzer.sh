#!/bin/bash

getExtension() {
    filename=$1
    echo "${filename##*.}"
}

map() {
    case $1 in
        txt | md) echo 0 ;;
        jpg | png | gif) echo 1 ;;
        sh) echo 2 ;;
        csv | json) echo 3 ;;
        *) echo 4 ;;
    esac
}

arr=(0 0 0 0 0)
for i in $@
do
    (( arr[$(map $(getExtension $i))]++ ))
done

# Print results
echo "Text/Markdown: ${arr[0]}"
echo "Images:        ${arr[1]}"
echo "Shell scripts: ${arr[2]}"
echo "Data files:    ${arr[3]}"
echo "Other:         ${arr[4]}"