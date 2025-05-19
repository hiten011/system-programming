#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 3
int matrix[N][N] = {
    {1, 2, 3},
    {1, 2, 3},
    {4, 5, 6}
};

typedef struct {
    int row;
    int sum;
} argument;

void* add(void* a) {
    // type casting
    argument* arg = (argument*)a;

    int row = arg->row;
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += matrix[row][i];
    }

    arg->sum = sum;
}

int main() {
    argument** arg = malloc(N * sizeof(argument*));

    pthread_t id[N];
    for (int i = 0; i < N; i++) {
        arg[i] = malloc(sizeof(argument));
        arg[i]->row = i;

        pthread_create(&id[i], NULL, &add, arg[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(id[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        printf("Row %d sum = %d\n", i, arg[i]->sum);
    }
    
    return 0;
}