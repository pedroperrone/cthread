#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/scheduler.h"

#define LOWEST_PRIORITY 2

int main_thread_exists = 0;

int ccreate (void* (*start)(void*), void *arg, int prio) {
	if(!main_thread_exists) {
		initialize_main_thread_and_queues();
		main_thread_exists = 1;
	}
	if(start == NULL) return -1;
	if(prio >= LOWEST_PRIORITY) return -1;

	create_thread(start, arg, prio);
	schedule();
	return 0;
}

int csetprio(int tid, int prio) {
	return -1;
}

int cyield(void) {
	return -1;
}

int cjoin(int tid) {
	return -1;
}

int csem_init(csem_t *sem, int count) {
	return -1;
}

int cwait(csem_t *sem) {
	return -1;
}

int csignal(csem_t *sem) {
	return -1;
}

int cidentify (char *name, int size) {
	strncpy (name, "Sergio Cechin - 2017/1 - Teste de compilacao.", size);
	return 0;
}


