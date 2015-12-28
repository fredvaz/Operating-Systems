#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

int *thrid = NULL;
pthread_t *thread = NULL;
int M, N, count = 1;
//static pthread_mutex_t mutex[10] = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};
static pthread_mutex_t *mutex;

void cleanup(int signum)
{
	int i;
	for(i = 0; i < M; i++)
		pthread_mutex_destroy(&mutex[i]);
	pthread_exit(NULL);
	if(thread != NULL)
		free(thread);
	if(thrid != NULL)
		free(thrid);
	if(mutex != NULL)
		free(mutex);
	exit(0);
}

void *threadf(void *arg)
{
	int *parg = (int *) arg;

	printf("Hello world, I'm thread %d\n", *parg);

	do{
		if(*parg == M)
			pthread_mutex_unlock(&mutex[0]);
		pthread_mutex_lock(&mutex[*parg-1]);
		if(count <= N)
			printf("thread %d counting %d\n", *parg, count);
		count++;
		if(count > N && *parg == M)
			pthread_mutex_unlock(&mutex[0]);
		if(*parg < M)
			pthread_mutex_unlock(&mutex[*parg]);
	} while(count < N);

	//printf("I'm thread %d and I'm leaving!\n", *parg);
	pthread_exit(NULL);
	return NULL;
}

int main(int argc, char **argv)
{
	int i;
	for(i = 0; i < 20; i++)
		signal(i, cleanup);

	if(argc != 3){
		printf("Usage: ./p6 M N, M threads, N counting!\n");
		return 0;
	}

	printf("Mutex program starting.\n");

	M = atoi(argv[1]);
	N = atoi(argv[2]);

	thread = (pthread_t *) malloc(M*sizeof(pthread_t));
	thrid = (int *) malloc(M*sizeof(int));
	mutex = malloc(M*sizeof(pthread_mutex_t));

	int j;
	for(j = 0; j < 10; j++){
		pthread_mutex_init(&mutex[j], NULL);
		pthread_mutex_lock(&mutex[j]);
	}

	for(j = 0; j < M; j++){
		thrid[j] = j+1;
		pthread_create(&thread[j], NULL, threadf, &thrid[j]);
	}

	for(j = 0; j < M; j++)
		pthread_join(thread[j], NULL);

	cleanup(1);

	pthread_exit(NULL);

	return 0;
}
