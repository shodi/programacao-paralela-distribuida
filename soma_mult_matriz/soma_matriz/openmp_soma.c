#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000

void print_matrix(int matrix[MAX_SIZE][MAX_SIZE]) {
    register size_t i, j;
    for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < MAX_SIZE; j++) {
            printf("resultado [%ld][%ld] = %d\n", i, j, matrix[i][j]);
        }
    }
}

int** generate_matrix(int value) {
    int **matrix;
    register size_t i, j;
    matrix = (int **)malloc(MAX_SIZE * sizeof(int*));
    for (i = 0; i < MAX_SIZE; i++) {
        matrix[i] = (int *)malloc(MAX_SIZE * sizeof(int));
        for (j = 0; j < MAX_SIZE; j++) {
            matrix[i][j] = value;
        }
    }
    return matrix;
}

void destroy(int **matrix) {
    register size_t i;
    for (i = 0; i < MAX_SIZE; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int matriz3[MAX_SIZE][MAX_SIZE];
int main(int argc, char **argv) {
    int **matriz1;
    int **matriz2;

    matriz1 = generate_matrix(1);
    matriz2 = generate_matrix(2);
    register int i, j;
    #pragma omp parallel private(i, j)
    {
        #pragma omp for
        for (i = 0; i < MAX_SIZE; i++) {
            for (j = 0; j < MAX_SIZE; j++) {
                matriz3[i][j] = matriz1[i][j] + matriz2[i][j];
            }
        }
    }

    print_matrix(matriz3);
    destroy(matriz1);
    destroy(matriz2);

    return 0;
}