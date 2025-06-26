#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    FILE* output = fopen("disk-usage.txt", "w");
    FILE* error = fopen("du-errors.txt", "w");

    int id = fork();
    if (id < 0) {
        printf("%s\n", "Fork Failed");
        return 1;
    } 
    
    else if (id == 0) {
        // child process

        // changing file descriptors
        dup2(fileno(output), 1);
        dup2(fileno(error), 2);

        // running process
        char *args[] = {"du", "-sh", "/root", NULL};
        execvp(args[0], args);

        // If execvp fails
        perror("execvp failed");
        return 1;
    } 

    // parent process
    wait(NULL);
    printf("%s\n", "disk usage analysis complete - results have been written to files");

    fclose(output);
    fclose(error);

    return 0;
}