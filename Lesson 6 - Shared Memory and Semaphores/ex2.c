/*
===============================================================================
SO - Lesson 6 - Exercise 2

Message Queues

+info: http://en.wikipedia.org/wiki/Message_queue

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>

struct msgbuf{
	long mtype;	/* message type */
	int n;	/* message number */
};

int main(){

	// Identifier Message Queues
	int msgid = msgget(IPC_PRIVATE, O_CREAT | S_IRUSR | S_IWUSR); 

	if (msgid==-1){
		perror("Error creating message queue!\n");
		return 0;
	}
	
	struct msgbuf number;
	number.mtype = 1; // mtype > 0: read the first message of type “mtype”.
	number.n = 5;

	// Create the child
	pid_t child = fork();

	if (child==0){
		
		int randn_child = rand() % 10; // Generate random number 0 to 9
		int n;

		do{ // Response of Child Process
			
			/*==============================*/
			// flags = 0: block until a message is available
			msgrcv(msgid, &number, sizeof(int), number.mtype, 0);
			//Note: I ignored call of errors 
			/*==============================*/

			if(number.n > randn_child){
				printf("[Child] Wrong! The number is smaller than attempt.\n");
				n = 1;
			}
			else if(number.n < randn_child){
				printf("[Child] Wrong! The number is bigger than attempt.\n");
				n = -1;
			}else{
				printf("[Child] Yeeh! The number is equal to attempt.\n");
				n = 0;
			}
      		/*==============================*/
      		number.n = n;
      		msgsnd(msgid, &number, sizeof(int), 0);
      		/*==============================*/

		}while(n!=0); // Until number attempt of father equal to number genarated by child
	}else if(child < 0){
		perror("Error creating child process!\n");
	}else{
		// We are in Father. Attempt generated number of child

		int number_father = 5; // Start attempt number
		int n; // Response

		do{
			printf("[Father] Try to guess the number is: %d\n", number_father);
			
			/*==============================*/
			number.n = number_father;
			msgsnd(msgid, &number, sizeof(int), 0);

			msgrcv(msgid, &number, sizeof(int), number.mtype, 0);
			n = number.n;
			/*==============================*/

			// Attempt if child responde is < or > and try other number
			if(n == 1)
				number_father--; // <
			else if (n == -1)
				number_father++; // >
			else if(n != 0)
				perror("Error occured in father!\n");

		}while(n!=0); 

		printf("[Father] The guess number was: %d\n", number_father);
	}

	return 0;
}