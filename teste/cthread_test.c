// Expected output:
// 	I am the main thread.
// 	Thread 1, with priority 0, starts.
// 	Thread 1 ends.
// 	Thread 2, with priority 2, starts.
// 	Thread 3, with priority 1, starts.
// 	Thread 3 ends.
// 	Thread 2 ends.
//	The execution came back to the main
//	Even after returning to the main, you can create new threads.
//	Expected error, thread with negative priority.
//	Expected error, thread with priority too big.
// 	I am the main thread. Now that all the created threads are finished, I execute again.

#include <stdio.h>
#include "../include/cthread.h"

void thread_one();
void thread_two();
void thread_three();
void extra_thread();

int main() {
	int thread_tcb;
	printf("I am the main thread.\n");
	thread_tcb = ccreate((void*) thread_one, NULL, 0);
	if(thread_tcb == -1) {
		printf("UNEXPECTED error creating the new thread.\n");
	}
	printf("The execution came back to the main.\n");
	thread_tcb = ccreate((void*) extra_thread, NULL, 0);
	if(thread_tcb == -1) {
		printf("UNEXPECTED error creating the new thread.\n");
	}
	thread_tcb = ccreate((void*) extra_thread, NULL, -1);
	if(thread_tcb == -1) {
		printf("Expected error, thread with negative priority.\n");
	}
	thread_tcb = ccreate((void*) extra_thread, NULL, 3);
	if(thread_tcb == -1) {
		printf("Expected error, thread with priority too big.\n");
	}
	printf("I am the main thread. Now that all the created threads are finished, I execute again.\n");
	return 0;
}

void thread_one() {
	int tcb;
	printf("Thread 1, with priority 0, starts.\n");
	tcb = ccreate((void*) thread_two, NULL, 2);
	if(tcb == -1) {
		printf("Error creating thread 2.\n");
	}
	printf("Thread 1 ends.\n");
}

void thread_two() {
	int tcb;
	printf("Thread 2, with priority 2, starts\n");
	tcb = ccreate((void*) thread_three, NULL, 1);
	if(tcb == -1) {
		printf("Error creating thread 3\n");
	}
	printf("Thread 2 ends.\n");
}

void thread_three() {
	printf("Thread 3, with priority 1, starts\n");
	printf("Thread 3 ends.\n");
}

void extra_thread() {
	printf("Even after returning to the main, you can create new threads.\n");
}
