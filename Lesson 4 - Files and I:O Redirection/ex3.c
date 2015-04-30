/*
===============================================================================
SO - Lesson 4 - Exercise 2

Files and I/O Redirection

+info: http://en.wikipedia.org/wiki/File_descriptor
+info: http://man7.org/linux/man-pages/man2/open.2.html

Developer: Frederico Vaz
===============================================================================
*/

#include <signal.h> // Libarie for manipulate signals
#include <stdio.h>  // "        "  operations of I/O
#include <stdlib.h> // "        "  allocation of memory (malloc, calloc), control of process(abort, exit)
#include <sys/stat.h> // "		 " Redirection E/S
#include <fcntl.h>
#include <time.h> // Clock


#define NMAX 10000000 // Int 8 Bytes

void write_func(int nbytes);

int main(){

	clock_t t;
	int i;

	for (i = 1; i < NMAX; i*=2){ // Progressive N*Bytes 

		t = clock(); // Inicial Time
		write_func(i);
		t = clock() - t; // Final Time
		printf("Time is: %f  N bytes: %d\n", (double)t/CLOCKS_PER_SEC, i);
	}

	return(0);
}

void write_func(int nbytes){

	mode_t fdmode = (S_IRUSR | S_IWUSR); // Permissions of acess at file 
	int aux_f = open("test_func.dat", O_CREAT | O_WRONLY, fdmode); // Also creates the file

	if (aux_f != -1){

		int i = 0;

		for (i = 0; i < NMAX/nbytes; i++){ // Write N*Byte by N*Byte 
			write(aux_f, &nbytes, sizeof(nbytes));
		}
		close(aux_f);

	}else{
		perror("Error opening the file!\n");
	}
}







