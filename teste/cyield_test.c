// Expected output:
// Yield having no other threads should not cause errors.
// A thread with the same priority as main should only execute after cyield(). Main yields here.
// Thread 1, with priority 2, starts.
// Thread 2, with priority 0, starts.
// Thread 2 created thread 3, with priority 1. Thread 2 yields.
// Thread 2 has the greatest priority and should keep executing just after yielding.
// Thread 3, with priority 1, starts.
// Thread 3 ends.
// This is thread 1 endind. It should execute only after main's second yield.

#include <stdio.h>
#include "../include/cthread.h"

void thread_one();
void thread_two();
void thread_three();

int main() {
	int thread_tcb;
	cyield();
	printf("Yield having no other threads should not cause errors.\n");
	thread_tcb = ccreate((void*) thread_one, NULL, 2);
	if(thread_tcb == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("A thread with the same priority as main should only \
execute after cyield(). Main yields here.\n");
	cyield();
	cyield();
	return 0;
}

void thread_one() {
	printf("Thread 1, with priority 2, starts.\n");
	if(ccreate((void*) thread_two, NULL, 0) == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("This is thread 1 endind. It should execute only after \
main's second yield.\n");
	// printf("Thread 2, with priority 0, created. Thread 1 yields.\n");
	// if(cyield() == -1) {
	// 	printf("UNEXPECTED error yielding.\n");
	// }
	// if(cyield() == -1) {
	// 	printf("UNEXPECTED error yielding.\n");
	// }
	// printf("Thread 1 yield again.\n");
	// printf("I am the thread 1. I am endind and should be the second to end.\n");
}

void thread_two() {
	printf("Thread 2, with priority 0, starts.\n");
	if(ccreate((void*) thread_three, NULL, 1) == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("Thread 2 created thread 3, with priority 1. Thread 2 yields.\n");
	cyield();
	printf("Thread 2 has the greatest priority and should keep \
executing just after yielding.\n");
}

void  thread_three() {
	printf("Thread 3, with priority 1, starts.\n");
	printf("Thread 3 ends.\n");
}