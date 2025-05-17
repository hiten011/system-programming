/* execute.c - code used by small shell to execute commands */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>

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
		}
		
		// wrinting to pipe
		if (index < n - 1) {
			// writing to pipe
			dup2(wpipe[1], 1);
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
