#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARR_SIZE 8 /* Necessariamente potencia de 2 */

// gcc max_arr_balanced_three.c -o teste -fopenmp -lm

int* generate_array(size_t size) {
    int* arr = (int *) malloc(size * sizeof(int));
    register unsigned int i = 0;
l1: if (i < size) {
        arr[i] = rand() % 20;
        i++;
        goto l1;
    }
    return arr;
}

void print_array(int* array, size_t size) {
    register unsigned int i = 0;
l1: if (i < size) {
        printf("%d\n", array[i]);
        i++;
        goto l1;
    }
}

int max(int a, int b) {
    return a >= b ? a : b;
}

int get_max_array(int* array) {

    if (array == NULL) return -1;
    int* array_aux = (int *)malloc(ARR_SIZE * 2 * sizeof(int));

    register unsigned int i;
    #pragma omp parallel private(i)
    {
        #pragma omp for
        for (i = 0; i < ARR_SIZE; i++) {
            array_aux[ARR_SIZE + i] = array[i];
        }
    }

    register int j, w;
    for (j = (int)log(ARR_SIZE); j >= 0; j--) {
        int x = (int)pow(2, j);
        int y = (int)pow(2, j + 1);
        #pragma omp parallel
        {
            #pragma omp for
            for (w = x; w <= y - 1; w++) {
                array_aux[w] = max(array_aux[2 * w], array_aux[(2 * w) + 1]);
            }
        }
    }

    int max_value = array_aux[1];
    free(array_aux);

    return max_value;
}

int main(int argc, char **argv) {

    int* arr = generate_array(ARR_SIZE);
    int max = get_max_array(arr);
    printf("Array's Max Value: %d\n", max);
    free(arr);
    return 0;

}