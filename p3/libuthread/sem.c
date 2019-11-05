#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "thread.h"

struct semaphore {
	int count = 0;
  queue_t blocked_queue;
  queue_t unblocked_queue; //blocked/unblocked to prevent starvation
};

sem_t sem_create(size_t count)
{
	enter_critical_section

  sem_t s = (sem_t) malloc(sizeof(struct semaphore));

  //return pointer to initialized semaphore
  exit_critical_section
}

int sem_destroy(sem_t sem)
{
  enter_critical_section

  exit_critical_section
}

int sem_down(sem_t sem)
{
  enter_critical_section
	if(sem == NULL){
    return -1;
  }
  exit_critical_section
}

int sem_up(sem_t sem)
{
  enter_critical_section
  if(sem == NULL){
    return -1;
  }
  exit_critical_section
}

int sem_getvalue(sem_t sem, int *sval)
{
  enter_critical_section

  exit_critical_section
}

void tid_enqueue(/* arguments */) {
  /* code */
}
