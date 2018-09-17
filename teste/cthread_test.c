// Expected output:
// 	I am the main thread.
// 	Thread 1, with priority 0, starts.
// 	Thread 1 ends.
// 	Thread 2, with priority 2, starts.
// 	Thread 3, with priority 1, starts.
// 	Thread 3 ends.
// 	Thread 2 ends.
// 	I am the main thread. Now that all the created threads are finished, I execute again.

#include <stdio.h>
#include "../include/cthread.h"

void thread_one();
void thread_two();
void thread_three();

int main() {
	int thread_tcb;
	printf("I am the main thread.\n");
	thread_tcb = ccreate((void*) thread_one, NULL, 0);
	if(thread_tcb == -1) {
		printf("Error creating the new thread.\n");
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
