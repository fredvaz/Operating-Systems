/*
===============================================================================
SO - Lesson 6 - Exercise 3

Shared Memory & Semaphores POSIX:XSI

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
#include <signal.h>
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
	struct sembuf sbuf;
	sbuf.sem_flg = 0;

	int semid = semget(IPC_PRIVATE, 2, 0777 | IPC_CREAT);

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
			sbuf.sem_op = -1; // Wait signal
			sbuf.sem_num = 0; // First Semaphore
			semop(semid, &sbuf, 1); 
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
      		sbuf.sem_op = 1; // Send signal
      		sbuf.sem_num = 1; // Second Semaphore
      		semop(semid, &sbuf, 1);
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
			sbuf.sem_op = 1; // Send signal
			sbuf.sem_num = 0; // First Semaphore
			sem_op(semid, &sbuf, 1); 

			sbuf.sem_op = -1; // Wait signal (Block Process)
			sbuf.sem_num = 1; // Second Semaphore
			sem_op(semid, &sbuf, 1); 
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

	// Clean UP
	semctl(semid, 0, IPC_RMID); // Immediately remove semaphore
	if(pointer != NULL)
		shmdt(pointer); // Remove  shared memory 
	shmctl(shmid, IPC_RMID, 0); // Mark memory region as destroyed

	return 0;
}