// Expected output:
	// 1: Thread 1, with priority 0, starts.
	// 2: Thread 1 sets prio to 1.
	// 3: Thread 2, with priority 0, starts.
	// 4: Thread 2 ends.
	// 5: Thread 3, with priority 0, starts.
	// 6: Thread 3 sets prio to 1
	// 7: Thread 3 should end before thread 1. Thread 3 ends.
	// 8: Thread 1 ends.

#include <stdio.h>
#include "../include/cthread.h"

void thread_one();
void thread_two();
void thread_three();
void thread_four();

int main() {
	int thread_tcb;
	thread_tcb = ccreate((void*) thread_one, NULL, 0);
	if(thread_tcb == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	csetprio(0, 0);
	thread_tcb = ccreate((void*) thread_four, NULL, 0);
	return 0;
}

void thread_one() {
	printf("1: Thread 1, with priority 0, starts.\n");
	if(ccreate((void*) thread_two, NULL, 0) == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	if(ccreate((void*) thread_three, NULL, 0) == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("2: Thread 1 sets prio to 1.\n");
	if(csetprio(0, 1) == -1) {
		printf("UNEXPECTED error setting prio.\n");
	}
	printf("8: Thread 1 ends.\n");
}

void thread_two() {
	printf("3: Thread 2, with priority 0, starts.\n");
	printf("4: Thread 2 ends.\n");
}

void  thread_three() {
	printf("5: Thread 3, with priority 0, starts.\n");
	printf("6: Thread 3 sets prio to 1\n");
	if(csetprio(0, 1) == -1) {
		printf("UNEXPECTED error setting prio.\n");
	}
	printf("7: Thread 3 should end before thread 1. Thread 3 ends.\n");
}

void thread_four() {
	printf("ERROR: thread 4 should not be executed.\n");
}