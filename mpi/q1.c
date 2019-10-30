#include <stdio.h>
#include <stdlib.h>
#include <mpi.h> 
#include <time.h>
#include <unistd.h>
#include <assert.h>

/*
Executar e compilar:
        $mpicc code.c -o out
        $mpirun -n 5 ./out
*/

int main(int argc, char const *argv[]){

	int rank, num_proc, limite, i, j; 

    MPI_Init(NULL, NULL);  // Inicializa o ambiente de execução MPI
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);  // Retorna o tamanho do grupo associado a um comunicador
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // determina a classificação do processo no comunicador
	
    int flag=0;
    limite = 40;

    int fatia = limite / num_proc;
    int inicio = (rank * fatia);
    if(rank==0)
        inicio+=1; //evitar divisão por 0
    int fim = inicio + fatia -1;     
	int k;

    int *vec = (int *)malloc(limite * sizeof(int));
    int *sub_vec = (int *)malloc(fatia *sizeof(int));

    for (i = 0; i < limite; i++){
        vec[i] = i;
    }
    
    MPI_Scatter(vec, fatia, MPI_INT, sub_vec, fatia, MPI_INT, 0, MPI_COMM_WORLD);

    // caluclo dos primos entre 1 e limite
    for(i = 0; i < fatia; ++i){ 
    	for(j = 0; j <= sub_vec[i]; ++j){ //testa os divisores desse numero
            if(j != 0){    
                if(sub_vec[i] % j == 0){ //se ele divide por algum numero diferente dele e de 1
                    flag+= 1;
                }
            }
    	}
    	if (flag <= 2){ // se ele só é divisível por ele e por 1
    		//
    	}
    	else{ // se nao eh primo
    		sub_vec[i] = -1;
    	}
    	flag = 0;
    }

    MPI_Gather(sub_vec, fatia, MPI_INT, vec, fatia, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Sou o processo %d\n", rank);
    
    
    if(rank == 0){
	    for (k = 0; k < limite; ++k){
	    	printf("%d\n", vec[k]);
	    }
	}

    MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize(); 
	return 0;
}