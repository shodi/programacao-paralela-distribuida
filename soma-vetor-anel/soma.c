#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    int *arr;
    int TAG = 1;
    int TAG_2 = 2;
    int qtd_elementos;

    MPI_Init(NULL, NULL);
    // Get the number of processes
    int qtd_processador;
    MPI_Comm_size(MPI_COMM_WORLD, &qtd_processador);

    // Get the rank of the process
    int id_processador;
    MPI_Comm_rank(MPI_COMM_WORLD, &id_processador);

    if (id_processador == 0) {
        arr = (int *) malloc(qtd_elementos * sizeof(int));
        scanf("%d", &qtd_elementos);
        for (int count = 0; count < qtd_elementos; count++) *(arr + count) = 1;
        for (int processor_id = 1; processor_id <= qtd_processador - 1; processor_id++) {
            MPI_Send(arr, qtd_elementos, MPI_INT, processor_id, TAG, MPI_COMM_WORLD);
            MPI_Send(&qtd_elementos, 1, MPI_INT, processor_id, TAG_2, MPI_COMM_WORLD);
        }
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    if (id_processador != 0) {
        MPI_Recv(&qtd_elementos, 1, MPI_INT, 0, TAG_2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("qtd_elementos: %d\n", qtd_elementos);
        arr = (int *) malloc(qtd_elementos * sizeof(int));
        MPI_Recv(arr, qtd_elementos, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    int s = 0, z = 0;
    for (int i = (id_processador) * (qtd_elementos / qtd_processador); i <= (id_processador + 1) * (qtd_elementos / qtd_processador) - 1; i++) {
        z += arr[i];
    }
    printf("soma: %d\tprocessador: %d\n", z, id_processador);
    if (id_processador == 0) {
        s = 0;
    } else {
        MPI_Recv(&s, 1, MPI_INT, id_processador - 1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    s += z;
    int next_processor = id_processador == qtd_processador - 1 ? 0 : id_processador + 1;
    MPI_Send(&s, 1, MPI_INT, next_processor, TAG, MPI_COMM_WORLD);
    
    if (id_processador == 0) {
        MPI_Recv(&s, 1, MPI_INT, qtd_processador - 1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Soma: %d\n", s);
    }
    free(arr);

    MPI_Finalize();
}