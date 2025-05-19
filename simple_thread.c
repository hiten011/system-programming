#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* hello(void* i) {
    int* id =  (int*)i;
    printf("Hello from thread %d\n", *id);
}

int main() {
    pthread_t t1[2];
    for (int i = 0; i < 2; i++) {
        pthread_create(&t1[i], NULL, &hello, &i);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(t1[i], NULL);
    }

    return 0;
}