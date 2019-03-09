#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include "../matrix.h"

#define MAX_THREAD 4
#define MATRIX_DIMENSION 5

Matrix_t *primeira, *segunda, *soma;

void* sum_matrix(void* arg) {
    register unsigned int i, j;
    int core = *((int*)arg);
    // Each thread computes 1/4th of matrix addition 
    for (i = core * MATRIX_DIMENSION / 4; i < (core + 1) * MATRIX_DIMENSION / 4; i++) { 
        for (j = 0; j < MATRIX_DIMENSION; j++) { 
            // Compute Sum Row wise
            soma->matrix[i][j] = primeira->matrix[i][j] + segunda->matrix[i][j]; 
        }
    } 
}

int main(int argc, char **argv) {
    srand(time(0));
    primeira = generate_matrix(MATRIX_DIMENSION, MATRIX_DIMENSION, 1);
    segunda = generate_matrix(MATRIX_DIMENSION, MATRIX_DIMENSION, 1);
    soma = generate_matrix(MATRIX_DIMENSION, MATRIX_DIMENSION, 0);
    pthread_t threads[MAX_THREAD];
    int thread_part[MAX_THREAD]; 
    unsigned int i;
    for (i = 0; i < MAX_THREAD; i++) {
        thread_part[i] = i;
        pthread_create(&threads[i], NULL, sum_matrix, &thread_part[i]);
    }
    for (i = 0; i < MAX_THREAD; i++) {
        pthread_join(threads[i], NULL); 
    }

    print_matrix(soma);

    destroy(primeira);
    destroy(segunda);
    destroy(soma);
    return 0;
}