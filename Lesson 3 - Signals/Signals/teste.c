#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

pid_t child;

void sig_c(int var)
{
	signal(SIGINT, sig_c);

	if(child == 0){
		printf("\nI'm the child process. Bye bye.\n");
		exit(0);
	}
}

void sig_s(int var)
{
	signal(SIGQUIT, sig_s);

	if(child == 0){
		printf("\nI'm the child process. Bye bye.\n");
		exit(0);
	}
	else{
		child = wait(NULL);
		printf("I'm the parent process. End of the program.\n");
		exit(0);
	}
}

int main(void)
{
	signal(SIGINT, sig_c);
	signal(SIGQUIT, sig_s);

	while(1){
		child = fork();

		if(child == 0)
			while(1){
				printf("I'm the child and I'm running! %d\n", getpid());
				sleep(1);
			}
		else if(child < 0)
			printf("Error creating child!\n");
		else
			child = wait(NULL);
	}

	return 0;
}