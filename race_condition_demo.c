#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int counter = 0;
const int update = 100000;

void* updateCounter(void*) {
    for (int i = 0; i < update; i++) {
        counter++;
    }
}

int main() {
    pthread_t id[2];
    for (int i = 0; i < 2; i++) {
        pthread_create(&id[i], NULL, &updateCounter, NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(id[i], NULL);
    }

    printf("counter: %d\n", counter);
}