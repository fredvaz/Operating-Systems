/*
===============================================================================
SO - Lesson 7 - Exercise 1

Threads & Condition Variables

+info: http://en.wikipedia.org/wiki/Thread_(computing)

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void *thread_a(void *arg);
void *thread_b(void *arg);

int main(){

	// Three inputs (They are vectors - adressable)
	int params_A[3] = {10, 20, 30};
	int params_B[3] = {40, 50, 60};
	// Create pointers and allocate dinamyc memory (Recomended) 
	int *ret_A = malloc(3*sizeof(int));
	int *ret_B = malloc(3*sizeof(int));

	// Two Threads
	pthread_t thread_A;
	pthread_t thread_B;

	// Create and execute Threads with Input paraments
	pthread_create(&thread_A, NULL, thread_a, params_A);
	pthread_create(&thread_B, NULL, thread_b, params_B);

	// Wait for termination of Threads and return Output paraments
	pthread_join(thread_A, (void *) &ret_A);
	pthread_join(thread_B, (void *) &ret_B);

	printf("Child threads have died!\n");
	// Print Outputs
	printf("Return A: %d, %d, %d\n", ret_A[0], ret_A[1], ret_A[2]);
	printf("Return B: %d, %d, %d\n", ret_A[0], ret_B[1], ret_B[2]);
	// or (Remember - Add to next adress)
	printf("T - Return A: %d, %d, %d\n", *ret_A,  *(ret_A+1), *(ret_A+2));
	printf("T - Return B: %d, %d, %d\n", *ret_B, *(ret_B+1), *(ret_B+2));


	// Releases allocated memory (for outputs)
	if (ret_A != NULL) 
		//free(ret_A); ??
	if (ret_B != NULL)
		//free(ret_B); ??

	pthread_exit(NULL);

	return 0;
}

void *thread_a(void *arg){
	int *ptr = (int *) arg;
	// Print Inputs
	printf("%d, %d, %d\n", ptr[0], ptr[1], ptr[2]);
	
	// Define Outputs
	ptr[0]=111;
	ptr[1]=222;
	ptr[2]=333;
	
	// Terminate calling thread and return Outputs
	pthread_exit(ptr);
	
	return NULL;
}


void *thread_b(void *arg){
	int *ptr = (int *) arg;
	// Print Inputs
	printf("%d, %d, %d\n", ptr[0], ptr[1], ptr[2]);
	
	// Define Outputs
	ptr[0]=444;
	ptr[1]=555;
	ptr[2]=666;
	
	// Terminate calling thread and return Outputs
	pthread_exit(ptr);
	
	return NULL;
}
