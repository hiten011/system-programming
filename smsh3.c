/**  smsh1.c  small-shell version 1
 **		first really useful version after prompting shell
 **		this one parses the command line into strings
 **		uses fork, exec, wait, and ignores signals
 **/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	"smsh.h"

#define	DFL_PROMPT	"> "

int main()
{
	char	*cmdline, *prompt, **arglist,  **cmds;
	int	result;
	void	setup();

	prompt = DFL_PROMPT ;
	setup();

	while ( (cmdline = next_cmd(prompt, stdin)) != NULL ){
		int n; // stores length of commands in pipes
		char** cmds;
		if ((cmds = splitpipe(cmdline, &n)) == NULL) {
			return 1;
		}
		// printf("%d %s %s", n, cmds[0], cmds[1]);

		// creating pipes
		int rpipe[2]; // reading pipe
		if (pipe(rpipe) == -1) return 1;

		for (int i = 0; i < n; i++) {
			// runs the loop for each commans
			// printf("%s\n", cmds[i]);

			// creating writing pipe
			int wpipe[2];
			if (pipe(wpipe) == -1) return 1;

			if ( (arglist = splitline(cmds[i])) != NULL  ){
				result = executePipes(arglist, rpipe, wpipe, i, n);
				freelist(arglist);
			}
		}

		free(cmdline);
	}
	return 0;
}

void setup()
/*
 * purpose: initialize shell
 * returns: nothing. calls fatal() if trouble
 */
{
	signal(SIGINT,  SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
	fprintf(stderr,"Error: %s,%s\n", s1, s2);
	exit(n);
}
