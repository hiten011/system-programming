#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

int main(int args, char* arg[]) {
    // printf("%d, %s\n", args, arg[1]);

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
    }

    int fd2[2];
    int id2 = fork();

    if (id2 == 0) {
        // child Process
        dup2(fd[0], 0);
        dup2(fd2[1], 1);

        char* cmd[] = {"grep", "^-", NULL};
        execvp("grep", cmd);
    }

    int id3 = fork();

    if (id3 == 0) {
        // child process
        close(fd2[1]);
        dup2(fd2[0], 0);

        char* cmd[] = {"ls", "-l", NULL};
        execvp("ls", cmd);
    }

    return 0;
}