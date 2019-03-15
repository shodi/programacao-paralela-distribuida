#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include "../matrix.h"

#define MAX_THREAD 4
#define MATRIX_DIMENSION 2

/*
    |++++++++++++++++|++++++++++++++++++++++++|
    | Status retorno | Significado            |
    |++++++++++++++++|++++++++++++++++++++++++|
    |              0 | Success                |
    |----------------|------------------------|
    |              1 | Matrizes incompatíveis |
    |+++++++++++++++++++++++++++++++++++++++++|
*/

Matrix_t *primeira, *segunda, *result;

void* mult_matrix(void* args) {
    register unsigned int i, j, k;
    int thread_index = *((int*) args);

    for (i = thread_index * MATRIX_DIMENSION / MAX_THREAD; i < (thread_index + 1) * MATRIX_DIMENSION / MAX_THREAD; i++) {
        for (j = 0; j < MATRIX_DIMENSION; j++) {
            for (k = 0; k < MATRIX_DIMENSION; k++) {
                result->matrix[i][j] += primeira->matrix[i][k] * segunda->matrix[k][j];
            }
        }
    }
}

int main(int argc, char **argv) {
    srand(time(0));
    primeira = generate_matrix(MATRIX_DIMENSION, MATRIX_DIMENSION, 1);
    segunda = generate_matrix(MATRIX_DIMENSION, MATRIX_DIMENSION, 1);
    result = generate_matrix(MATRIX_DIMENSION, MATRIX_DIMENSION, 0);
    pthread_t threads[MAX_THREAD];
    int threads_index[MAX_THREAD];

    int i = 0;
    if (primeira->m != segunda->n) return 1;
    for (; i < MAX_THREAD; i++) {
        threads_index[i] = i;
        pthread_create(&threads[i], NULL, mult_matrix, &threads_index[i]);
    }

    for (i = 0; i < MAX_THREAD; i++) {
        pthread_join(threads[i], NULL);
    }

    print_matrix(result);

    destroy(primeira);
    destroy(segunda);
    destroy(result);

    return 0;

}