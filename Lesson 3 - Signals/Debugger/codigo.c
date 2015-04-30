/*
===============================================================================
SO - Lesson 3 - Exercise 1 

GDB Debuger

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>


int main(){

	long i,j;
    double soma;
    double arraysoma[5000];
    double *ponteiro;

    ponteiro=arraysoma;

    for (j=0; j<10000; j+=2){
        
        soma=0;
		for (i=0; i<20000; i++)
	  		soma+=1.0/(i+j);
		ponteiro=&soma;
		ponteiro++;
	}

	for (j=0; j<=5000;j++) //if we put j <= 10000 (forced) we are accessing outside memory array area. This is the problem.
        printf("%f \n",arraysoma[j]);

    sleep(60); // 60 (5 for fast debug)

    printf("Estou pronto para terminar, prima [ENTER] para sair.\n");

    getchar();

	return(0);
}