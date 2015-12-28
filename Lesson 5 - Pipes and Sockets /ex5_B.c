/*
===============================================================================
SO - Lesson 5 - Exercise 5

Sockets

+info: http://gnosis.cx/publish/programming/sockets.html
+info: http://en.wikipedia.org/wiki/Berkeley_sockets
+info: http://en.wikipedia.org/wiki/Unix_domain_socket
+info: http://man7.org/linux/man-pages/man2/socket.2.html

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
	
	int sd; // Client
   	struct sockaddr_un serveraddr;

   	// Create Socket
	sd = socket(AF_UNIX, SOCK_STREAM, 0); // Definitions

	if(sd < 0){
		perror("Error creating client socket!\n");
		return 0;
	}

	int randn = 5; // Attempt
	int n;

	// Address
	serveraddr.sun_family = AF_UNIX;
	// We can bind a socket to a file
	strcpy(serveraddr.sun_path, "/tmp");

	// Connect to Server
   	if(connect(sd, (struct sockaddr *) &serveraddr, SUN_LEN(&serveraddr)) < 0){
        perror("Error connecting client socket!\n");
        return 0;
    }

	do{
		// Send data to Server
    	if(send(sd, &randn, sizeof(randn), 0) < 0){
         	perror("Error sending data in client server!\n");
         	return 0;
      	}
      	// Receiving data from Server
        if(recv(sd, &n, sizeof(n), 0) < 0){
        	perror("Error receiving data in client server!\n");
           	return 0;
        }

		if(n == 1)
			randn--;
		else if(n == -1)
			randn++;
		else if(n != 0)
			perror("Error occured in client server!\n");

	} while(n != 0);

	printf("\nThe guess number was: %d\n", randn);

	close(sd); // Close Client


	return 0;
}