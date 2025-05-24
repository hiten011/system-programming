#include "slow_functions.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// How nice of me to include a global that tells you how many commands there were :)
int total_commands = 0;


// ####################################################################################
// ## Please write some code in the following two functions

pthread_cond_t writerCond;
pthread_cond_t readerCond;
pthread_mutex_t lock;

void * writer(void * in_ptr)
{

	char ** commands = in_ptr;
	//must include bad_write;
	pthread_mutex_lock(&lock);

	for (int i = 0; i < total_commands; i++) {
		bad_write(commands[i]);
		
		// signal reader to start
		pthread_cond_signal(&readerCond);

		// waiting for read to finish
		pthread_cond_wait(&writerCond, &lock);
	}

	pthread_cond_signal(&readerCond);
	pthread_mutex_unlock(&lock);

	return NULL;
}

void * reader(void * empty)
{
	//must include bad_read
	pthread_mutex_lock(&lock);

	if (!get_written()) {
		// wait for writer: incase reader lock first
		pthread_cond_wait(&readerCond, &lock);
	}

	while (get_written()) {
		bad_read(NULL);
		
		// signal writer to start
		pthread_cond_signal(&writerCond);
		
		// wait for writer
		pthread_cond_wait(&readerCond, &lock);
	}

	pthread_cond_signal(&writerCond);
	pthread_mutex_unlock(&lock);

	return NULL;
}




int main()
{
	// ## SOME SPACE IN CASE YOU NEED TO INITIALISE VARIABLES
	pthread_cond_init(&readerCond, NULL);
	pthread_cond_init(&writerCond, NULL);
	pthread_mutex_init(&lock, NULL);

	// ################################################################################
	// ## DO NOT MODIFY BELOW HERE

	// ## Parse STDIN and read into commands
	char * commands[100];
	char line[256];
    while (fgets(line, 256, stdin))
    {
		commands[total_commands] = (char*)(malloc(strlen(line) * sizeof(char)));
 		strcpy(commands[total_commands], line);
		total_commands = total_commands + 1;
	}

	pthread_t write1;
	pthread_t read1;

	// Creates a thread which executes writer!
	if(pthread_create(&write1, NULL, writer, commands))
	{
		fprintf(stderr, "Error creating write thread\n");
		return 1;
	}

	// Creates a thread which executes reader!
	if(pthread_create(&read1, NULL, reader, NULL))
	{
		fprintf(stderr, "Error creating read thread\n");
		return 1;
	}

	// Ensure Threads Join Well
	if(pthread_join(write1, NULL)) 
	{
		fprintf(stderr, "Error joining write thread\n");
		return 2;
	}

	if(pthread_join(read1, NULL)) 
	{
		fprintf(stderr, "Error joining read thread\n");
		return 2;
	}

	// Did you really call the right functions?
	get_output();

	// I am a responsible memory user!
	int command_i;
	for (command_i = 0; command_i < total_commands; command_i++)
	{
		free(commands[command_i]);
	}
	return 0;
	// ## DO NOT MODIFY ABOVE HERE
	// ################################################################################
}

