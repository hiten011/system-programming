all: redirector pipe_command multi_pipe tee

clean:
	rm *.out *.txt
	clear

redirector pipe_command multi_pipe tee: %: %.c
	gcc $^ -o $@.out