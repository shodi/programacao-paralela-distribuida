#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../matrix.h"

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

int main(int argc, char **argv) {
    srand(time(1));
    Matrix_t *matrix1, *matrix2, *result;
    matrix1 = generate_matrix(5, 5, 1);
    matrix2 = generate_matrix(5, 5, 1);
    result = multiply(matrix1, matrix2);
    if (result == NULL) return 1;
    print_matrix(result);
    destroy(matrix1);
    destroy(matrix2);
    destroy(result);
    return 0;
}