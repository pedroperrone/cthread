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
	//sem = malloc(sizeof(csem_t));
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
	strncpy (name, "Sergio Cechin - 2017/1 - Teste de compilacao.", size);
	return 0;
}


