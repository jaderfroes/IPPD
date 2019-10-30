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


    int * vec = NULL;
    if(rank == 0){
        vec = malloc(fatia * num_proc * sizeof(int)); // vetor original
    }
    int * sub_vec = malloc(fatia * sizeof(int));
    assert(sub_vec != NULL);
    
    MPI_Scatter(vec, fatia, MPI_INT, sub_vec, fatia, MPI_INT, 0, MPI_COMM_WORLD);
    //printf("processo[%d] -> ini = %d, fim %d\n", rank, inicio, fim);

    // caluclo dos primos entre 1 e limite

    int * sub_primo = (int *)malloc(fatia * sizeof(int));
    for(i = inicio; i < fim; ++i){ 
    	for(j = 2; j < limite; ++j){ //testa os divisores desse numero
    		if((i % j == 0) && (i != j)){ //se ele divide por algum numero diferente dele e de 1
    			flag = 1;
    		}
    	}
    	if (flag == 0){ // se ele só é divisível por ele e por 1
    		sub_primo[i] = i;
    	}
    	else{ // se nao eh primo
    		sub_primo[i] = -1;
    	}
    	flag = 0;
    }

    int *primos = NULL;
    if(rank == 0){
        primos = (int *)malloc(limite * sizeof(int));
        assert(primos != NULL);
        primos [0] = -1;
    }
    printf("Sou o processo %d\n", rank);
    MPI_Gather(sub_primo, fatia, MPI_INT, primos, fatia, MPI_INT, 0, MPI_COMM_WORLD);
    
    if(rank == 0){
	    for (k = 0; k < limite; ++k){
	    	printf("%d\n", primos[k]);
	    }
	}

    MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize(); 
	return 0;
}