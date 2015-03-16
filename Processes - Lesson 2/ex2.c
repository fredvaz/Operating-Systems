/*
===============================================================================
SO - Lesson 2 - Exercise 2 

Implementation of "System calls" through "Process Control"

+info: http://en.wikipedia.org/wiki/System_call
+info: http://en.wikipedia.org/wiki/Fork_(system_call)
+info: http://en.wikipedia.org/wiki/Wait_(system_call)
+info: http://en.wikipedia.org/wiki/Exec_(computing)
+info: http://en.wikipedia.org/wiki/Exit_(system_call)

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>
#include <errno.h>

// Note: C does have boolean type, but C99 have
typedef int bool;

#define true 1
#define false 0

char * filepath();
void edit();
void view();
void list();
void delete();


int main(){

	bool exit = false;
	char option = '0'; // Clean memory garbage

	do{
		printf("\n======= MENU =======\n");
		printf("1 - Edit a file\n");
		printf("2 - View a file\n");
		printf("3 - List files\n");
		printf("4 - Remove file\n");
		printf("q - Quit\n");
		
		printf("\nIntroduce one option: ");

		scanf("%c", &option);
		while(getchar() != '\n'); // trick - always repeats until the next character is '\n'

		switch(option){
			case '1': edit(); break;
			case '2': view(); break;
			case '3': list(); break;
			case '4': delete(); break;
			case 'q': exit=true; break;
			default: break;
		}

	}while(!exit);

	return 0;
}

char * filepath(){ 
	// Note: returned is created with automatic storage duration. 
	// We will need to dynamically allocate the memory inside of the function or fill a preallocated buffer provided by the caller.

	char *filepath = malloc(sizeof(char)*20); // 20 size char, como 1 char 1 byte = 20 bytes

	printf("Directory or file: ");
	scanf("%s", filepath);

	return(filepath);
}

void edit(){

	pid_t pid = fork(); // Create child and return PID of child (PPID)
	int status;

	if (pid > 0){ // Code only executed by parent process
		
		wait(&status); // Parent wait until child exit, otherwise the parent and child run together (parent is executed again)

	}else if(pid == 0){ // Code only executed by child process
		
		execl("/usr/bin/pico", "pico", filepath(), NULL); // the machine code, data, heap, and stack of the process are replaced by those of the new program (child)
		printf("Error in execl edit: [%s]", strerror(errno));
		_exit(EXIT_SUCCESS); // Said to be a dead process after it terminates. Must be used because child process can not exit

	}else{ // failed to fork return -1
		
		printf("Error edit:[%s]", strerror(errno));
	}
}

void view(){

	pid_t pid = fork();
	int status;

	if (pid > 0){
		wait(&status);
	}else if(pid == 0){
		execl("/bin/cat", "cat", filepath(), NULL); // The list of arguments must be terminated by a NULL pointer
		printf("Error in execl view: [%s]\n", strerror(errno));
		_exit(1);
	}else{
		printf("Error view:[%s]", strerror(errno));
	}
}

void list(){

	printf("\nList of files:\n");

	pid_t pid = fork();
	int status;

	if (pid > 0){
		wait(&status); 
	}else if(pid == 0){
		execl("/bin/ls", "ls", "-l", NULL);
		printf("Error in execl list!\n");
		_exit(1);
	}else{
		printf("Error list:[%s]", strerror(errno));
	}
}

void delete(){

	pid_t pid = fork();
	int status;

	if (pid > 0){
		wait(&status);
	}else if(pid == 0){
		execl("/bin/rm", "rm", filepath(), NULL);
		printf("Error in execl remove!\n");
		_exit(1);
	}else{
		printf("Error delete:[%s]", strerror(errno));
	}
}