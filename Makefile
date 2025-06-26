INPUT="ls -l"

all: spawner

clean:
	rm -f *.out
	clear

spawner: spawner.c
	gcc $^ -o $@.out && ./$@.out $(INPUT)

q1 q2 q3: %: %.c
	gcc $^ -o $@.out && ./$@.out
