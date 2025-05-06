#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>
#include <string.h>

int main(int args, char* arg[]) {
    // printf("%d, %s\n", args, arg[1]);
    char input[1000];

    while (fgets(input, sizeof(input), stdin) != NULL){
        int id = fork();

        if (id == 0) {
            // child process
            int file = open(arg[1], O_WRONLY | O_CREAT | O_APPEND);
            write(file, input, strlen(input));
            close(file);
            return 0;
        } else {
            // parent process
            wait(NULL);
            printf("%s", input);
        }
    }

    return 0;
}