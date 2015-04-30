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


#define NMAX 100000000 // MACRO


void write_a();
void write_b1();
void write_b2();

int main(){

	clock_t t;

	//write_a();
	//write_b1();

	t = clock();
	write_b1();
	t = clock() - t;

	printf("Time is: %f\n", (double)t/CLOCKS_PER_SEC);

	//execl("/usr/bin/time", "time", "-p", "date", NULL); // not working

	return 0;
}
// One by One 
void write_a(){

	mode_t fdmode = (S_IRUSR | S_IWUSR); // Permissions of acess at file 
	int aux_f = open("test_a.dat", O_CREAT | O_WRONLY, fdmode); // Also creates the file

	if (aux_f != -1){

		int i, aux_i = 5; 

		for (i = 0; i < NMAX; i++){ // Note: C - for (int i = 0) not correct (loop initial declarations are only allowed in C99 mode)
			write(aux_f, &aux_i, sizeof(aux_i));
		}
		close(aux_f);

	}else{
		perror("Error opening the file!\n");
	}
}

// Block of 512
void write_b1(){

	mode_t fdmode = (S_IRUSR | S_IWUSR); // Permissions of acess at file 
	int aux_f = open("test_b1.dat", O_CREAT | O_WRONLY, fdmode); // Also creates the file

	if (aux_f != -1){

		int i, aux_i[512];

		for (i = 0; i < 512; ++i){ 
			aux_i[i] = i;
		}

		for (i = 0; i < (NMAX/512)+0.5; i++){ // Note: C - for (int i = 0) not correct (loop initial declarations are only allowed in C99 mode)
			write(aux_f, aux_i, sizeof(aux_i));
		}
		close(aux_f);

	}else{
		perror("Error opening the file!\n");
	}
}

// Block of 4096
void write_b2(){

	mode_t fdmode = (S_IRUSR | S_IWUSR); // Permissions of acess at file 
	int aux_f = open("test_b2.dat", O_CREAT | O_WRONLY, fdmode); // Also creates the file

	if (aux_f != -1){

		int i, aux_i[4096];

		for (i = 0; i < 512; ++i){ 
			aux_i[i] = i;
		}

		for (i = 0; i < (NMAX/4096)+0.5; i++){ // Note: C - for (int i = 0) not correct (loop initial declarations are only allowed in C99 mode)
			write(aux_f, aux_i, sizeof(aux_i));
		}
		close(aux_f);

	}else{
		perror("Error opening the file!\n");
	}
}

