all: default part1 part2

clean:
	rm *.out

default: smsh1.c splitline.c execute.c
	gcc -o smsh1 $^

part1: smsh2.c splitline.c execute.c
	gcc -o smsh2 $^

part2: smsh3.c splitline.c execute.c
	gcc -o smsh3 $^