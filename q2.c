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

        char* cmd[] = {"ls", "-l", NULL};
        execvp("ls", cmd);
    }

    int id2 = fork();

    if (id2 == 0) {
        // child Process
        close(fd[1]);
        dup2(fd[0], 0);

        char* cmd[] = {"wc", "-l", NULL};
        execvp("wc", cmd);
    }

    return 0;
}