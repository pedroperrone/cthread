CC=gcc
LIB_DIR=../lib
FLAGS=-L$(LIB_DIR) -lcthread -Wall

all: cthread_test cyield_test csetprio_test cjoin_test sem_test quicksort

cthread_test: cthread_test.o $(LIB_DIR)/libcthread.a
	$(CC) -o teste cthread_test.o $(FLAGS)
cthread_test.o: cthread_test.c
	$(CC) -c cthread_test.c -Wall

cyield_test: cyield_test.o $(LIB_DIR)/libcthread.a
	$(CC) -o cyield_test cyield_test.o $(FLAGS)
cyield_test.o: cyield_test.c
	$(CC) -c cyield_test.c -Wall

csetprio_test: csetprio_test.o $(LIB_DIR)/libcthread.a
	$(CC) -o csetprio_test csetprio_test.o $(FLAGS)
csetprio_test.o: csetprio_test.c
	$(CC) -c csetprio_test.c -Wall

cjoin_test: cjoin_test.o $(LIB_DIR)/libcthread.a
	$(CC) -o cjoin_test cjoin_test.o $(FLAGS)
cjoin_test.o: cjoin_test.c
	$(CC) -c cjoin_test.c -Wall

quicksort: quicksort.o $(LIB_DIR)/libcthread.a
	$(CC) -o quicksort quicksort.o $(FLAGS)
quicksort.o: quicksort.c
	$(CC) -c quicksort.c -Wall

sem_test: sem_test.o $(LIB_DIR)/libcthread.a
	$(CC) -o sem_test sem_test.o $(FLAGS)
sem_test.o: sem_test.c
	$(CC) -c sem_test.c -Wall

clean:
	rm *.o teste cyield_test csetprio_test cjoin_test quicksort sem_test
