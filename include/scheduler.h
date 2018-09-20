#ifndef __scheduler__
#define __scheduler__

#include <stdlib.h>
#include "cdata.h"
#include "cthread.h"

typedef struct s_JOIN {
	int waiting_tid;
	int waited_tid;
} JOIN_t;

void initialize_queue(PFILA2* fila);
void initialize_main_thread_and_queues();
int create_thread(void* (*start)(void*), void *arg, int prio);
void threat_end_of_thread();
int next_tid();
int thread_is_in_queue(PFILA2 queue, int tid);
TCB_t* select_thread_to_run();
TCB_t* select_thread_by_priority_on(PFILA2 queue);
TCB_t* find_by_tid(PFILA2 queue, int tid);
int is_empty(PFILA2 queue);
void schedule();
void remove_thread_from_queue(PFILA2 queue, int tid);
TCB_t* select_thread_to_preempt();
void print_fila(PFILA2 fila);
void print_ready();
void print_running();
void yield();
void dispatch(PFILA2 current_thread_destiny, TCB_t *current_thread,
			  TCB_t *next_thread);
int priority_is_valid(int priority);
int update_current_thread_priority(int priority);
void change_thread_queue(PFILA2 origin, PFILA2 destiny, int tid);
int thread_waiting_for(int waited_tid);
int thread_exists(int tid);
int join(int tid);
void free_blocked_thread(int waited_tid);
void initialize_context(ucontext_t *cont, ucontext_t *following);
int sem_init(csem_t *sem, int count);
int c_wait(csem_t *sem);
int c_signal(csem_t *sem);

#endif
