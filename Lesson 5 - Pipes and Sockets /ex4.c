/*
===============================================================================
SO - Lesson 5 - Exercise 4

Sockets

+info: http://gnosis.cx/publish/programming/sockets.html
+info: http://en.wikipedia.org/wiki/Berkeley_sockets
+info: http://pubs.opengroup.org/onlinepubs/9699919799/functions/socketpair.html
+info: http://stackoverflow.com/questions/11461106/socketpair-in-c-unix

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(){
	
	int sockets[2]; // Pair of Sockets one to Father and one to Child

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0){ // Now you have two socket file descriptors (two ends of a single pipe)
		perror("Error creating socket pair!\n");
		return 0;
	}
	// You can use socketpair only where you create both processes

	pid_t child = fork();

	if (child==0){ // We are in Child
		close(sockets[0]); // Close Socket Father

		int randn_child = rand() % 10; // Generated random number 
		int n;

		do{

			read(sockets[1], &n, sizeof(n)); // Response of Father

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

		}while(n!=0);

		close(sockets[1]); // Close Socket Child

	}else if(child < 0)
		perror("Error creating child!\n");
	else{ // We are in Father
		close(sockets[1]); // Close Socket Child

		int randn = 5; // First Attempt
		int n;

		do{
			write(sockets[0], &randn, sizeof(randn)); // Send to Child
			read(sockets[0], &n, sizeof(n)); // Response of Child

			if(n == 1)
				randn--;
			else if(n == -1)
				randn++;
			else if(n != 0)
				perror("Error occured in father!\n");

		} while(n != 0);

		printf("The guess number was: %d\n", randn);

		close(sockets[0]); // Close socket Father
	}

	return 0;
}