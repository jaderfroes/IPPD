#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

typedef struct merge_MPI{
    int num_proc;    
    int rank;
    int *vet;
}mpi_data;

// colocar o subarray da funcao mpi_merge dentro da struct
#define SIZE 10

int *generateRandomIntegers(int *vet);
void printArray(int *vet);
mpi_data *initData();
void initMPI();
void MPI_merge(mpi_data *control_data);

void merge(int vetor[], int comeco, int meio, int fim) {
    
    int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    
    int *vetAux;
    vetAux = (int*)malloc(tam * sizeof(int));

    while(com1 <= meio && com2 <= fim){
        if(vetor[com1] < vetor[com2]) {
            vetAux[comAux] = vetor[com1];
            com1++;
        } else {
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio){  //Caso ainda haja elementos na primeira metade
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {   //Caso ainda haja elementos na segunda metade
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++){    //Move os elementos de volta para o vetor original
        vetor[comAux] = vetAux[comAux-comeco];
    }
    
    free(vetAux);
}

void mergeSort(int vetor[], int comeco, int fim, int rank){
    
    printf("Olá eu sou o processo[%d]\n", rank);

    if (comeco < fim) {
        int meio = (fim+comeco)/2;
        mergeSort(vetor, comeco, meio, rank);
        mergeSort(vetor, meio+1, fim, rank);    
        merge(vetor, comeco, meio, fim);
    }
}

int main(int argc, char *argv[]){


    initMPI();
    mpi_data *control_data = initData();
    MPI_merge(control_data);
    
    if(control_data->rank == 0)
        printArray(control_data->vet);   

    mergeSort(control_data->vet, 0, SIZE-1, control_data->rank);

    finilizeMPI(control_data);
    
    if(control_data->rank == 0)
        printArray(control_data->vet);

    free(control_data->vet);
    free(control_data);

    return 0;
}

int *generateRandomIntegers(int *vet){
    
    int i;

    vet = (int *)malloc(SIZE*sizeof(int));
    srandom(time(NULL));
    for(i = 0; i < SIZE; i++){ //gera SIZE numeros aleatórios
        vet[i] = (int) random() % SIZE; 
                 
    }

    return vet;
}

void printArray(int *vet){
    int i;

    for(i = 0; i < SIZE; i++){
            printf("%d ,", vet[i]);     
    }
    printf("\n");

}

void MPI_merge(mpi_data *control_data){
    
    int subSize = SIZE / control_data->num_proc; // tamanho do vetor particionado
    int *sub_array = malloc(subSize * sizeof(int));

    MPI_Scatter(control_data->vet, subSize, MPI_INT,
    sub_array, subSize, MPI_INT, 0,
    MPI_COMM_WORLD);


}

void initMPI(){
    
    MPI_Init(NULL, NULL);
    return;
}

mpi_data *initData(){
    mpi_data *ret;
    
    ret = malloc(sizeof(mpi_data));

    ret->vet = generateRandomIntegers(ret->vet);

    MPI_Comm_size(MPI_COMM_WORLD, &ret->num_proc); // indica o número de processos envolvidos em um comunicador
    MPI_Comm_rank(MPI_COMM_WORLD, &ret->rank); // Essa função fornece o rank do processo no grupo do comunicador específico      
    
    return ret;

}

void finilizeMPI(control_data){
    MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm);

    MPI_Finalize();
}