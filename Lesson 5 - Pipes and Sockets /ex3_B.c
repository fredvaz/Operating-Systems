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
#include <unistd.h>

int main(){
	
	mode_t fdmode = (S_IRUSR | S_IWUSR);
	if(mkfifo("/tmp/fifoB", fdmode) == -1){
		perror("Error creating fifoB!\n");
		return 0;
	}

	int randn = 5; // Vamos começar a adivinhar a meio do intervalo de 0 a 9
	int n;

	int fdA = open("/tmp/fifoA", O_WRONLY, fdmode);
	int fdB = open("/tmp/fifoB", O_RDONLY, fdmode);

	do{
		write(fdA, &randn, sizeof(randn)); // Send to A
		read(fdB, &n, sizeof(n)); // Response of A

		if(n == 1)
			randn--;
		else if(n == -1)
			randn++;
		else if(n != 0)
			perror("Error occured in p3p!\n");
	} while(n != 0);

	printf("\nThe guess number was: %d\n", randn);

	close(fdA);
	close(fdB);

	if(unlink("/tmp/fifoB") == -1)
		perror("Failed to remove fifoB!\n");
	
	return 0;
}