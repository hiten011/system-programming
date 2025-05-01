#include <stdio.h>
#include <unistd.h>

int main() {
    char *args[] = {"du", "-sh", "/root/sp", NULL};
    execvp(args[0], args);
    return 0;
}