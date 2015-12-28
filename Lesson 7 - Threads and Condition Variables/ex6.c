/*
===============================================================================
SO - Lesson 7 - Exercise 6

Threads & Condition Variables

+info: http://en.wikipedia.org/wiki/Thread_(computing)

Developer: Frederico Vaz
===============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

int M, N, count = 1;
static pthread_mutex_t *mutex;
pthread_t *thread = NULL;
int *thread_ID = NULL;
// Ideal we can make a struct and passing by input argument of thread 
// but for simplicity we use the global memory 
void *thread_func(void *arg);

int main(int argc, char const *argv[]){
	
	if (argc != 3){
		printf("Usage: ./ex6 M N, M threads, N counting!\n");
		return 0;
	}

	printf("Mutex program starting!\n");

	M = atoi(argv[1]); // Number of Threads
	N = atoi(argv[2]); // Number of counting

	// Allocate memory Threads and Mutex Dynamicaly
	thread = (pthread_t *) malloc(M*sizeof(pthread_t));
	mutex = malloc(M*sizeof(pthread_mutex_t));
	thread_ID = (int *) malloc(M*sizeof(int));

	int i;
	// One Mutex for each Thread (Must be created first)
	for (i = 0; i < M; i++){
		pthread_mutex_init(&mutex[i], NULL);
		pthread_mutex_lock(&mutex[i]); // All Threads Waiting!
	}
	// Create and execute Threads with Input paraments
	for (i = 0; i < M; i++){
		thread_ID[i] = i+1; // Number of Thread (Virtual ID)
		pthread_create(&thread[i], NULL, thread_func, &thread_ID[i]);
	}
	// Waiting for termination of Threads and wihout return Output paraments
	for (i = 0; i < M; i++){
		pthread_join(thread[i], NULL);
	}

	printf("Terminating process...\n");

	// Clean and Terminate
	for(i = 0; i < M; i++)
		pthread_mutex_destroy(&mutex[i]);
	pthread_exit(NULL);
	if(thread != NULL)
		free(thread);
	if(thread_ID != NULL)
		free(thread_ID);
	if(mutex != NULL)
		free(mutex);

	return 0;
}

void *thread_func(void *arg){

	int ID = *((int *) arg);

	printf("Hello World! I'm thread %d\n", ID); // Lauching threads

	do{ // Threads initially are waiting then cycle While is stopped/break

		if (ID==M) // When last thread run go back to (unlock) first thread
			pthread_mutex_unlock(&mutex[0]);
		pthread_mutex_lock(&mutex[ID-1]); // Last thread waiting!
		if (count <= N) // Until counting not end
			printf("Thread %d counting %d\n", ID, count);
		count++;
		if(count > N && ID == M)
			pthread_mutex_unlock(&mutex[0]);
		if(ID < M) // Launch current thread
			pthread_mutex_unlock(&mutex[ID]);
		
	}while(count < N);

	pthread_exit(NULL);
	return NULL;
}







