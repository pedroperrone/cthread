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

all: cthread_test cyield_test

cthread_test: cthread_test.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o
	$(CC) -o teste cthread_test.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o $(BIN_DIR)/support.o -Wall
cthread_test.o: cthread_test.c
	$(CC) -c cthread_test.c -Wall

cyield_test: cyield_test.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o
	$(CC) -o cyield_test cyield_test.o $(BIN_DIR)/cthread.o $(BIN_DIR)/scheduler.o $(BIN_DIR)/support.o
cyield_test.o: cyield_test.c
	$(CC) -c cyield_test.c -Wall
