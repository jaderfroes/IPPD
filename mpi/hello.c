#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int size, myRank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size); // descobrir quantos processos
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank); // para saber o id de cada um

    printf("Hello! sou o processo %d de um total de %d\n", myRank, size);
    fflush(stdout); //sincronização para não ter erro nas mensagens
    
    MPI_Finalize();

    return 0;
}

/*
 
*/