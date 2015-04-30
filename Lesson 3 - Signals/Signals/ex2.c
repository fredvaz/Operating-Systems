/*
===============================================================================
SO - Lesson 3 - Exercise 2 

Signals

+info: http://en.wikipedia.org/wiki/Unix_signal
+info: http://people.cs.pitt.edu/~alanjawi/cs449/code/shell/UnixSignals.htm
+info: http://www.delorie.com/gnu/docs/glibc/libc_481.html

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>   
#include <stdlib.h>  
#include <signal.h> 

#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

pid_t pid;

void kill_child();
void kill_both();

int main(){

	// Create child process (Copy of father process)
	pid = fork();

	// Wait for signals Ctrl-C & Ctrl-\ (). The signal is run by OS
	signal(SIGINT, kill_child);
	signal(SIGQUIT, kill_both);

	// Program - process
	while(1){
		sleep(1);
		printf("I'm running. My PID is %d.\n", getpid());
	}

	// Both process (Father and child) are running as required in exercise
	// Otherside we must use wait()
	return(0);
}

void kill_child(){

	if(pid == 0){ // We are in child process
		printf("I am the child process %d. Bye Bye!\n", getpid());
		signal(SIGUSR1, SIG_IGN); 
		// Safeguard that ignore other Signals are sent to a process (like Ctrl-\)

	}else if(pid > 0){ // We are in father process

		kill(pid, SIGTERM); // The parent process must be Terminat child
		wait(NULL); // wait for exit child (The wait() function returns child pid on success)
		pid = fork(); // Create new child process

	}else{ 
		//error 
		printf("Error creating child:[%s]", strerror(errno));
	}
}

void kill_both(){

	if(pid == 0){ // We are in child process
		printf("I am the child process %d. Bye Bye!\n", getpid());
		exit(0); // Terminate process

	}else if(pid > 0){ // We are in father process
		
		wait(NULL);
		printf("I am the father process %d. The End of program!\n", getpid());
		exit(0); 

	}else{ 
		//error 
		printf("Error creating child:[%s]", strerror(errno));
	}
}