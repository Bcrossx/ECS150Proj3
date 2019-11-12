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

struct tps {
  //tps data
}
//queue to the strucs, strucs have their own info (TID,mmap, etc.)
//Read and write, pthread_self to search through the queue and see if it exists,
// if not, we need to add a new tps to our queue

int tps_init(int segv)
{
	/* TODO: Phase 2 */
}

int tps_create(void)
{
  pthread_t tid = pthread_self();
	//thread queue
  //mmap queue
  //void* mem = mmap(address, TPS_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE |
  //MAP_ANONYMOUS,file descriptor, where in file to start);
  //struct tps td;
}

int tps_destroy(void)
{
	/* TODO: Phase 2 */
}

int tps_read(size_t offset, size_t length, char *buffer)
{
	/* TODO: Phase 2 */
}

int tps_write(size_t offset, size_t length, char *buffer)
{
	/* TODO: Phase 2 */
}

int tps_clone(pthread_t tid)
{
	/* TODO: Phase 2 */
}
