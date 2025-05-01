#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        system("echo | du -sh /root");
    } else {
        // Parent process
        
    }

    return 0;
}
