#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/scheduler.h"

int main_thread_exists = 0;

int ccreate (void* (*start)(void*), void *arg, int prio) {
	int tid;
	if(!main_thread_exists) {
		initialize_main_thread_and_queues();
		main_thread_exists = 1;
	}
	if(start == NULL) return -1;
	if(!priority_is_valid(prio)) return -1;

	tid = create_thread(start, arg, prio);
	schedule();
	return tid;
}

int csetprio(int tid, int prio) {
	if(!main_thread_exists) {
		initialize_main_thread_and_queues();
		main_thread_exists = 1;
	}
	if(!priority_is_valid(prio)) return -1;
	if(update_current_thread_priority(prio) == -1) return -1;
	schedule();
	return 0;
}

int cyield(void) {
	if(!main_thread_exists) {
		initialize_main_thread_and_queues();
		main_thread_exists = 1;
	}
	yield();
	return 0;
}

int cjoin(int tid) {
	if(!main_thread_exists) {
		initialize_main_thread_and_queues();
		main_thread_exists = 1;
	}
	if(thread_waiting_for(tid) != -1) return -1;
	if(!thread_exists(tid)) return -1;
	return join(tid);
}

int csem_init(csem_t *sem, int count) {
	if(!main_thread_exists) {
		initialize_main_thread_and_queues();
		main_thread_exists = 1;
	}
	return sem_init(sem, count);
}

int cwait(csem_t *sem) {
	return c_wait(sem);
}

int csignal(csem_t *sem) {
	return c_signal(sem);
}

int cidentify (char *name, int size) {
	char names[] = "Bruno Santana Massena de Lima - 274711\nPedro Salgado Perrone - 274696";
	if(size < strlen(names)) {
		printf("ERROR: the given size for the names is not big enough.\n");
		return -1;
	}
	strncpy (name, names, size);
	return 0;
}


