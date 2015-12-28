/*
===============================================================================
SO - Lesson 6 - Exercise 4

Shared Memory & Semaphores POSIX:SEM

+info: http://en.wikipedia.org/wiki/Semaphore_(programming)

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <time.h>

int main(){

	// Identifier Shared Memory with size 4
	int shmid = shmget(IPC_PRIVATE, 4, S_IRUSR | S_IWUSR); 

	if (shmid==-1){
		perror("Error creating shared memory!\n");
		return 0;
	}
	// Attach address for shared block memory (Mapping)
	// NULL -> system chooses unused address (Recommended)
	int *pointer = (int *) shmat(shmid, NULL, 0); 

	// Create Semaphore
	sem_t *sem_child = NULL, *sem_father = NULL;
	// Tabled in memory
	sem_child = (sem_t *) (pointer+1);
	sem_father = (sem_t *) (sem_child+1);

	sem_init(sem_child, 1, 0);
	sem_init(sem_father, shmid, 0);

	// Create the child
	pid_t child = fork();

	if (child==0){
		
		int randn_child = rand() % 10; // Generate random number 0 to 9
		int n; // Response

		do{ // Response of Child Process
			
			/*==============================*/
			sem_wait(sem_father);
			n = *pointer;
			/*==============================*/

			if(n > randn_child){
				printf("[Child] Wrong! The number is smaller than attempt.\n");
				n = 1;
			}
			else if(n < randn_child){
				printf("[Child] Wrong! The number is bigger than attempt.\n");
				n = -1;
			}else{
				printf("[Child] Yeeh! The number is equal to attempt.\n");
				n = 0;
			}
      		/*==============================*/
      		*pointer = n;
      		sem_post(sem_child);
      		/*==============================*/

		}while(n!=0); // Until number attempt of father equal to number genarated by child
	}else if(child < 0){
		perror("Error creating child process!\n");
	}else{
		// We are in Father. Attempt generated number of child

		int number_father = 5; // Start attempt number
		int n; // Response

		do{
			printf("[Father] Try to guess the number is: %d\n", number_father);
			
			/*==============================*/
			*pointer = number_father;
			sem_post(sem_father);

			sem_wait(sem_child);
			n = *pointer;
			/*==============================*/

			// Attempt if child responde is < or > and try other number
			if(n == 1)
				number_father--; // <
			else if (n == -1)
				number_father++; // >
			else if(n != 0)
				perror("Error occured in father!\n");

		}while(n!=0); 

		printf("[Father] The guess number was: %d\n", number_father);
	}

	shmdt(pointer); // Remove  shared memory 

	return 0;
}