// Expected output:
	// Bruno Santana Massena de Lima - 274711
	// Pedro Salgado Perrone - 274696

#include <stdio.h>
#include "../include/cthread.h"

#define NAMES_SIZE 100

int main() {
	char names[NAMES_SIZE + 1];
	cidentify(names, NAMES_SIZE);
	printf("%s\n", names);
	return 0;
}
