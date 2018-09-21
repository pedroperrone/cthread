#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/scheduler.h"

#define STACK_SIZE 8192
#define LOWEST_PRIORITY 2
#define HIGHEST_PRIORITY 0

PFILA2 ready = NULL, blocked = NULL, running = NULL, joins = NULL;
int tid_sequence = 0;

void initialize_queue(PFILA2* fila) {
	*fila = malloc(sizeof(PFILA2));
	CreateFila2(*fila);
	FirstFila2(*fila);
}

int priority_is_valid(int priority) {
	return (priority >= HIGHEST_PRIORITY) && (priority <= LOWEST_PRIORITY);
}

void initialize_main_thread_and_queues() {
	PFILA2* queues_of_states[] = {&ready, &blocked, &running, &joins};
	TCB_t *main_thread = malloc(sizeof(TCB_t));
	int i;
	main_thread->tid = 0;
	main_thread->prio = 2;

	for(i = 0; i <= 3; i++) {
		initialize_queue(queues_of_states[i]);
	}

	AppendFila2(running, main_thread);
	initialize_context(&(main_thread->context), NULL);
}

int create_thread(void* (*start)(void*), void *arg, int prio) {
	ucontext_t *end_thread_function_context = malloc(sizeof(ucontext_t));
	TCB_t *thread;
	// Set the thread attributes
	thread = malloc(sizeof(TCB_t));
	thread->tid = next_tid();
	// TODO: deal with state
	thread->state = 1;
	thread->prio = prio;

	initialize_context(end_thread_function_context, NULL);
	initialize_context(&(thread->context), end_thread_function_context);
	makecontext(end_thread_function_context, threat_end_of_thread, 0);
	makecontext(&(thread->context), (void(*)(void))start, 1, arg);

	// Add the created thread to the ready list
	AppendFila2(ready, (void*) thread);
	return thread->tid;
}

void initialize_context(ucontext_t* cont, ucontext_t* following) {
	char *stack;
	getcontext(cont);
	stack = malloc(STACK_SIZE);
	cont->uc_stack.ss_size = STACK_SIZE;
	cont->uc_stack.ss_sp = stack;
	cont->uc_link = following;
}

void threat_end_of_thread() {
	TCB_t *next_thread;
	TCB_t *current_thread = select_thread_to_preempt();
	free_blocked_thread(current_thread->tid);
	next_thread = select_thread_to_run();
	remove_thread_from_queue(running, current_thread->tid);
	free(current_thread);

	if(next_thread != NULL) {
		remove_thread_from_queue(ready, next_thread->tid);
		AppendFila2(running, next_thread);
		setcontext(&(next_thread->context));
	}
}

// TODO: remove
void print_fila(PFILA2 fila) {
	TCB_t* elem;
	if(FirstFila2(fila) != 0) {
		printf("TA VAZIA\n");
		return;
	}
	printf("\nOLHA O PRINT DA FILA\n");
	do {
		elem = (TCB_t*) GetAtIteratorFila2(fila);
		printf("Tid: %d\tPrioridade: %d\n", elem->tid, elem->prio);
	} while(NextFila2(fila) == 0);
	printf("ACABOU O PRINT DA FILA\n");
}

// Find the first element with highest priority and return a pointer to it.
TCB_t* select_thread_to_run() {
	return select_thread_by_priority_on(ready);
}

// Find the first element with highest priority and return a pointer to it.
TCB_t* select_thread_by_priority_on(PFILA2 queue) {
	int priority;
	TCB_t* thread;
	if(FirstFila2(queue) != 0) { // If the queue is empty
		return NULL;
	}
	for(priority = HIGHEST_PRIORITY; priority <= LOWEST_PRIORITY; priority++) {
		do {
			thread = GetAtIteratorFila2(queue);
			if(thread->prio == priority) {
				return thread;
			}
		} while(NextFila2(queue) == 0);
		FirstFila2(queue);
	}
	return NULL;
}

int next_tid() {
	tid_sequence++;
	return tid_sequence;
}

int thread_is_in_queue(PFILA2 queue, int tid) {
	return find_by_tid(queue, tid) != NULL;
}

TCB_t* find_by_tid(PFILA2 queue, int tid) {
	TCB_t* element;
	if(FirstFila2(queue) != 0) {
		return NULL;
	}
	do {
		element = (TCB_t*) GetAtIteratorFila2(queue);
		if(element->tid == tid) {
			return element;
		}
	} while(NextFila2(queue) == 0);
	return NULL;
}

