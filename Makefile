all : sequence pipeline

sequence: 
	gcc $@.c -o $@.out

pipeline:
	gcc $@.c -o $@.out