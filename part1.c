#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include "slow_functions.h"

const int n = 10;

int main() {
    // calling slow function 2
    pthread_t t1;
    pthread_create(&t1, NULL, &slow_function2, NULL);

    // creating array to store threads
    pthread_t id[n];
    for (int i = 0; i < n; i++) {
        pthread_create(&id[i], NULL,  &slow_function1, NULL);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(id[i], NULL);
    }
    gs 
    pthread_join(t1, NULL);
    return 0;
}