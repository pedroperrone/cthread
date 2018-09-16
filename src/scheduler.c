#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/scheduler.h"

#define STACK_SIZE 8192

PFILA2 ready = NULL, blocked = NULL, running = NULL;
TCB_t main_thread;

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
	getcontext(&main_thread.context);

	for(i = 0; i <= 2; i++) {
		initialize_queue(queues_of_states[i]);
	}
	AppendFila2(running, (void*) &main_thread);
}

void create_thread(void* (*start)(void*), void *arg, int prio) {
	char *thread_stack, *end_thread_function_stack;
	ucontext_t thread_context;
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

	// Create a context for the thread being created
	thread_stack = malloc(STACK_SIZE);
	getcontext(&thread_context);
	thread_context.uc_stack.ss_size = STACK_SIZE;
	thread_context.uc_stack.ss_sp = thread_stack;
	thread_context.uc_link = end_thread_function_context;
	makecontext(&thread_context, (void(*)(void))start, 1, arg);

	// Set the tread attributes
	thread = malloc(sizeof(TCB_t));
	thread->tid = 1;
	thread->state = 1;
	thread->prio = 1;
	thread->context = thread_context;

	// Add the created thread to the ready list
	AppendFila2(ready, (void*) thread);
}

void threat_end_of_thread() {

}

void select_thread_and_execute() {
	TCB_t *selected_thread, *current_thread;

	// Take a thread on the ready list
	FirstFila2(ready);
	selected_thread = (TCB_t*) GetAtIteratorFila2(ready);
	DeleteAtIteratorFila2(ready);
	AppendFila2(running, selected_thread);

	// Take the thread on the running list
	FirstFila2(running);
	current_thread = (TCB_t*) GetAtIteratorFila2(running);
	DeleteAtIteratorFila2(running);
	AppendFila2(ready, current_thread);

	swapcontext(&(current_thread->context), &(selected_thread->context));
	printf("Bola\n");
}
