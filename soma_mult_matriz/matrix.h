#ifndef MATRIX_H_
#define MATRIX_H_
#include <stdlib.h>
typedef struct matrix {
    int n;
    int m;
    int **matrix;
} Matrix_t;

void print_matrix(Matrix_t *);
void destroy(Matrix_t *);
Matrix_t* generate_matrix(size_t, size_t, unsigned int);
#endif