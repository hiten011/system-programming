#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

char** convetCommands(char* cmd) {
    // parsing throught the arguments
    const int len = 12; // maximum arguments
    const char* delimiter = " ";
    char** token = malloc(len * sizeof(char*));
    int i = 0;

    token[i] = strtok(cmd, delimiter);
    while (token[i] != NULL) {
        i++;
        token[i] = strtok(NULL, delimiter);
    }
    token[i] = NULL;

    return token;
}

int main() {
    
    // taking input
    char cmds[100][256]; // max: 100 lines per file and 256 characters per line
    
    int count = 0;
    while (count < 100 && fgets(cmds[count], 256, stdin) != NULL) {
        // removing the newline character
        cmds[count][strcspn(cmds[count], "\n")] = '\0'; 
        count++;
    }

    // processing the input
    for (int i = 0; i < count; i++) {
        // Forking
        int id = fork();
        if (id == -1) {
            printf("Fork Failed!");
            return 1;
        }

        if (id == 0) {
            // child process

            // getting the command in terms of array
            char** cmd = convetCommands(cmds[i]);
            
            // running the excv command
            execvp(cmd[0], cmd);

            // incase the execvp fails
            free(cmd);
            perror("execvp");
            return 1;

        } else {
            // parent process
            wait(NULL);
        }
    }


    return 0;
}