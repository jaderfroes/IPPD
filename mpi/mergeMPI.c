#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define SIZE 10

int num_proc, rank;



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

void mergeSort(int vetor[], int comeco, int fim){
    printf("Olá eu sou o processo[%d]\n", rank);
    if (comeco < fim) {
        int meio = (fim+comeco)/2;

        if(rank % 2 == 0){ // se rank do processo é par
            mergeSort(vetor, comeco, meio);
        }
        else{
            mergeSort(vetor, meio+1, fim);
        }
        
        
        merge(vetor, comeco, meio, fim);
    }
}

int main(int argc, char *argv[]){

    int *vet;
    int i;
       
    vet = malloc(SIZE*(sizeof(int)));
    srandom(time(NULL));   


    for(i = 0; i < SIZE; i++){
        vet[i] = (int) random() % SIZE; 
        printf("%d, ", vet[i]);     
    }

    printf("-----------\n");

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    mergeSort(vet, 0, SIZE);

    MPI_Finalize();

    for(i = 0; i < SIZE; i++){
        printf("%d ,", vet[i]);     
    }
 
    printf("\n");

    return 0;
}