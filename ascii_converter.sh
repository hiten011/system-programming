#!/bin/bash

a=$(printf "%d" "'$1")
echo ASCII: $a

printf "Char: \\$(printf '%03o' $a) \n"
