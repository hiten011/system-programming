all: part1

clean: part1 part2
	rm PART1 PART2
	clear

part1: part1.c slow_functions.c
	gcc -o PART1 $^

part2: part2.c slow_functions.c
	gcc -o PART2 $^