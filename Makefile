all: part1

clean: PART1
	rm $^
	clear

part1: part1.c slow_functions.c
	gcc -o PART1 $^

part2: part2.c slow_functions.c
	gcc -o PART2 $^