#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix {
    int n;
    int m;
    int **matrix;
} Matrix_t;

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

Matrix_t* multiply(Matrix_t *bidimen_array1, Matrix_t *bidimen_array2) {
    Matrix_t* result;
    int **matrix1, **matrix2;
    matrix1 = bidimen_array1->matrix;
    matrix2 = bidimen_array2->matrix;
    // Não é possivel fazer a multiplicação de matriz caso a quantidade de colunas
    // da primeira matriz seja diferente do número de linhas da segunda matriz
    if (bidimen_array1->m != bidimen_array2->n) return NULL;
    result = generate_matrix(bidimen_array1->n, bidimen_array2->m, 0);

    register unsigned int i, j, k;
    #pragma omp parallel for private(i, j, k)
    for (i = 0; i < bidimen_array1->n; i++) {
        for (j = 0; j < bidimen_array2->m; j++) {
            result->matrix[i][j] = 0;
            for (k = 0; k < bidimen_array2->n; k++) {
                result->matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

void destroy(Matrix_t* bidimen_array) {
    register size_t i;
    for (i = 0; i < bidimen_array->n; i++) {
        free(bidimen_array->matrix[i]);
    }
    free(bidimen_array->matrix);
    free(bidimen_array);
}

int main(int argc, char **argv) {
    Matrix_t *matrix1, *matrix2, *result;
    matrix1 = generate_matrix(5, 5, 1);
    matrix2 = generate_matrix(5, 5, 1);
    result = multiply(matrix1, matrix2);
    print_matrix(result);
    destroy(matrix1);
    destroy(matrix2);
    destroy(result);
    return 0;
}