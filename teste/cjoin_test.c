// Expected output:
	// 1: Thread 1, with priority 0, starts.
	// 2: Thread 2, with priority 1, created. Thread 1 joins.
	// 3: Thread 2, with priority 1, starts.
	// 4: Thread 3, with priority 1, created. Thread 2 joins.
	// 5: Thread 3, with priority 1, starts.
	// 6: Thread 3 ends.
	// 7: Thread 2 joined thread with same priority.
	// 8: Thread 2, with priority 1, ends.
	// 9: Thread 1 joined thread with lower priority.
	// 10: Thread 1 create threads 4 and 5 and yields.
	// 11: Thread 4 yields so 5 can join.
	// 12: Thread 5 joins thread 4.
	// 13: Thread 1 joins 5
	// 14: Thread 4 ends and frees thread 5
	// 15: Thread 5 ends ends and frees thread 1.
	// 16: Thread 1 ends.
	// 17: Mains join should return error because new thread is ended.

#include <stdio.h>
#include "../include/cthread.h"

void thread_one();
void thread_two();
void thread_three();
void thread_four();
void thread_five(int *tid);

int main() {
	int thread_tcb = ccreate((void*) thread_one, NULL, 0);
	if(thread_tcb == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	if(cjoin(thread_tcb) == -1) {
		printf("17: Mains join should return error because new thread is ended.\n");
	} else {
		printf("ERROR: Main's join should return -1.\n");
	}
	return 0;
}

void thread_one() {
	int tid, tid_two;
	printf("1: Thread 1, with priority 0, starts.\n");
	tid = ccreate((void*) thread_two, NULL, 1);
	if(tid == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("2: Thread 2, with priority 1, created. Thread 1 joins.\n");
	if(cjoin(tid) == -1) {
		printf("ERROR on join.\n");
	}
	printf("9: Thread 1 joined thread with lower priority.\n");
	tid = ccreate((void*) thread_four, NULL, 0);
	if(tid == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	tid_two = ccreate((void*) thread_five, &tid, 0);
	if(tid_two == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("10: Thread 1 create threads 4 and 5 and yields.\n");
	cyield();
	printf("13: Thread 1 joins 5\n");
	cjoin(tid_two);
	printf("16: Thread 1 ends.\n");
}

void thread_two() {
	int tid;
	printf("3: Thread 2, with priority 1, starts.\n");
	tid = ccreate((void*) thread_three, NULL, 1);
	if(tid == -1) {
		printf("UNEXPECTED error creating thread.\n");
	}
	printf("4: Thread 3, with priority 1, created. Thread 2 joins.\n");
	if(cjoin(tid) == -1) {
		printf("ERROR on join.\n");
	}
	printf("7: Thread 2 joined thread with same priority.\n");
	printf("8: Thread 2, with priority 1, ends.\n");
}

void  thread_three() {
	printf("5: Thread 3, with priority 1, starts.\n");
	printf("6: Thread 3 ends.\n");
}

void thread_four() {
	printf("11: Thread 4 yields so 5 can join.\n");
	cyield();
	printf("14: Thread 4 ends and frees thread 5\n");

}

void thread_five(int *tid) {
	printf("12: Thread 5 joins thread 4.\n");
	cjoin(*tid);
	printf("15: Thread 5 ends ends and frees thread 1.\n");
}