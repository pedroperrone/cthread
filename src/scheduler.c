#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/scheduler.h"

#define STACK_SIZE 8192

PFILA2 ready = NULL, blocked = NULL, running = NULL;
TCB_t main_thread;
int tid_sequence = 0;

void initialize_queue(PFILA2* fila) {
	*fila = malloc(sizeof(PFILA2));
	CreateFila2(*fila);
	FirstFila2(*fila);
}

void initialize_main_thread_and_queues() {
	PFILA2* queues_of_states[] = {&ready, &blocked, &running};
	int i;
	main_thread.tid = 0;
	main_thread.prio = 2;
	getcontext(&(main_thread.context));

	for(i = 0; i <= 2; i++) {
		initialize_queue(queues_of_states[i]);
	}
}

void create_thread(void* (*start)(void*), void *arg, int prio) {
	char *end_thread_function_stack;
	ucontext_t *end_thread_function_context;
	TCB_t *thread;

	// Create a context for the end thread function
	end_thread_function_stack = malloc(STACK_SIZE);
	end_thread_function_context = malloc(sizeof(ucontext_t));
	getcontext(end_thread_function_context);
	end_thread_function_context->uc_stack.ss_size = STACK_SIZE;
	end_thread_function_context->uc_stack.ss_sp = end_thread_function_stack;
	end_thread_function_context->uc_link = NULL;
	makecontext(end_thread_function_context, threat_end_of_thread, 0);

	// Set the thread attributes
	thread = malloc(sizeof(TCB_t));
	thread->tid = next_tid();
	// TODO: deal with state
	thread->state = 1;
	thread->prio = prio;
	getcontext(&(thread->context));
	thread->context.uc_stack.ss_size = STACK_SIZE;
	thread->context.uc_stack.ss_sp = malloc(STACK_SIZE);
	thread->context.uc_link = end_thread_function_context;
	makecontext(&(thread->context), (void(*)(void))start, 1, arg);

	// Add the created thread to the ready list
	AppendFila2(ready, (void*) thread);
}

void threat_end_of_thread() {
	TCB_t *next_thread = select_thread_to_run();
	TCB_t *current_thread = select_thread_to_preempt();
	free(current_thread);

	FirstFila2(running);
	DeleteAtIteratorFila2(running);

	if(next_thread == NULL) {
		setcontext(&(main_thread.context));
	} else {
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

// Find the first element with highest priority, removes it from the list and return a pointer to it.
TCB_t* select_thread_to_run() {
	int priority;
	TCB_t* thread;
	if(FirstFila2(ready) != 0) { // If the queue is empty
		return NULL;
	}
	for(priority = 0; priority <= 2; priority++) {
		do {
			thread = GetAtIteratorFila2(ready);
			if(thread->prio == priority) {
				return thread;
			}
		} while(NextFila2(ready) == 0);
		FirstFila2(ready);
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
	return !FirstFila2(queue);
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

	if(running_thread == NULL) {
		remove_thread_from_queue(ready, fittest_ready_thread->tid);
		AppendFila2(running, fittest_ready_thread);
		swapcontext(&(main_thread.context), &(fittest_ready_thread->context));
		return;
	}
	if(running_thread->prio > fittest_ready_thread->prio) {
		swap_from_ready_and_running(fittest_ready_thread, running_thread);
		swapcontext(&(running_thread->context), &(fittest_ready_thread->context));
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

void swap_from_ready_and_running(TCB_t* ready_thread, TCB_t* running_thread) {
	if(!thread_is_in_queue(ready, ready_thread->tid)) {
		return;
	}
	if(!thread_is_in_queue(running, running_thread->tid)) {
		return;
	}
	remove_thread_from_queue(ready, ready_thread->tid);
	remove_thread_from_queue(running, running_thread->tid);
	AppendFila2(ready, running_thread);
	AppendFila2(running, ready_thread);
}
