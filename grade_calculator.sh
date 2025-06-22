#!/bin/bash

case $1 in 
100 | 9[0-9]) echo A ;;
8[0-9]) echo B ;;
7[0-9]) echo C ;;
6[0-9]) echo D ;;
*) echo F ;;
esac