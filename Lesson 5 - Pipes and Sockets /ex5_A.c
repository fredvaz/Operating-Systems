/*
===============================================================================
SO - Lesson 5 - Exercise 5

Sockets

+info: http://gnosis.cx/publish/programming/sockets.html
+info: http://en.wikipedia.org/wiki/Berkeley_sockets
+info: http://en.wikipedia.org/wiki/Unix_domain_socket
+info: http://man7.org/linux/man-pages/man2/socket.2.html
+info: http://man7.org/linux/man-pages/man2/listen.2.html

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

int main(){
	
	int sdA, sdB; // Server and client
	struct sockaddr_un serveraddr;

	// Create Socket
	sdA = socket(AF_UNIX, SOCK_STREAM, 0); // Definitions

	if (sdA < 0){
		perror("Error creating server socket!\n");
		return 0;
	}

	int randn = rand() % 10; // Generated random number 
	int n;

	printf("The generated number was: %d\n", randn);

	// Address
	serveraddr.sun_family = AF_UNIX;
	// We can bind a socket to a file
	strcpy(serveraddr.sun_path, "/tmp");

	// Start Server
	if(bind(sdA, (struct sockaddr *) &serveraddr, SUN_LEN(&serveraddr)) < 0){
		perror("Error start server socket!\n");
		return 0;
	}
	// Server stay Listing
	if(listen(sdA, 10) < 0){ // 10 is max of connections
		perror("Error listening server socket!\n");
		return 0;
	}
	// Accepeting Client
	sdB = accept(sdA, NULL, NULL);
	if(sdB < 0){
		perror("Error accepting client socket!\n");
		return 0;
	}

	do{
      	// Receiving data from Client
      	if(recv(sdB, &n, sizeof(n), 0) < 0){
         	perror("Error receiving data in server socket!\n");
        	return 0;
      	}

		if(n > randn)
			n = 1;
		else if(n < randn)
			n = -1;
		else
			n = 0;

		// Sending data to Client
      	if(send(sdB, &n, sizeof(n), 0) < 0){
         	perror("Error sending data in server socket!\n");
         	return 0;
      	}
	} while(n!=0);

	close(sdA); // Close Server
	close(sdB); // Close Client
	unlink("/tmp"); // Delete server file


	return 0;
}