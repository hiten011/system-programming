all: default part1 part2 part3

clean:
	rm smsh1 smsh2 smsh3 smsh4
	rm *.txt

default: smsh1.c splitline.c execute.c helper.c
	gcc -o smsh1 $^

part1: smsh2.c splitline.c execute.c helper.c
	gcc -o smsh2 $^

part2: smsh3.c splitline.c execute.c helper.c
	gcc -o smsh3 $^

part3: smsh4.c splitline.c execute.c helper.c
	gcc -o smsh4 $^