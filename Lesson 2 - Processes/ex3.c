/*
===============================================================================
SO - Lesson 2 - Exercise 3 

	Process Control

+info: http://unixhelp.ed.ac.uk/CGI/man-cgi?wait+2

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>     
#include <stdlib.h>    
#include <unistd.h>

#include <string.h>
#include <errno.h>


int main(){

	pid_t childone, childtwo, pid;
	//Note: We can get pid of father by getpid() in process father
	int i;

	for (i = 0; i < 5; ++i){

		childone = fork();
		childtwo = fork();
		
		if(childone == 0){
			for (int j = 0; j < 10; ++j){
				printf("I am the child one! %d\n", j); //print j differentiate in shell
				sleep(1);
			}
			_exit(EXIT_SUCCESS);

		}else if(childone == -1){
			printf("Error create child one: [%s]", strerror(errno));

		}else if(childtwo == 0){
			for (int j = 0; j < 10; ++j){
				printf("I am the child two! %d\n", j);
				sleep(1);
			}
			_exit(EXIT_SUCCESS);

		}else if(childtwo == -1){
			printf("Error create child two: [%s]", strerror(errno));
		}else{ 
			//Geral case childone > 0 & childtwo > 0
			//jump to here 

			// First Run Father wait. Second Run etc one of child's wait
			for (int j = 0; j < 2; ++j){

				pid = wait(NULL);
				// wait() > 0 meaning  wait  for  the  child  whose process ID is equal to the value of pid

				if(pid == childone && i < 4){
					printf("Relauching child one!\n");
				}else if(pid == childtwo && i < 4){
					printf("Relauching child two!\n");
				}
				else{
					printf("No more relauching!\n");
				}
			}

		}
	}

	return(0);
}