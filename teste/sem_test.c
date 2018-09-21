// Expected output:
// 
// Main thread started
// 1: thread 1 started with medium priority
// 2: thread 1 has entered a critial section
// 3: thread 2 has been created with higher priority than thread 1
// 4: thread 2 started with high priority
// 5: thread 1 has left a critical section
// 6: thread 2 has entered a critical section
// 7: thread 3 has been created with medium priority
// 8: thread 2 has left a critical section
// 9: thread 2 ended
// 10: thread 1 ended
// 11: thread 3 started with medium priority
// 12: thread 3 has entered a critial section
// 13: thread 4 has been created with medium priority
// 14: thread 5 has been created with high priority
// 15: thread 5 started with high priority
// 16: thread 4 started with medium priority
// 17: thread 3 has left a critical section
// 18: thread 5 has entered a critial section
// 19: thread 5 has left a critical section
// 20: thread 5 ended
// 21: thread 3 ended
// 22: thread 4 has entered a critial section
// 23: thread 4 has left a critical section
// 24: thread 4 ended
// Main thread ended

#include <stdio.h>
#include "../include/cthread.h"

void thread_one(csem_t *sem);
void thread_two(csem_t *sem);
void thread_three(csem_t *sem);
void thread_four(csem_t *sem);
void thread_five(csem_t *sem);

int main() {
	csem_t sem;
	int thread_tcb;

	csem_init(&sem, 1);

	printf("\nMain thread started\n");
	thread_tcb = ccreate((void*) thread_one, &sem, 1);
	if(thread_tcb == -1) {
		printf("UNEXPECTED error creating the new thread.\n");
	}
	
	printf("Main thread ended\n\n");
	return 0;
}

void thread_one(csem_t *sem) {
	printf("1: thread 1 started with medium priority\n");
	cwait(sem);
	printf("2: thread 1 has entered a critial section\n");
	printf("3: thread 2 has been created with higher priority than thread 1\n");
	ccreate((void*) thread_two, sem, 0);
	printf("5: thread 1 has left a critical section\n");
	csignal(sem);
	printf("10: thread 1 ended\n");
}

void thread_two(csem_t *sem) {
	printf("4: thread 2 started with high priority\n");
	cwait(sem);
	printf("6: thread 2 has entered a critical section\n");
	printf("7: thread 3 has been created with medium priority\n");
	ccreate((void*) thread_three, sem, 1);
	printf("8: thread 2 has left a critical section\n");
	csignal(sem);
	printf("9: thread 2 ended\n");
}

void thread_three(csem_t *sem) {
	printf("11: thread 3 started with medium priority\n");
	cwait(sem);
	printf("12: thread 3 has entered a critial section\n");
	printf("13: thread 4 has been created with medium priority\n");
	ccreate((void*) thread_four, sem, 1);
	printf("14: thread 5 has been created with high priority\n");
	ccreate((void*) thread_five, sem, 0);
	printf("17: thread 3 has left a critical section\n");
	csignal(sem);
	printf("21: thread 3 ended\n");
}

void thread_four(csem_t *sem) {
	printf("16: thread 4 started with medium priority\n");
	cwait(sem);
	printf("22: thread 4 has entered a critial section\n");
	printf("23: thread 4 has left a critical section\n");
	csignal(sem);
	printf("24: thread 4 ended\n");
}

void thread_five(csem_t *sem) {
	printf("15: thread 5 started with high priority\n");
	cwait(sem);
	printf("18: thread 5 has entered a critial section\n");
	printf("19: thread 5 has left a critical section\n");
	csignal(sem);
	printf("20: thread 5 ended\n");
}
