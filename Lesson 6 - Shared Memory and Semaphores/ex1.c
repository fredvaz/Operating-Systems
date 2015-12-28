/*
===============================================================================
SO - Lesson 6 - Exercise 1

Shared Memory & Semaphores

+info: http://en.wikipedia.org/wiki/Shared_memory_(interprocess_communication)
+info: http://en.wikipedia.org/wiki/Semaphore_(programming)

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>//inter-process comunication
#include <sys/shm.h>//shared memory
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "semlib.c"


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
	int semid = sem_create(2,0);

	if (semid==-1){
		perror("Error creating semaphores!\n");
		return 0;
	}

	// Create the child
	pid_t child = fork();

	if (child==0){
		
		int randn_child = rand() % 10; // Generate random number 0 to 9
		int n; // Response

		do{ // Response of Child Process
			
			/*==============================*/
			sem_wait(semid, 1);
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
      		sem_signal(semid,0);
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
			sem_signal(semid,1);

			sem_wait(semid, 0);
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

	sem_rm(semid); // Close semaphore

	return 0;
}