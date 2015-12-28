/*-----------------------------------------------------------------------*/
/*                  semlib.c                                             */
/*-----------------------------------------------------------------------*/
/*  Semaphores module.                                                   */
/*  Compilation: gcc -Wall -c semlib.c                                   */
/*-----------------------------------------------------------------------*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "semlib.h"

/*-----------------------------------------------------------------------*/
/*                  type definitions                                     */
/*-----------------------------------------------------------------------*/
#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
/* union semun is defined by including <sys/sem.h> */
#else
/* according to X/OPEN we have to define it ourselves */
union semun {
  int val;                    /* value for SETVAL */
  struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
  unsigned short int *array;  /* array for GETALL, SETALL */
  struct seminfo *__buf;      /* buffer for IPC_INFO */
};
#endif

/*-----------------------------------------------------------------------*/
/*                  sem_create()                                         */
/*-----------------------------------------------------------------------*/
/*  Create or open a semaphore. Use IPC_PRIVATE key.                     */
/*-----------------------------------------------------------------------*/
int sem_create(int nsem, int init_val){

  int semid;
  int x,i;

  semid=semget(IPC_PRIVATE,nsem,0777|IPC_CREAT);

  if(semid == -1){
    printf("Failed to create the semaphore.\n");
    return(-1);
  }

  for (i=0; i<nsem; i++){
    x=sem_setvalue(semid, i, init_val);
    if(x == -1){
      printf("Error in sem_setvalue.\n");
      return(-1);
    }
  }

  return(semid);

}

/*-----------------------------------------------------------------------*/
/*                  sem_create_wkey()                                    */
/*-----------------------------------------------------------------------*/
/*  Create or open a semaphore with a specified key.                     */
/*-----------------------------------------------------------------------*/
int sem_create_wkey(int key, int nsem, int init_val){

  int semid;
  int x,i;

  semid=semget(key,nsem,0777|IPC_CREAT);

  if(semid == -1){
    printf("Failed to create the semaphore.\n");
    return(-1);
  }

  for (i=0; i<nsem; i++){
    x=sem_setvalue(semid, i, init_val);
    if(x == -1){
      printf("Error in sem_setvalue.\n");
      return(-1);
    }
  }

  return(semid);

}

/*-----------------------------------------------------------------------*/
/*                  sem_close()                                          */
/*-----------------------------------------------------------------------*/
/*  Release a semaphore set.                                             */
/*-----------------------------------------------------------------------*/
void sem_close(int sem_id){

  int ret;

  ret = semctl(sem_id,0,IPC_RMID,0);
  if(ret == -1)
    printf("Failed to remove a semaphore.\n");

  return;

}

/*-----------------------------------------------------------------------*/
/*                  sem_setvalue()                                       */
/*-----------------------------------------------------------------------*/
/*  Set the value of a semaphore.                                        */
/*-----------------------------------------------------------------------*/
int sem_setvalue(int sem_id, int sem_num, int value){

  union semun val;
  int ret;

  val.val = value;

  ret=semctl(sem_id, sem_num, SETVAL, val);
  if(ret == -1){
    printf("Failed to initialize semaphore.\n");
    return(-1);
  }

  return(0);

}

/*-----------------------------------------------------------------------*/
/*                  sem_wait()                                           */
/*-----------------------------------------------------------------------*/
/*  Wait on the semaphore.                                               */
/*-----------------------------------------------------------------------*/
int sem_wait(int sem_id, int sem_num){

  struct sembuf x;
  int ret;

  x.sem_op  = -1 ;
  x.sem_flg = 0 ;
  x.sem_num = sem_num;

  ret=semop(sem_id,&x,1);
  if(ret == -1){
    printf("Failed to make wait on semaphore.\n");
    return(-1);
  }

  return(0);

}

/*-----------------------------------------------------------------------*/
/*                  sem_signal()                                         */
/*-----------------------------------------------------------------------*/
/*  Signal the semaphore.                                                */
/*-----------------------------------------------------------------------*/
int sem_signal(int sem_id, int sem_num){

  struct sembuf x;
  int ret;

  x.sem_op  = +1 ;
  x.sem_flg = 0 ;
  x.sem_num = sem_num ;

  ret=semop(sem_id,&x,1);
  if(ret == -1){
    printf("Failed to make signal on semaphore.\n");
    return(-1);
  }

  return(0);

}

/*-----------------------------------------------------------------------*/
/*                  sem_op()                                             */
/*-----------------------------------------------------------------------*/
/*  Operation on a semaphore.                                            */
/*    if n < 0  ==>  wait                                                */
/*    if n > 0  ==>  signal                                              */
/*-----------------------------------------------------------------------*/
int sem_op(int sem_id, int sem_num, int n){

  struct sembuf x;
  int    ret;

  x.sem_op  = n ;
  x.sem_flg = 0 ;
  x.sem_num = sem_num ;

  ret=semop(sem_id,&x,1);
  if(ret == -1){
    printf("Failed to make sem_op on semaphore.\n");
    return(-1);
  }

  return(0);

}

/*-----------------------------------------------------------------------*/
/*                  sem_rm()                                             */
/*-----------------------------------------------------------------------*/
/*  Remove a semaphore.                                                  */
/*-----------------------------------------------------------------------*/
int sem_rm(int sem_id){

  int ret;

  ret=semctl(sem_id,0,IPC_RMID,0);
  if(ret == -1){
    printf("Failed to remove a semaphore.\n");
    return(-1);
  }

  return(0);

}

/*-----------------------------------------------------------------------*/

