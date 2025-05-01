#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // storing the arguments
    char* cmd = argv[1];
    // printf("%d %s\n", argc, cmd);

    // parsing throught the arguments
    const int len = strlen(cmd);
    const char* delimiter = " ";
    char* token[len];
    int i = 0;

    token[i] = strtok(cmd, delimiter);
    while (token[i] != NULL) {
        i++;
        token[i] = strtok(NULL, delimiter);
    }
    token[i] = NULL;
    // printf("%s\n", token[3]);

    // running the excv command
    execvp(token[0], token);
    return 1;
}