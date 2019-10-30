#include <stdio.h>
#include <stdlib.h>
//#include <omp.h>
//#include <time.h>
//#include <unistd.h>

int main(int argc, char const *argv[]){

    int n = 40, i, j, flag = 0;

    for(i = 2; i < n; ++i){ // numero que passara pelo teste de primo   
        flag = 0;
        for(j = 2; j < n; ++j){ // testa tentando dividir (mod) pra ver se eh primo
            if(i % j == 0 && i != j){
                flag = 1;
            }
        }
        if(flag == 1){
            flag = 0;
        }
        else{
            printf("%d\n", i);
        }
    }
        
    return 0;
}
