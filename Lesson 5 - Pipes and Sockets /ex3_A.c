/*
===============================================================================
SO - Lesson 5 - Exercise 3

Pipes FIFO e Sockets

+info: http://unixhelp.ed.ac.uk/CGI/man-cgi?fifo+4

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	
	mode_t fdmode = (S_IRUSR | S_IWUSR); // Permissions of file

	if(mkfifo("/tmp/fifoA", fdmode) == -1){ //media/psf/SO/Aula5
		perror("Error creating fifoA!\n");
		return 0;
	}

	time_t t;
	srand((unsigned) time(&t));

	int randn = rand() % 10; // Generated random number
	int n;

	printf("The generated number was: %d\n", randn);

	int fdA = open("/tmp/fifoA", O_RDONLY, fdmode);
	int fdB = open("/tmp/fifoB", O_WRONLY, fdmode);

	do{
		read(fdA, &n, sizeof(n)); // Response of B

		if(n > randn){
			printf("[Child] Wrong! The number is smaller than attempt.\n");
			n = 1;
		}else if(n < randn){
			printf("[Child] Wrong! The number is bigger than attempt.\n");
			n = -1;
		}else{
			printf("[Child] Yeeh! The number is equal to attempt.\n");
			n = 0;
		}
		write(fdB, &n, sizeof(n)); // Send to B
		
		sleep(1); // Test/Debug

	} while(n!=0); // Until find the number

	close(fdA);
	close(fdB);

	if(unlink("/tmp/fifoA") == -1)
		perror("Failed to remove fifoA!\n");
	
	return 0;
}