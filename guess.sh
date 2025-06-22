#!/bin/bash

num=$(($RANDOM % 10 + 1))

echo "Guess the Num: "
read guess
while [[ $guess != $num ]]
do
    echo "Try Again!!!"
    echo "Guess the Num: "
    read guess
done

echo "Congrats, Num guessed successfully"