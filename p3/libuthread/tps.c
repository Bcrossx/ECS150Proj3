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

typedef struct page{
  void* pa; //page address pointer

}page;

typedef struct threadPS {
  pthread_t threadID;
  page* page;
}threadPS;

static queue_t threadQueue = NULL;

//queue to the strucs, strucs have their own info (TID,mmap, etc.)
//Read and write, pthread_self to search through the queue and see if it exists,
// if not, we need to add a new tps to our queue

static int findTID(void *data, void *arg)
{
    threadPS* tps = (threadPS*)data;
    pthread_t found = *((pthread_t*)arg);

    if (tps->threadID == found){
      return 1;
    }

    return 0;
}
int tps_init(int segv)
{
	/* TODO: Phase 2 */
  return 0;
}

int tps_create(void)
{
  threadPS* tps = (threadPS*) malloc(sizeof(struct threadPS));
  page* pageThread = (page*) malloc(sizeof(struct page));

  tps->threadID = pthread_self();
  void* mem = mmap(NULL, TPS_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
  pageThread->pa = mem;

  tps->page = pageThread;

  threadQueue = queue_create();
  queue_enqueue(threadQueue, pageThread);
  int check = queue_iterate(threadQueue, findTID, &tps->threadID, NULL);
  if(check == 1){
    return -1;
  }

  return 0;
}

int tps_destroy(void)
{
  enter_critical_section();
	/* TODO: Phase 2 */
  exit_critical_section();
  return 0;
}

int tps_read(size_t offset, size_t length, char *buffer)
{
  enter_critical_section();
	/* TODO: Phase 2 */
  exit_critical_section();
  return 0;
}

int tps_write(size_t offset, size_t length, char *buffer)
{
  enter_critical_section();
	/* TODO: Phase 2 */
  exit_critical_section();
  return 0;
}

int tps_clone(pthread_t tid)
{
  enter_critical_section();
  //memcpy()
  exit_critical_section();
  return 0;
}
