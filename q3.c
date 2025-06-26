#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    FILE* output = fopen("disk-usage.txt", write);
    FILE* error = fopen("du-errors.txt", write);

    int id = fork();
    if (id < 0) {
        printf("%s\n", "Fork Failed");
        return 1;
    } 
    
    else if (id == 0) {
        // child process

        // changing file descriptors
        dup2(output, 1);
        dup2(error, 2);

        // running process
        char *args[] = {"du", "-sh", "/root/sp", NULL};
        execvp(args[0], args);
    } 
    
    else {
        // parent process
        wait(NULL);
        printf("%s\n", "disk usage analysis complete - results have been written to files");
    }

    return 0;
}