#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

int main(int args, char* arg[]) {
    int fd[2];
    pipe(fd);

    int id = fork();
    if (id == 0) {
        // child process
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);

        char* cmd[] = {"ls", "-la", NULL};
        execvp("ls", cmd);
        exit(1);
    }

    close(fd[1]); // write end

    int fd2[2];
    pipe(fd2);

    int id2 = fork();
    if (id2 == 0) {
        // child Process
        close(fd2[0]);

        dup2(fd[0], 0);
        dup2(fd2[1], 1);

        close(fd2[1]);
        close(fd[0]);

        char* cmd[] = {"grep", "^-", NULL};
        execvp("grep", cmd);
        exit(1);
    }

    close(fd[0]); // read end
    close(fd2[1]); // write end

    int id3 = fork();
    if (id3 == 0) {
        // child process
        dup2(fd2[0], 0);
        close(fd2[0]);

        char* cmd[] = {"wc", "-l", NULL};
        execvp("wc", cmd);
        exit(1);
    }

    close(fd2[0]);
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    return 0;
}