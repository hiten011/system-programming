#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/wait.h> 

int main(int argc, char *argv[]) {
    char* fileName = argv[1];

    int id = fork();
    if (id == 0) {
        // child process
        int fd = open(fileName, O_RDONLY);
        dup2(fd, 0);
        close(fd);

        char *args[] = {"wc", NULL};
        execvp("wc", args);
    }

    wait(NULL);

    return 0;
}