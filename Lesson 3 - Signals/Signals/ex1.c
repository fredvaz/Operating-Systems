/*
===============================================================================
SO - Lesson 3 - Exercise 1 

Signals

+info: http://en.wikipedia.org/wiki/Unix_signal

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>   
#include <stdlib.h>  
#include <signal.h> 


void process1();
void process2();

int main() {
     
     signal(SIGINT, process1);
     // Wait for signal Ctrl-C (type SIGINT) for execute function process1()
     //1º parament is the signal recieved from process
     //2º parament is the function to be execute

     signal(SIGQUIT, process2);
     // Ctrl-\ The signal is run by OS

     // Program - process
     while(1){
     	sleep(1);
     	printf("I'm running.\n");
     }

	return(0);
}

void process1(){

	 /*--------------------------------------
     NOTE some versions of UNIX will reset
     signal to default after each call. So for
     portability reset signal each time */
     signal(SIGINT, process1);
     /*------------------------------------*/
     printf("You have pressed ctrl-c\n");

    //Attetion ! Whithout exit
}

void process2(){

	signal(SIGINT, process2);

	printf("Good Bye!\n");
	exit(0); //Terminate process
}

