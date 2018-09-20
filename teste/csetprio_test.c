// Expected output:
	// As expected, main thread can't set prio.
	// Thread 1, with priority 0, starts.
	// Thread 1 sets prio to 2.
	// Thread 2, with priority 1, starts.
	// Thread 2, with priority 1, ends.
	// Thread 3, with priority 1, starts.
	// Thread 3 sets prio to 2
	// Thread 3 ends.
	// Thread 1 ends.

#include <stdio.h>
#include "../include/cthread.h"

void thread_one();
void thread_two();
void thread_three();

int main() {
	int thread_tcb;
	if(csetprio(0, 1) == -1) {
		printf("As expected, main thread can't set prio.\n");
	} else {
		printf("ERROR: main thread shouldn't be able to set prio.\n");
	}
	thread_tcb = ccreate((void*) thread_one, NULL, 0);
	if(thread_tcb == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	return 0;
}

void thread_one() {
	printf("Thread 1, with priority 0, starts.\n");
	if(ccreate((void*) thread_two, NULL, 1) == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	if(ccreate((void*) thread_three, NULL, 1) == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("Thread 1 sets prio to 2.\n");
	if(csetprio(0, 2) == -1) {
		printf("UNEXPECTED error setting prio.\n");
	}
	printf("Thread 1 ends.\n");
}

void thread_two() {
	printf("Thread 2, with priority 1, starts.\n");
	printf("Thread 2, with priority 1, ends.\n");
}

void  thread_three() {
	printf("Thread 3, with priority 1, starts.\n");
	printf("Thread 3 sets prio to 2\n");
	if(csetprio(0, 2) == -1) {
		printf("UNEXPECTED error setting prio.\n");
	}
	printf("Thread 3 ends.\n");
}