int is_empty(PFILA2 queue) {
	return FirstFila2(queue);
}


// TODO: remove
void print_ready() {
	print_fila(ready);
}


// TODO: remove
void print_running() {
	print_fila(running);
}

void schedule() {
	TCB_t *running_thread, *fittest_ready_thread;

	running_thread = select_thread_to_preempt();
	fittest_ready_thread = select_thread_to_run();
	if(fittest_ready_thread == NULL) return; // There are no more threads to execute
	if(running_thread->prio > fittest_ready_thread->prio) {
		dispatch(ready, running_thread, fittest_ready_thread);
	}
}

TCB_t* select_thread_to_preempt() {
	if(FirstFila2(running) != 0) {
		return NULL;
	}
	return GetAtIteratorFila2(running);
}

void remove_thread_from_queue(PFILA2 queue, int tid) {
	TCB_t *thread_to_remove;
	thread_to_remove = find_by_tid(queue, tid);
	if(thread_to_remove == NULL) {
		return;
	}
	DeleteAtIteratorFila2(queue);
}

void yield() {
	TCB_t *running_thread, *next_thread;
	running_thread = select_thread_to_preempt();
	next_thread = select_thread_to_run();
	if(next_thread == NULL) return; // There are no more threads to run
	if(next_thread->prio <= running_thread->prio) {
		dispatch(ready, running_thread, next_thread);
	}
}

void dispatch(PFILA2 current_thread_destiny,
			  TCB_t *current_thread, TCB_t* next_thread) {
	change_thread_queue(ready, running, next_thread->tid);
	change_thread_queue(running, current_thread_destiny,
						current_thread->tid);
	swapcontext(&(current_thread->context), &(next_thread->context));
}

int update_current_thread_priority(int priority) {
	TCB_t *current_thread = select_thread_to_preempt();
	if(current_thread == NULL) return -1;
	current_thread->prio = priority;
	return 0;
}

void change_thread_queue(PFILA2 origin, PFILA2 destiny, int tid) {
	TCB_t *thread;
	if(!thread_is_in_queue(origin, tid)) return;
	thread = find_by_tid(origin, tid);
	remove_thread_from_queue(origin, tid);
	AppendFila2(destiny, thread);
}

int thread_waiting_for(int waited_tid) {
	JOIN_t* join;
	if(FirstFila2(joins) != 0) {
		return -1;
	}
	do {
		join = (JOIN_t*) GetAtIteratorFila2(joins);
		if(join->waited_tid == waited_tid) {
			return join->waiting_tid;
		}
	} while(NextFila2(joins) == 0);
	return -1;
}

int thread_exists(int tid) {
	return thread_is_in_queue(ready, tid) || thread_is_in_queue(blocked, tid);
}

int join(int tid) {
	TCB_t *next_thread = select_thread_to_run(),
		  *current_thread = select_thread_to_preempt();
	JOIN_t *join = malloc(sizeof(JOIN_t));
	join->waiting_tid = current_thread->tid;
	join->waited_tid = tid;
	AppendFila2(joins, join);
	dispatch(blocked, current_thread, next_thread);
	return 0;
}

void free_blocked_thread(int waited_tid) {
	int tid = thread_waiting_for(waited_tid);
	JOIN_t *join;
	if(tid == -1) return;
	change_thread_queue(blocked, ready, tid);
	join = GetAtIteratorFila2(joins);
	DeleteAtIteratorFila2(joins);
	free(join);
}

int sem_init(csem_t *sem, int count) {
	sem->count = count;
	initialize_queue(&sem->fila);
	return 0;
}

int c_wait(csem_t *sem) {
	TCB_t *running_thread, *next_thread;

	if (sem->count == 0) { // If there are no resources available
		running_thread = select_thread_to_preempt();
		next_thread = select_thread_to_run();
		AppendFila2(sem->fila, running_thread);
		dispatch(blocked, running_thread, next_thread);
		return 0;
	} else {
		sem->count--;
		return 0;
	}
}

int c_signal(csem_t *sem) {
	TCB_t *fittest_sem_thread;

	if (is_empty(sem->fila)) {
		sem->count++;
		return 0;
	} else {
		fittest_sem_thread = select_thread_by_priority_on(sem->fila);
		remove_thread_from_queue(sem->fila, fittest_sem_thread->tid);
		change_thread_queue(blocked, ready, fittest_sem_thread->tid);
		schedule();
		return 0;
	}
}
