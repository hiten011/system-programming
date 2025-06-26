#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

int main() {
    // creating pipe
    int fd[2];
    pipe(fd);

    int id1 = fork();
    if (id1 == 0) {
        // child process: "ls -l"
        
        // redirect stdout
        close(fd[0]); // readend
        dup2(fd[1], 1);
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
    }

    int id2 = fork();
    if (id2 == 0) {
        // child process: "wc"
        // redirect stdin
        close(fd[1]); // writeend
        dup2(fd[0], 0);
        close(fd[0]);

        execlp("wc", "wc", "-l", NULL);
    }

    // Parent process
    close(fd[0]);
    close(fd[1]);

    wait(NULL); // Wait for first child
    wait(NULL); // Wait for second child
    return 0;
}