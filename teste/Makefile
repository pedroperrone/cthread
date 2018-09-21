#
# Makefile de EXEMPLO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# É NECESSARIO ADAPTAR ESSE ARQUIVO de makefile para suas necessidades.
#  1. Cuidado com a regra "clean" para não apagar o "support.o"
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "cthread"
# 

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=../bin
SRC_DIR=./src

all: cthread_test cyield_test csetprio_test cjoin_test sem_test quicksort

cthread_test: cthread_test.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o
	$(CC) -o teste cthread_test.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o $(BIN_DIR)/support.o -Wall
cthread_test.o: cthread_test.c
	$(CC) -c cthread_test.c -Wall

cyield_test: cyield_test.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o
	$(CC) -o cyield_test cyield_test.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o $(BIN_DIR)/support.o
cyield_test.o: cyield_test.c
	$(CC) -c cyield_test.c -Wall

csetprio_test: csetprio_test.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o
	$(CC) -o csetprio_test csetprio_test.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o $(BIN_DIR)/support.o
csetprio_test.o: csetprio_test.c
	$(CC) -c csetprio_test.c -Wall

cjoin_test: cjoin_test.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o
	$(CC) -o cjoin_test cjoin_test.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o $(BIN_DIR)/support.o
cjoin_test.o: cjoin_test.c
	$(CC) -c cjoin_test.c -Wall

quicksort: quicksort.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o
	$(CC) -o quicksort quicksort.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o $(BIN_DIR)/support.o
quicksort.o: quicksort.c
	$(CC) -c quicksort.c -Wall

sem_test: sem_test.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o
	$(CC) -o sem_test sem_test.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o $(BIN_DIR)/support.o
sem_test.o: sem_test.c
	$(CC) -c sem_test.c -Wall

