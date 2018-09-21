// Expected output:
	// 1: I am the main thread.
	// 2: Thread 1, with priority 0, starts.
	// 3: Thread 1 ends.
	// 4: Thread 2, with priority 0, starts
	// 5: Thread 2 ends.
	// 6: Thread 3, with priority 1, starts
	// 7: Thread 3 ends.
	// 8: The execution came back to the main.
	// 9: Even after returning to the main, you can create new threads.
	// 10: Thread 4, with priority 2, starts
	// 11: Main was preempted when created a new thread, so I can run.
	// 12: Thread 4 ends.
	// 13: Expected error, thread with negative priority.
	// 14: Expected error, thread with priority too big.

#include <stdio.h>
#include "../include/cthread.h"

void thread_one();
void thread_two();
void thread_three();
void thread_four();
void extra_thread();

int main() {
	int thread_tcb;
	printf("1: I am the main thread.\n");
	thread_tcb = ccreate((void*) thread_one, NULL, 0);
	if(thread_tcb == -1) {
		printf("UNEXPECTED error creating the new thread.\n");
	}
	printf("8: The execution came back to the main.\n");
	thread_tcb = ccreate((void*) extra_thread, NULL, 0);
	if(thread_tcb == -1) {
		printf("UNEXPECTED error creating the new thread.\n");
	}
	thread_tcb = ccreate((void*) extra_thread, NULL, -1);
	if(thread_tcb == -1) {
		printf("13: Expected error, thread with negative priority.\n");
	}
	thread_tcb = ccreate((void*) extra_thread, NULL, 3);
	if(thread_tcb == -1) {
		printf("14: Expected error, thread with priority too big.\n");
	}
	return 0;
}

void thread_one() {
	int tcb;
	printf("2: Thread 1, with priority 0, starts.\n");
	tcb = ccreate((void*) thread_two, NULL, 0);
	if(tcb == -1) {
		printf("Error creating thread 2.\n");
	}
	printf("3: Thread 1 ends.\n");
}

void thread_two() {
	int tcb;
	printf("4: Thread 2, with priority 0, starts\n");
	tcb = ccreate((void*) thread_three, NULL, 1);
	if(tcb == -1) {
		printf("Error creating thread 3\n");
	}
	printf("5: Thread 2 ends.\n");
}

void thread_three() {
	printf("6: Thread 3, with priority 1, starts\n");
	if(ccreate((void*) thread_four, NULL, 2) == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("7: Thread 3 ends.\n");
}

void thread_four() {
	printf("10: Thread 4, with priority 2, starts\n");
	printf("11: Main was preempted when created a new thread, so I can run.\n");
	printf("12: Thread 4 ends.\n");
}

void extra_thread() {
	printf("9: Even after returning to the main, you can create new threads.\n");
}
