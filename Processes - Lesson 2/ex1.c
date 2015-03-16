#include <sys/types.h> /* pid_t */
#include <stdio.h>     /* printf, perror */
#include <stdlib.h>    /* exit */
#include <unistd.h>    /* _exit, fork */

 
int main(){

  printf("Hello world!\n");

  pid_t pid = fork(); // create a child process

  if (pid == 0){ //quando fork() retorna 0 nós estamos no processo child (copiado)
  	// Code only executed by child process

  	printf("Eu sou o filho!\n");
  	
  }else {
    // When fork() returns a positive number, we are in the parent process
    // and the return value is the PID of the newly created child process.
  	// Code only executed by parent process

  	printf("Eu sou o pai!\n");

  }

   // Code executed by both parent and child.


  return EXIT_SUCCESS;
}

//Nota: Ele cria o child onde pid recebe o PID do processo child logo é != 0 
//pelo que executa "eu sou o pai", só depois de fork() retornar 0 é que entramos
//no processo child e ai ele executa "eu sou o filho"