#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main() {
    
    // taking input
    char cmds[100][256]; // max: 100 lines per file and 256 characters per line
    
    int count = 0;
    while (count < 100 && fgets(cmds[count], 256, stdin) != NULL) {
        // removing the newline character
        cmds[count][strcspn(cmds[count], "\n")] = '\0'; 
        count++;
    }

    // priinting input for confirmation
    // for (int i = 0; i < count; i++) {
    //     printf("Line %d: %s\n", i+1, cmds[i]);
    // }

    // processing the input
    for (int i = 0; i < count; i++) {
        int id = fork();

        if (id == 0) {
            // child process
            
        } else {
            // parent process
            wait(NULL);
        }
    }


    return 0;
}