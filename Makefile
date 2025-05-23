all: part1

clean: part1
	rm $^
	clear

part1: part1.c slow_functions.c
	gcc -o part1 $^