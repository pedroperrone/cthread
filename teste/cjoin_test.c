// Expected output:
	// Thread 1, with priority 0, starts.
	// Thread 2, with priority 1, created. Thread 1 joins.
	// Thread 2, with priority 1, starts.
	// Thread 3, with priority 1, created. Thread 2 joins.
	// Thread 3, with priority 1, starts.
	// Thread 3 ends.
	// Thread 2 joined thread with same priority.
	// Thread 2, with priority 1, ends.
	// Thread 1 joined thread with lower priority.
	// Thread 1 ends.
	// Mains join should return error because new thread is ended.

#include <stdio.h>
#include "../include/cthread.h"

void thread_one();
void thread_two();
void thread_three();

int main() {
	int thread_tcb = ccreate((void*) thread_one, NULL, 0);
	if(thread_tcb == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	if(cjoin(thread_tcb) == -1) {
		printf("Mains join should return error because new thread is ended.\n");
	} else {
		printf("ERROR: Main's join should return -1.\n");
	}
	return 0;
}

void thread_one() {
	int tid;
	printf("Thread 1, with priority 0, starts.\n");
	tid = ccreate((void*) thread_two, NULL, 1);
	if(tid == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("Thread 2, with priority 1, created. Thread 1 joins.\n");
	if(cjoin(tid) == -1) {
		printf("ERROR on join.\n");
	}
	printf("Thread 1 joined thread with lower priority.\n");
	printf("Thread 1 ends.\n");
}

void thread_two() {
	int tid;
	printf("Thread 2, with priority 1, starts.\n");
	tid = ccreate((void*) thread_three, NULL, 1);
	if(tid == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("Thread 3, with priority 1, created. Thread 2 joins.\n");
	if(cjoin(tid) == -1) {
		printf("ERROR on join.\n");
	}
	printf("Thread 2 joined thread with same priority.\n");
	printf("Thread 2, with priority 1, ends.\n");
}

void  thread_three() {
	printf("Thread 3, with priority 1, starts.\n");
	printf("Thread 3 ends.\n");
}