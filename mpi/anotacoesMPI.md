# MPI Anotações

## Primitivas

### MPI_Init : 
    inicialização para o ambiente MPI

### MPI_Comm_size :
    retorna o número de processadores

### MPI_Comm_rank : 
    retorna o "rank" (índice, identificador) do processador

### MPI_Send : 
    envia uma mensagem. Ele envia mensagem mesmo q o recepetor não esteja executando Recv(Caso tamanho seja menor que o limite). O MPI implementa um buffer que armazena a mensagem. MPI é envio de dados BLOQUEANTE. Caso seja > limite, o emissor aguarda o receptor sincronizar pra receber o dado.

### MPI_Recv : 
    recebe uma mensagem

### MRP_Finilize : 
    sai do ambiente MPI

### Tipos básicos no MPI
    MPI_CHAR, MPI_SHORT, MPI_INT, MPI_LONG, MPI_FLOAT, MPI_DOUBLE, MPI_LONG_DOUBLE, MPI_BYTE, MPI_PACKED(mandar structs inteiras).


### Executar
    Baixar a biblioteca open-mpi;
    ```
    $mpicc code.c -o out
    $mpirun -n 5 ./out
    ```
    -n : número de processos.