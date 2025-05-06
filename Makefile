all : sequence pipeline

sequence: sequence.c
	gcc $@.c -o $@

pipeline: pipeline.c
	gcc $@.c -o $@