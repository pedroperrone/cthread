#ifndef __scheduler__
#define __scheduler__

#include <stdlib.h>

void initialize_queue(PFILA2* fila);
void initialize_main_thread_and_queues();
void create_thread(void* (*start)(void*), void *arg, int prio);
void select_thread_and_execute();
void threat_end_of_thread();

#endif
