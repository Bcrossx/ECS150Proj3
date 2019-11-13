#include <assert.h>
#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include "queue.h"
#include "thread.h"
#include "tps.h"


// holds the page address
typedef struct page{
  void* pa; //page address pointer

}page;


// holds the threadID
// and pointer to page address pointer
typedef struct threadPS {
  pthread_t threadID;
  page* page;
}threadPS;


static queue_t threadQueue = NULL; //static queue initialize

//Basically try to find a TID matche
//and return 1 if we do.
static int findTID(void *arg, void *data)
{
    pthread_t found = *((pthread_t*)arg);
    threadPS* tps = (threadPS*)data;

    if (tps->threadID == found){
      return 1;
    }

    return 0;
}

//Same thing but modified to get the Page address
static void* findPA(void *arg, void *data)
{
    threadPS* tps = (threadPS*)data;
    pthread_t found = *((pthread_t*)arg);

    if (tps->threadID == found){
      return tps->page->pa;
    }

    return 0;
}

static void segv_handler(int sig, siginfo_t *si, void *context)
{
    // /*
    //  * Get the address corresponding to the beginning of the page where the
    //  * fault occurred
    //  */
    // void *p_fault = (void*)((uintptr_t)si->si_addr & ~(TPS_SIZE - 1));
    //
    // /*
    //  * Iterate through all the TPS areas and find if p_fault matches one of them
    //  */
    // //...
    // if (/* There is a match */)
    //     /* Printf the following error message */
    //     fprintf(stderr, "TPS protection error!\n");
    //
    // /* In any case, restore the default signal handlers */
    // signal(SIGSEGV, SIG_DFL);
    // signal(SIGBUS, SIG_DFL);
    // /* And transmit the signal again in order to cause the program to crash */
    // raise(sig);
}

// uses segfault for initialization

int tps_init(int segv)
{
  if (segv) {
        struct sigaction sa;

        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = segv_handler;
        sigaction(SIGBUS, &sa, NULL);
        sigaction(SIGSEGV, &sa, NULL);
    }

  return 0;
}

// creates a TPS
int tps_create(void)
{
  threadPS* tps = (threadPS*) malloc(sizeof(struct threadPS));//allocate/init tps struct
  page* pageThread = (page*) malloc(sizeof(struct page));//allocate/init page struct

  tps->threadID = pthread_self(); //get thread ID
  void* mem = mmap(NULL, TPS_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
  pageThread->pa = mem; //memory address for our thread pages

  tps->page = pageThread;

  threadQueue = queue_create();//init queue
  queue_enqueue(threadQueue, pageThread);//enqueue pages
  int tpsCheck = queue_iterate(threadQueue, findTID, &tps->threadID, NULL);
  if(tpsCheck == 1){ //iterate through and if theres already
    return -1;      // a TPS, then quit.
  }

  return 0;
}


// Destroys and frees memory block
int tps_destroy(void)
{
  enter_critical_section();
  pthread_t tid = pthread_self();

  void* pa;

  queue_iterate(threadQueue, (void*)findPA, &tid, (void**)&pa);

  munmap(pa, TPS_SIZE);//destroy the TPS

  int *ptr;
  int tpsCheck = queue_iterate(threadQueue, findTID, &tid, (void**)&ptr);

  if(tpsCheck == 0){ //opposite of the create case
    return -1;
  }
  exit_critical_section();
  return 0;
}


// reads the info from the TPS char/string
// and puts it into the buffer
int tps_read(size_t offset, size_t length, char *buffer)
{
  enter_critical_section();

  pthread_t tid = pthread_self();

  int *pa;

  queue_iterate(threadQueue, (void*)findPA, &tid, (void**)&pa);
  void* info = mmap(pa, TPS_SIZE, PROT_READ, MAP_PRIVATE|MAP_ANONYMOUS, -1, offset);

  memcpy(buffer, info, length);

  exit_critical_section();
  return 0;
}


// takes the message from the User
// and writes it into the TPS
int tps_write(size_t offset, size_t length, char *buffer)
{
  enter_critical_section();
  pthread_t tid = pthread_self();

  int *pa;

  queue_iterate(threadQueue, (void*)findPA, &tid, (void**)&pa);
  void* info = mmap(pa, TPS_SIZE, PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, offset);

  memcpy(info, buffer, length);
  exit_critical_section();
  return 0;
}


// creates a clone of the TPS
int tps_clone(pthread_t tid)
{
  enter_critical_section();
  int ptr;
  void* clonePA = mmap(NULL, TPS_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

  int tpsCheck = queue_iterate(threadQueue, findTID, &tid, NULL);
  queue_iterate(threadQueue, (void*)findPA, &tid, (void**)&ptr);

  memcpy(clonePA, &ptr, TPS_SIZE);

  if(tpsCheck == 1){
    return -1;
  }

  exit_critical_section();
  return 0;
}
