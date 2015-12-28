/*
===============================================================================
SO - Lesson 4 - Exercise 1 

Files and I/O Redirection

+info: http://en.wikipedia.org/wiki/File_descriptor
+info: http://man7.org/linux/man-pages/man2/open.2.html

Developer: Frederico Vaz
===============================================================================
*/

#include <signal.h> // Libarie for manipulate signals
#include <stdio.h>  //    "        "  operations of I/O
#include <stdlib.h> //    "        "  allocation of memory (malloc, calloc), control of process(abort, exit)
#include <sys/stat.h>
#include <fcntl.h>

int main(){

	int counter = 0;

	while(1){

		if (open("/tmp/text.txt", O_RDONLY) == -1){ // Open file read only
			
			printf("The open file limit is: %d\n", counter);
			return(0); // Terminate
		}
		counter++;
	}
	
	return 0;
}