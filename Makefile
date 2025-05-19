all: task1 task2 task2.1 task3 task4

clean: task1 task2 task2.1 task3 task4
	rm $^
	clear

task1: simple_thread.c
	gcc -o $@ $^
task2: race_condition_demo.c
	gcc -o $@ $^
task2.1: race_condition_demo_mutex.c
	gcc -o $@ $^
task3: matrix_row_sum.c
	gcc -o $@ $^
task4: ping_pong.c
	gcc -o $@ $^