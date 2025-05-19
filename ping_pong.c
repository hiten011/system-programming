#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

pthread_mutex_t mutex;
pthread_cond_t cond1;
pthread_cond_t cond2;

void* ping(void* ) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 10; i++) {
        printf("Ping\n");
        pthread_cond_signal(&cond1);
        pthread_cond_wait(&cond2, &mutex);
    }

    pthread_cond_signal(&cond1);
    pthread_mutex_unlock(&mutex);

    return NULL;  
}

void* pong(void* ) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 10; i++) {
        printf("Pong\n");
        pthread_cond_signal(&cond2);
        pthread_cond_wait(&cond1, &mutex);
    }
    
    pthread_cond_signal(&cond2);
    pthread_mutex_unlock(&mutex);

    return NULL;  
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond1, NULL);
    pthread_cond_init(&cond2, NULL);

    pthread_t id[2];
    pthread_create(&id[0], NULL, &ping, NULL);
    pthread_create(&id[1], NULL, &pong, NULL);

    for (int i = 0; i < 2; i++) {
        pthread_join(id[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);

    return 0;
}