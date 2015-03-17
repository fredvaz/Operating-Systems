/*
===============================================================================
SO - Lesson 2 - Exercise 3 

	Processes Control

+info: http://linux.die.net/man/2/getpid

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>     
#include <stdlib.h>    
#include <unistd.h>

#include <string.h>
#include <errno.h>


int main(){

	pid_t pid = fork();

	if(pid > 0){
		//
	}else if(pid == 0){
		exit(EXIT_SUCCESS); 
		printf("END\n");
	}else{
		printf("Error edit:[%s]", strerror(errno));
	}
	//We getpid() in First Run (This code it's run by the father process because we close/exit child process)
	printf("I am father, my PID is %d and of my child is %d\n", getpid(), pid);
	printf("I am child, my PID is %d and of my father is %d\n", pid, getpid());
	
	

	return(0);
}
