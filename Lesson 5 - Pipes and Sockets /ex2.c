/*
===============================================================================
SO - Lesson 5 - Exercise 2

Pipes e Sockets

+info: http://en.wikipedia.org/wiki/Dup_(system_call)

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){
	
	int fd[2]; // Pipe

	if (pipe(fd) == -1){ // Open Pipe
		perror("Error creating pipe!\n");
		return 0;
	}
	
	pid_t child1, child2;

	int fd1 = dup(1); // Create a copy of stdout (output of ls)
	close(1); // Close standard output -> stdout (console)

	// now stdout and fd1 are equivalent (dup returns lowest free descriptor) 

	mode_t fdmode = (S_IRUSR | S_IWUSR); // Permissions of file
	int fdp = open("count.txt", O_CREAT | O_WRONLY, fdmode);

	// Create two Childs
	child1 = fork();
	if (child1!=0)
		child2 = fork();

	if (child1==0){ // First Command
		char msgi[] = "Child 1 created!\n";
		char msgf[] = "Child 1 terminated!\n";

		write(fd1, msgi, strlen(msgi)+1); // 

		close(fd[0]); // Close Read Pipe (We don't need)
		dup2(fd[1], fdp); // (Copy) Link Pipe Input (Write) to file discriptor
		close(fd[1]); // Close Write Pipe (Output)

		write(fd1, msgf, strlen(msgf)+1); // Write to stdout copy

		execlp("ls", "ls", NULL); // Execute comand ls

		perror("Error in process child 1!\n");
		return 0;

	}else if(child2==0){ // Second Command

		char msgi[] = "Child 2 created!\n";
		char msgf[] = "Child 2 terminated!\n";

		write(fd1, msgi, strlen(msgi)+1);

		close(fd[1]);
		dup2(fd[0], 0); // (Copy) Link Pipe Input to stdin
		close(fd[0]);

		write(fd1, msgf, strlen(msgf)+1);
		execlp("wc", "wc", "-l", NULL);

		perror("Error in process child 2!\n");
		return 0;

	}else if(child1 < 0 || child2 < 0){
		perror("Error creating childs!\n");
		return 0;
	}
	else{ // Father
		wait(NULL); // Wait for childs exit

		char msgi[] = "Parent process created!\n";
		char msgf[] = "Parent process terminated!\n";

		write(fd1, msgi, strlen(msgi)+1);

		close(fd[0]);
		close(fd[1]);
		close(fdp);

		write(fd1, msgf, strlen(msgf)+1);
	}


	return 0;
}