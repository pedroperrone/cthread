// Expected output:
// 	yield in the main should not cause errors.
// 	Thread 1, with priority 0, starts.
// 	Thread 2, with priority 0, created. Thread 1 yields.
// 	Thread 2, with priority 0, starts.
// 	Thread 3, with priority 1, created.
// 	I am the thread 2. I am endind and should be the first one to end.
// 	Thread 1 yield again.
// 	I am the thread 1. I am endind and should be the second to end.
// 	Thread 3, with priority 1, starts.
// 	I am the thread 3. I am endind and should be the last to end.

#include <stdio.h>
#include "../include/cthread.h"

void thread_one();
void thread_two();
void thread_three();

int main() {
	int thread_tcb;
	cyield();
	printf("yield in the main should not cause errors.\n");
	thread_tcb = ccreate((void*) thread_one, NULL, 0);
	if(thread_tcb == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	return 0;
}

void thread_one() {
	printf("Thread 1, with priority 0, starts.\n");
	if(ccreate((void*) thread_two, NULL, 0) == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("Thread 2, with priority 0, created. Thread 1 yields.\n");
	if(cyield() == -1) {
		printf("UNEXPECTED error yielding.\n");
	}
	if(cyield() == -1) {
		printf("UNEXPECTED error yielding.\n");
	}
	printf("Thread 1 yield again.\n");
	printf("I am the thread 1. I am endind and should be the second to end.\n");
}

void thread_two() {
	printf("Thread 2, with priority 0, starts.\n");
	if(ccreate((void*) thread_three, NULL, 1) == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("Thread 3, with priority 1, created.\n");
	printf("I am the thread 2. I am endind and should be the first one to end.\n");
}

void  thread_three() {
	printf("Thread 3, with priority 1, starts.\n");
	printf("I am the thread 3. I am endind and should be the last to end.\n");
}