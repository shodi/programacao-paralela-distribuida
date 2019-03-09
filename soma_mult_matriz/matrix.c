#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_matrix(Matrix_t *bidimen_array) {
    int **matrix = bidimen_array->matrix;
    register size_t i, j;
    for (i = 0; i < bidimen_array->n; i++) {
        for (j = 0; j < bidimen_array->m; j++) {
            printf("MATRIZ[%ld][%ld] = %d\n", i, j, bidimen_array->matrix[i][j]);
        }
    }
}

/*
 * Function: generate_matrix
 * ----------------------------
 *   Retorna um ponteiro para uma estrutura do tipo Matrix_t contendo uma matriz n x m
 *
 *   n: quantidade de linhas
 *   m: quantidade de colunas
 *
 *   returns: a pointer to Matrix_t with a n x m matrix
 */
Matrix_t* generate_matrix(size_t n, size_t m, unsigned int random) {
    Matrix_t *bidimen_array = (Matrix_t *)malloc(sizeof(Matrix_t));
    bidimen_array->n = n;
    bidimen_array->m = m;
    int **matrix;
    register size_t i, j;
    matrix = (int **)malloc(bidimen_array->n * sizeof(int*));
    for (i = 0; i < bidimen_array->n; i++) {
        *(matrix + i) = (int *)malloc(bidimen_array->m * sizeof(int));
        if (!random) continue;
        for (j = 0; j < bidimen_array->m; j++) {
            *(*(matrix + i) + j) = rand() % 20; // gera numeros de 0 a 20
        }
    }
    bidimen_array->matrix = matrix;
    return bidimen_array;
}

void destroy(Matrix_t* bidimen_array) {
    register size_t i;
    for (i = 0; i < bidimen_array->n; i++) {
        free(bidimen_array->matrix[i]);
    }
    free(bidimen_array->matrix);
    free(bidimen_array);
}