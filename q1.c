#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

int main(int args, char* arg[]) {
    // printf("%d, %s\n", args, arg[1]);

    int id = fork();

    if (id == 0) {
        // child process
        int fd = open(arg[1], O_RDONLY);
        dup2(fd, 0);

        char* cmd[] = {"wc", NULL};
        execvp("wc", cmd);
    } else {
        wait(NULL);
    }

    return 0;
}