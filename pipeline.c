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

    // creating pipes
    int prev_pipe[2];
    if (pipe(prev_pipe) == -1) {return 1;}
    // pipe[0]: Reading
    // pipe[1]: writing

    // processing the input
    for (int i = 0; i < count; i++) {

        int cur_pipe[2];
        if (pipe(cur_pipe) == -1) {return 1;}
        // pipe[0]: Reading
        // pipe[1]: writing

        // Forking
        int id = fork();
        if (id == -1) {
            printf("Fork Failed!");
            return 1;
        }

        if (id == 0) {
            // child process

            close(prev_pipe[1]); // write of prev
            close(cur_pipe[0]); // read of current
            
            if (i != 0) {
                dup2(prev_pipe[0], 0); // reading from the prev
            }

            if (i != count - 1) {
                dup2(cur_pipe[1], 1); // writing to the cur
            }

            close(prev_pipe[0]);
            close(prev_pipe[1]);

            // getting the command in terms of array
            char** cmd = convetCommands(cmds[i]);
            // running the excv command
            execvp(cmd[0], cmd);

            // incase the execvp fails
            free(cmd);
            perror("execvp");
            return 2;
        } else {
            if (i == count - 1) {
                continue;
            }

            // parent process
            close(prev_pipe[0]); // read of prev
            close(prev_pipe[1]); // write of current
            
            prev_pipe[0] = cur_pipe[0];
            prev_pipe[1] = cur_pipe[1];

            wait(NULL);
        } 


    }

    return 0;
}
