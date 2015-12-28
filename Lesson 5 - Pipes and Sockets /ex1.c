/*
===============================================================================
SO - Lesson 5 - Exercise 1

Pipes e Sockets

+info: http://www.tutorialspoint.com/unix_system_calls/pipe.htm

Developer: Frederico Vaz
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){

	// File discriptors
	int fd1[2];
	int fd2[2];

	//Open Pipes and watch errors
	if (pipe(fd1) == -1){
		perror("Error creating pipe 1!\n");
		return 0;
	}
	if (pipe(fd2) == -1){
		perror("Error creating pipe 2\n");
		return 0;
	}

	// Create the child
	pid_t child = fork();

	if (child == 0){ // We are in child

		close(fd1[0]); // Close Read Child 
		close(fd2[1]); // Close Write Child

		int randn_child = rand() % 10; // Generate random number 0 to 9
		int n; // Response

		//printf("[Child] The generated number was: %d\n", randn_child);

		do{
			read(fd2[0], &n, sizeof(n)); // Response of Father Process (attempt number)

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

      		write(fd1[1], &n, sizeof(n)); // Send response to Father Process

		}while(n!=0); // Until number attempt of father equal to number genarated by child

	}else if(child < 0){
		perror("Error creating child process!\n");
	}else{
		// We are in Father. Attempt generated number of child

		close(fd1[1]); // Close Write Father
		close(fd2[0]); // Close Read Father

		// Note: fd1[0] is Read of Child & fd2[1] is Write to Child

		int number_father = 5; // Start attempt number
		int n; // Response

		do{
			printf("[Father] Try to guess the number is: %d\n", number_father);
			write(fd2[1], &number_father, sizeof(number_father)); // Send response (attempt number) to Child Process 
			read(fd1[0], &n, sizeof(n)); // Response of Child Process

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

	return 0;
}