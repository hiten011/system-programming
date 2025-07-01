#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int counter = 0;
const int update = 100000;

pthread_mutex_t mutex;

void* updateCounter(void*) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < update; i++) {
        counter++;
    }
    pthread_mutex_unlock(&mutex);
}

int main() {

    pthread_mutex_init(&mutex, NULL);

    pthread_t id[2];
    for (int i = 0; i < 2; i++) {
        pthread_create(&id[i], NULL, &updateCounter, NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(id[i], NULL);
    }

    printf("counter: %d\n", counter);
}