#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

pthread_mutex_t mutex;
bool isPing;

void* ping(void* ) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        if (isPing) {
            printf("Ping\n");
        }
        isPing = !isPing;
        pthread_mutex_unlock(&mutex);
    }
}

void* pong(void* ) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        if (isPing) {
            printf("Pong\n");
        }
        isPing = !isPing;
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    isPing = true;

    pthread_t id[2];
    pthread_create(&id[0], NULL, &ping, NULL);
    pthread_create(&id[1], NULL, &pong, NULL);

    for (int i = 0; i < 2; i++) {
        pthread_join(id[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);

    return 0;
}