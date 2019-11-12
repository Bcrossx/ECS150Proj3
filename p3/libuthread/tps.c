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
  //mmap
  //page address pointer
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

  struct tps td;
  //
	//thread queue
  //mmap queue
  void* mem = mmap(NULL, TPS_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS,
    -1, 0);
  //struct tps td;

}

int tps_destroy(void)
{
  enter_critical_section();
	/* TODO: Phase 2 */
  exit_critical_section();
}

int tps_read(size_t offset, size_t length, char *buffer)
{
  enter_critical_section();
	/* TODO: Phase 2 */
  exit_critical_section();
}

int tps_write(size_t offset, size_t length, char *buffer)
{
  enter_critical_section();
	/* TODO: Phase 2 */
  exit_critical_section();
}

int tps_clone(pthread_t tid)
{
  enter_critical_section();
  /* TODO: Phase 2 */
  //memcpy()
  exit_critical_section();
}
