/*
===============================================================================
SO - Lesson 7 - Exercise 4

Threads & Mutex

+info: http://en.wikipedia.org/wiki/Thread_(computing)

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>


static pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
 
void *thread_a(void *arg);
void *thread_b(void *arg);

int main(){
	
	// Identifier Shared Memory with size of int
	int shmid = shmget(IPC_PRIVATE, sizeof(int), S_IRUSR | S_IWUSR); 

	if (shmid==-1){
		perror("Error creating shared memory!\n");
		return 0;
	}
	// Note: Next errors are ignored because i want

	// Attach address for shared block memory (Mapping)
	// NULL -> system chooses unused address (Recommended)
	int *pointer = (int *) shmat(shmid, NULL, 0); 

	// Create Mutexes
	pthread_mutex_lock(&lock1);
	pthread_mutex_lock(&lock2);

	// Two Threads
	pthread_t thread_1, thread_2;

	// Create and execute Threads with Input paraments
	pthread_create(&thread_1, NULL, thread_a, pointer);
	pthread_create(&thread_2, NULL, thread_b, pointer);

	// Wait for termination of Threads and wihout return Output paraments
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	printf("Terminating process...\n");

	pthread_mutex_destroy(&lock1);
	pthread_mutex_destroy(&lock2);
	shmctl(shmid, IPC_RMID, 0);
	pthread_exit(NULL);

	return 0;
}

void *thread_a(void *arg){

	int number_father = 5; // Start attempt number
	int response;

	do{
		printf("[Father] Try to guess the number is: %d\n", number_father);
		
		/*==============================*/
		*((int *) arg) = number_father;
		pthread_mutex_unlock(&lock2); // Go

		pthread_mutex_lock(&lock1); // Wait
		response = *((int *) arg);
		/*==============================*/

		// Attempt if child responde is < or > and try other number
		if(response == 1)
			number_father--; // <
		else if (response == -1)
			number_father++; // >
		else if(response != 0)
			perror("Error occured in father!\n");
		sleep(1); // Slow Debug

	}while(response!=0); 

	printf("[Father] The guess number was: %d\n", number_father);

	pthread_exit(NULL);
	return NULL;
}

void *thread_b(void *arg){


	int randn_child = rand() % 10; // Generate random number 0 to 9
	int response;

	do{ 
		/*==============================*/
		pthread_mutex_lock(&lock2); //Wait
		response = *((int *) arg); // Cast Simple
		/*==============================*/

		if(response > randn_child){
			printf("[Child] Wrong! The number is smaller than attempt.\n");
			response = 1;
		}
		else if(response < randn_child){
			printf("[Child] Wrong! The number is bigger than attempt.\n");
			response = -1;
		}else{
			printf("[Child] Yeeh! The number is equal to attempt.\n");
			response = 0;
		}
  		/*==============================*/
  		*((int *) arg) = response;
  		pthread_mutex_unlock(&lock1); // Go
  		/*==============================*/
  		sleep(1); // Slow Debug
	}while(response!=0); // Until number attempt of Thread_2 equal to number genarated by Thread_1 
	
	pthread_exit(NULL);
	return NULL;
}



