#include <stdio.h>
#include <mpi.h>

    /* Exercicio
        processo 0 envia valores para os outros processos, 
        os outros vão multiplicar o valor recebido e devolver
        para o processo 0, que vai somar todos os valores
    */


int main(int argc, char *argv[]){
    
    int size, myRank;
    int valor_inicial, valor_modificado, total, num_proc;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size); // descobrir quantos processos
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank); // para saber o id de cada um

    printf("Hello! sou o processo %d de um total de %d\n", myRank, size);
    fflush(stdout); //sincronização para não ter erro nas mensagens
    
    if(myRank == 0){
        for(nproc = 1; num_proc < size; ++nrpoc){
            valor_inicial = num_proc * 10;
        }
        MPI_SEND();
    }
    else{
        
    }
    

    MPI_Finalize();

    return 0;
}
