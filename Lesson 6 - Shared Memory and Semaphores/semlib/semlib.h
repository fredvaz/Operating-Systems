/*-----------------------------------------------------------------------*/
/*                  semlib.h                                             */
/*-----------------------------------------------------------------------*/
/* Interface definition of a simple semaphore library for using          */
/* in inherited programs (parent-child relationship).                    */
/*-----------------------------------------------------------------------*/
#ifndef _SEMLIB_H_
#define _SEMLIB_H_

/*-----------------------------------------------------------------------*/
/*                  include files                                        */
/*-----------------------------------------------------------------------*/
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

/*-----------------------------------------------------------------------*/
/*                  function prototypes                                  */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/*                  sem_create()                                         */
/*-----------------------------------------------------------------------*/
/* Obtains a new or existing (i.e. creates or opens) array of semaphores */
/* from the system. The number of semaphores in the array is <nsem>, and */
/* they all have the initial value of <init_val>. The function returns   */
/* the semaphore id (semid) of the set, or -1 on error. The semaphores   */
/* in the set range from 0 to nsem-1.                                    */
/* This function specifies the key as IPC_PRIVATE.                       */
/*-----------------------------------------------------------------------*/
extern int sem_create(int nsem, int init_val);

/*-----------------------------------------------------------------------*/
/*                  sem_create_wkey()                                    */
/*-----------------------------------------------------------------------*/
/* Obtains a new or existing (i.e. creates or opens) array of semaphores */
/* from the system. The number of semaphores in the array is <nsem>, and */
/* they all have the initial value of <init_val>. The function returns   */
/* the semaphore id (semid) of the set, or -1 on error. The semaphores   */
/* in the set range from 0 to nsem-1.                                    */
/* This function uses the specified <key>.                               */
/*-----------------------------------------------------------------------*/
extern int sem_create_wkey(int key, int nsem, int init_val);

/*-----------------------------------------------------------------------*/
/*                  sem_close()                                          */
/*-----------------------------------------------------------------------*/
/* Releases a semaphore set that is no longer in use. <sem_id> identifies*/
/* the semaphore set.                                                    */
/*-----------------------------------------------------------------------*/
extern void sem_close(int sem_id);

/*-----------------------------------------------------------------------*/
/*                  sem_wait()                                           */
/*-----------------------------------------------------------------------*/
/* Performs a wait on a certain semaphore in a semaphore set.            */
/* The semaphore set is <sem_id>, and <sem_num> represents the particular*/ 
/* semaphore in question.                                                */
/*-----------------------------------------------------------------------*/
extern int sem_wait(int sem_id, int sem_num);

/*-----------------------------------------------------------------------*/
/*                  sem_signal()                                         */
/*-----------------------------------------------------------------------*/
/* Performs a signal on a certain semaphore in a semaphore set.          */
/* The semaphore set is <sem_id>, and <sem_num> represents the particular*/
/* semaphore in question.                                                */
/*-----------------------------------------------------------------------*/
extern int sem_signal(int sem_id, int sem_num);

/*-----------------------------------------------------------------------*/
/*                  sem_setvalue()                                       */
/*-----------------------------------------------------------------------*/
/* Directly sets the value of a semaphore in a semaphore set to a        */
/* certain value. The semaphore set is identified by <sem_id>, and the   */
/* semaphore is <sem_num>. <value> represents the new value of the       */
/* semaphore. This routine should only be used for initializing          */
/* semaphores.                                                           */
/*-----------------------------------------------------------------------*/
extern int sem_setvalue(int sem_id, int sem_num, int value);

/*-----------------------------------------------------------------------*/
/*                  sem_op()                                             */
/*-----------------------------------------------------------------------*/
/*  Operation on a semaphore.                                            */
/*    if n < 0  ==>  wait                                                */
/*    if n > 0  ==>  signal                                              */
/*-----------------------------------------------------------------------*/
extern int sem_op(int sem_id, int sem_num, int n);

/*-----------------------------------------------------------------------*/
/*                  sem_rm()                                             */
/*-----------------------------------------------------------------------*/
/*  Remove a semaphore.                                                  */
/*-----------------------------------------------------------------------*/
extern int sem_rm(int sem_id);

#endif
/*-----------------------------------------------------------------------*/

