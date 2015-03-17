/*
===============================================================================
SO - Lesson 2 - Exercise 1

Implementation of fork() The obtained result is as expected? Why?

+info: http://en.wikipedia.org/wiki/Fork_(system_call)
+info: http://en.wikipedia.org/wiki/Exit_(system_call)

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>     
#include <stdlib.h>    
#include <unistd.h> 

 
int main(){

  printf("Hello world!\n");

  pid_t pid = fork(); // create a child process

  if (pid == 0){ //When fork() return 0 we are in process child
  	
    // Code only executed by child process
    for(int i = 1; i <= 100; i++)
      printf("I am the child process!\n");
    exit(EXIT_SUCCESS);
  	
  }else if(pid == -1){

    printf("Failed to create child process!\n");

  }else{
    // When fork() returns a positive number, we are in the parent process
    // and the return value is the PID of the newly created child process.
    // Code only executed by parent process
    for(int i = 1; i <= 100; i++)
      printf("I am the father process!\n");
  }

   // Code executed by both parent and child.

  return EXIT_SUCCESS;
}