/* execute.c - code used by small shell to execute commands */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include    <fcntl.h>
#include    <string.h>

int search(char *argv[], const char *find);

int execute(char *argv[])
/*
 * purpose: run a program passing it arguments
 * returns: status returned via wait, or -1 on error
 *  errors: -1 on fork() or wait() errors

 */
{
	int	pid ;
	int	child_info = -1;

	if ( argv[0] == NULL )		/* nothing succeeds	*/
		return 0;

	if ( (pid = fork())  == -1 )
		perror("fork");
	else if ( pid == 0 ){
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execvp(argv[0], argv);
		perror("cannot execute command");
		exit(1);
	}
	else {
		if ( wait(&child_info) == -1 )
			perror("wait");
	}
	return child_info;
}

int executePipes(char *argv[], int rpipe[2], int wpipe[2], int index, int n)
/*
 * purpose: run a program passing it arguments
 * returns: status returned via wait, or -1 on error
 *  errors: -1 on fork() or wait() errors

 */
{
	int	pid ;
	int	child_info = -1;

	if ( argv[0] == NULL )		/* nothing succeeds	*/
		return 0;

	if ( (pid = fork())  == -1 )
		perror("fork");
	else if ( pid == 0 ){

		close(wpipe[0]);
		close(rpipe[1]);

		if (index != 0) {
			// reading from pipe
			dup2(rpipe[0], 0);
		} else {
			// if first command check for < (input)redirection
			int i = search(argv, "<"); // index at < appears
			if ( i != -1 ) {
				// found < redirection: opening file and redirecting input from file
				int fd = open(argv[i + 1], O_RDONLY);
				dup2(fd, 0);

				close(fd);

				// cutting the argv to store only command
				argv[i] = NULL;
			}
		}
		
		// wrinting to pipe
		if (index < n - 1) {
			// writing to pipe
			dup2(wpipe[1], 1);
		} else {
			// check for redirection > (output)
			int o = search(argv, ">"); // index at which > appers
			if ( o != -1 ) {
				// found > redirection: opening file and redirecting output to file
				int fd = open(argv[o + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				dup2(fd, 1);

				close(fd);

				// cutting the argv to store only command
				argv[o] = NULL;
			}
		}

		close(rpipe[0]);
		close(wpipe[1]);
		
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execvp(argv[0], argv);
		perror("cannot execute command");
		exit(1);
	}
	else {
		// swapping the pipes
		close(rpipe[1]);
		close(rpipe[0]);
		
		rpipe[0] = wpipe[0];
		rpipe[1] = wpipe[1];
		
		if ( wait(&child_info) == -1 )
			perror("wait");
	}
	return child_info;
}

int search(char *argv[], const char* find) { 
	for (int i = 0; argv[i] != NULL; i++) {
		if (strcmp(argv[i], find) == 0) {
			return i;
		}
	}

	return -1;
}
