#include <stdio.h>
#include "../include/cthread.h"

void thread();

int main() {
	int thread_tcb;
	printf("I am the main thread.\n");
	thread_tcb = ccreate((void*) thread, NULL, 1);
	if(thread_tcb == -1) {
		printf("Error creating the new thread.\n");
	}
	printf("I am the main thread. Now that all the created threads are finished, I execute again.\n");
	return 0;
}

void thread() {
	printf("This is the new thread.\n");
}