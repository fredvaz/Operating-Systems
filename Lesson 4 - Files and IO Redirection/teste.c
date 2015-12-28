#include <signal.h> //biblioteca para manipular sinais
#include <stdio.h>  //    "        "  operações de entrada e saída
#include <stdlib.h> //    "        "  alocação de memória(malloc, calloc), controlo de processos(abort, exit), nºs aleatórios 
#include <sys/stat.h>
#include <fcntl.h>

int main (){
  int counter=0;
  int test;

while(1){ //ciclo infinito

	test=open("/tmp/teste",O_RDONLY); //abre ficheiro zero para leitura

    	if(test==-1){
     		printf("Limite de ficheiros abertos atingido! Foram abertos %d \n",counter);
     		return(0);
    	}

    	else
	     counter++;

}
	return(0);
}
