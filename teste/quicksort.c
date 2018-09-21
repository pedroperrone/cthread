// Expected output:
    // The listed printed should be sorted

#include <stdio.h>
#include "../include/cthread.h"

typedef struct quicksort_params {
    int* list;
    int start_index;
    int end_index;
} QUICKSORT_PARAMS;

void swap(int* number_a, int* number_b);
int partitionate(int list[], int start_index, int end_index);
void recursive_quicksort(int list[], int start_index, int end_index);
void quicksort(int list[], int list_size);
void print_array(int array[], int array_size);
void multi_threading_recursive_quicksort(void* params_pttr);
void multi_threading_quicksort(int list[], int list_size);
void set_quicksort_params(QUICKSORT_PARAMS* params_struct, int* list, int start_index, int end_index);

int main() {
    int numbers[] = {9, 5, 2, 99, 43, 6, 4, 45, 22, 13};
    printf("Array before sorting: \n");
    print_array(numbers, 10);
    multi_threading_quicksort(numbers, 10);
    printf("\nArray after sorting: \n");
    print_array(numbers, 10);
    return 0;
}

void print_array(int array[], int array_size) {
    int i;
    printf("[");
    for(i = 0; i < array_size - 1; i++) {
        printf("%d - ", array[i]);
    }
    printf("%d]\n", array[i]);
}

void swap(int* number_a, int* number_b) {
    int aux = *number_a;
    *number_a = *number_b;
    *number_b = aux;
}

int partitionate(int list[], int start_index, int end_index) {
    int i, smallers_limit = start_index + 1;
    for(i = start_index + 1; i <= end_index; i++) {
        if(list[i] < list[start_index]) {
            swap(&list[smallers_limit], &list[i]);
            smallers_limit++;
        }
    }
    return smallers_limit - 1;
}

void recursive_quicksort(int list[], int start_index, int end_index) {
    int pivot_correct_index;
    
    if(end_index <= start_index) {
        return;
    }
    pivot_correct_index = partitionate(list, start_index, end_index);
    swap(&list[pivot_correct_index], &list[start_index]);
    recursive_quicksort(list, start_index, pivot_correct_index - 1);
    recursive_quicksort(list, pivot_correct_index + 1, end_index);
}

void quicksort(int list[], int list_size) {
    recursive_quicksort(list, 0, list_size - 1);
}

void multi_threading_recursive_quicksort(void* params_pttr) {
    QUICKSORT_PARAMS params = *((QUICKSORT_PARAMS*) params_pttr);
    int pivot_correct_index, end_index = params.end_index, start_index = params.start_index;
    int* list = params.list;
    
    if(end_index <= start_index) {
        return;
    }
    pivot_correct_index = partitionate(list, start_index, end_index);
    swap(&list[pivot_correct_index], &list[start_index]);
    recursive_quicksort(list, start_index, pivot_correct_index - 1);
    recursive_quicksort(list, pivot_correct_index + 1, end_index);
    return;
}

void multi_threading_quicksort(int list[], int list_size) {
    QUICKSORT_PARAMS params_for_smallers, params_for_greaters;
    int pivot_correct_index, smallers_tid, greaters_tid;
    if(list_size == 0) {
        return;
    }
    csetprio(0, 0);
    pivot_correct_index = partitionate(list, 0, list_size - 1);
    swap(&list[pivot_correct_index], &list[0]);

    set_quicksort_params(&params_for_smallers, list, 0, pivot_correct_index - 1);
    set_quicksort_params(&params_for_greaters, list, pivot_correct_index + 1, list_size - 1);
    
    smallers_tid = ccreate((void*) multi_threading_recursive_quicksort, &params_for_smallers, 2);
    if(smallers_tid == -1) {
        printf("ERROR creating thread\n");
        csetprio(0, 2);
        return;
    }
    greaters_tid = ccreate((void*) multi_threading_recursive_quicksort, &params_for_greaters, 2);
    if(greaters_tid == -1) {
        printf("ERROR creating thread\n");
        csetprio(0, 2);
        return;
    }

    cjoin(smallers_tid);
    cjoin(greaters_tid);
    csetprio(0, 2);
}

void set_quicksort_params(QUICKSORT_PARAMS* params_struct, int* list, int start_index, int end_index) {
    params_struct->list = list;
    params_struct->start_index = start_index;
    params_struct->end_index = end_index;
}
