#include "dynamic_array.h"
#include <stdlib.h>

void initLetterNode(LetterNode *node, char letter) {
    node->character = letter;
    node->quantityOfCharacters = 1;
}

void growArray(DynamicArray *array) {
    if (array->size == 0) {
        array->capacity = INITIAL_SIZE;
        array->nodeAddressArray = (void **)malloc(INITIAL_SIZE * sizeof(void *));
        TEST(array->nodeAddressArray, NULL, "malloc");
        return;
    }

    if (array->size + 1 > array->capacity) {
        array->capacity *= 2;
        array->nodeAddressArray = (void **)realloc(array->nodeAddressArray, array->capacity * sizeof(void *));
        TEST(array->nodeAddressArray, NULL, "realloc");
    }
}

void push(DynamicArray *array, void *address) {
    growArray(array);
    array->nodeAddressArray[array->size] = address;
    array->size++;
}

void freeArray(DynamicArray *array) {
    for (int i = 0; i < array->size; i++) {
        free(array->nodeAddressArray[i]);
    }

    free(array->nodeAddressArray);
}

void printArray(DynamicArray *array) {
    for (int i = 0; i < array->size; i++) {
        printf("ADDRESS: %p | CHARACTER: %c | COUNT: %ld\n", array->nodeAddressArray[i], ((LetterNode *)array->nodeAddressArray[i])->character, ((LetterNode *)array->nodeAddressArray[i])->quantityOfCharacters);
    }

    printf("SIZE: %ld\n", array->size);
    printf("CAPACITY: %ld\n", array->capacity);
    printf("\n");
}

void swap(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

int partition(DynamicArray *array, int low, int high) {
    int pivot = ((LetterNode *)array->nodeAddressArray[high])->quantityOfCharacters;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (((LetterNode *)array->nodeAddressArray[j])->quantityOfCharacters <= pivot) {
            i++;
            swap(&array->nodeAddressArray[i], &array->nodeAddressArray[j]);
        }
    }

    swap(&array->nodeAddressArray[i + 1], &array->nodeAddressArray[high]);
    return i + 1;
}

void quickSort(DynamicArray *array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

LetterNode *pop(DynamicArray *array, int index) {
    if (index < 0 || index >= array->size) return NULL;

    void *toRemove = array->nodeAddressArray[index];

    for (int i = index; i < array->size - 1; i++) {
        array->nodeAddressArray[i] = array->nodeAddressArray[i + 1];
    }

    array->size--;
    return toRemove;
}


void initDynamicArray(DynamicArray *array) {
    array->size = 0;
    array->capacity = 10;
    array->nodeAddressArray = NULL;

    array->printArray = printArray;
    array->push = push;
    array->freeArray = freeArray;
    array->quickSort = quickSort;
    array->pop = pop;
}