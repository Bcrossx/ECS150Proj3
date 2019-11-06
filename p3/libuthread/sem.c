#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "thread.h"

struct semaphore {
	int count = 0;
  queue_t blocked_queue; //add blocked threads to this queue
};

sem_t sem_create(size_t count)
{
	enter_critical_section();

  sem_t s = (sem_t) malloc(sizeof(struct semaphore)); //allocate semaphore
	s->count = count; //initialize semaphore
	blocked_queue = queue_create(); //initialize queue

	exit_critical_section();

	//return pointer to initialized semaphore
	return s;
}

int sem_destroy(sem_t sem)
{
  enter_critical_section();
	if(sem == NULL || blocked_queue != 0) //check if sem is NULL or if other threads
		return -1;									 //are still in blocked queue

	free(sem);										 //Deallocate sem
  exit_critical_section();

	return 0;
}

int sem_down(sem_t sem)
{
	pthread_t tid = pthread_self();
  enter_critical_section();
	if(sem == NULL){
    return -1;
  }
	if(sem = 0){
		queue_enqueue(blocked_queue,tid); //enqueue
		thread_block(); //block if no resources
	}
	count--;
  exit_critical_section();

	return 0;
}

int sem_up(sem_t sem)
{
	pthread_t tid = pthread_self();
  enter_critical_section();
  if(sem == NULL){
    return -1;
  }
	if(sem >= 1){
		queue_dequeue(blocked_queue, tid);
		thread_unblock();
	}
	count++;
  exit_critical_section();

	return 0;
}

int sem_getvalue(sem_t sem, int *sval)
{
  enter_critical_section();
	if(sem >= 0){
		*sval = count;
	}
	if(sem == 0){
		//assign a negative number
	  //whose absolute value is the count of
		//the number of threads currently blocked
	  //in sem_down().
	}
	if(sem == NULL || *sval == NULL){
		return -1;
	}

  exit_critical_section();

	return 0;
}
