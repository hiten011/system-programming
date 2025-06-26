#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // copying
    char* cmd = (char*) malloc(sizeof(argv[1]));
    strcpy(cmd, argv[1]);

    // storing cmd
    char* cmds[100];
    int index = 0;
    cmds[index] = strtok(cmd, " ");
    while (cmds[index] != NULL) {
        cmds[++index] = strtok(NULL, " ");
    }

    // running processor
    execvp(cmds[0], cmds);
    return 0;
}