// Expected output:
	// 1: Yield having no other threads should not cause errors.
	// 2: A thread with the same priority as main should only execute after cyield(). Main yields here.
	// 3: Thread 1, with priority 2, starts.
	// 4: Thread 2, with priority 0, starts.
	// 5: Thread 2 created thread 3, with priority 1. Thread 2 yields.
	// 6: Thread 2 has the greatest priority and should keep executing just after yielding.
	// 7: Thread 3, with priority 1, starts.
	// 8: Thread 3 ends.
	// 9: This is thread 1 endind. It should execute only after main's second yield.

#include <stdio.h>
#include "../include/cthread.h"

void thread_one();
void thread_two();
void thread_three();

int main() {
	int thread_tcb;
	cyield();
	printf("1: Yield having no other threads should not cause errors.\n");
	thread_tcb = ccreate((void*) thread_one, NULL, 2);
	if(thread_tcb == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("2: A thread with the same priority as main should only \
execute after cyield(). Main yields here.\n");
	cyield();
	cyield();
	return 0;
}

void thread_one() {
	printf("3: Thread 1, with priority 2, starts.\n");
	if(ccreate((void*) thread_two, NULL, 0) == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("9: This is thread 1 endind. It should execute only after \
main's second yield.\n");
}

void thread_two() {
	printf("4: Thread 2, with priority 0, starts.\n");
	if(ccreate((void*) thread_three, NULL, 1) == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("5: Thread 2 created thread 3, with priority 1. Thread 2 yields.\n");
	cyield();
	printf("6: Thread 2 has the greatest priority and should keep \
executing just after yielding.\n");
}

void  thread_three() {
	printf("7: Thread 3, with priority 1, starts.\n");
	printf("8: Thread 3 ends.\n");
}