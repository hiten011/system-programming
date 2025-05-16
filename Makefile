all: part1

default: smsh1.c splitline.c execute.c
	gcc -o smsh1 $^

part1: smsh2.c splitline.c execute.c
	gcc -o smsh2 $^