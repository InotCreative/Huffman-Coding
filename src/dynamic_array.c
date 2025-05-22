#include "dynamic_array.h"
#include "huffman.h"
#include <stdlib.h>

void initLetterNode(LetterNode *node, char letter) {
    node->character = letter;
    node->quantityOfCharacters = 1;
}

void growArray(DynamicArray *array) {
    if (array->size == 0) {
        array->capacity = INITIAL_SIZE;
        array->nodeAddressArray = malloc(INITIAL_SIZE * sizeof(void *));
        TEST(array->nodeAddressArray, NULL, "malloc");
        return;
    }

    if (array->size + 1 > array->capacity) {
        size_t new_capacity = array->capacity * 2;
        void **temp = realloc(array->nodeAddressArray, new_capacity * sizeof(void *));
        TEST(temp, NULL, "realloc");

        if (temp == NULL) return;
        array->nodeAddressArray = temp;
        array->capacity = new_capacity;
    }
}

void push(DynamicArray *array, void *address) {
    growArray(array);
    array->nodeAddressArray[array->size] = address;
    array->size++;
}

void freeArray(DynamicArray *array) {
    for (int i = 0; i < array->size; i++) {
        if (array->nodeAddressArray[i] != NULL) {
            free(array->nodeAddressArray[i]);
        }
    }

    free(array->nodeAddressArray);
}

void printArray(DynamicArray *array, int flag) {
    if (flag == 0) {
        for (int i = 0; i < array->size; i++) {
            printf("ADDRESS: %p | CHARACTER: %c | COUNT: %ld\n", array->nodeAddressArray[i], ((LetterNode *)array->nodeAddressArray[i])->character, ((LetterNode *)array->nodeAddressArray[i])->quantityOfCharacters);
        }

        printf("SIZE: %ld\n", array->size);
        printf("CAPACITY: %ld\n", array->capacity);
        printf("\n");
    } else {
        for (int i = 0; i < array->size; i++) {
            printf("ADDRESS: %p\n", array->nodeAddressArray[i]);
        }
    }
}

void swap(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

int partition(DynamicArray *array, int low, int high, int flag) {
    int pivot;
    
    if (flag == 0) {
        pivot = ((LetterNode *)array->nodeAddressArray[high])->quantityOfCharacters;
    } else {
        pivot = ((BinaryTreeNode *)array->nodeAddressArray[high])->node->quantityOfCharacters;
    }

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (flag == 0) {
            if (((LetterNode *)array->nodeAddressArray[j])->quantityOfCharacters <= pivot) {
                i++;
                swap(&array->nodeAddressArray[i], &array->nodeAddressArray[j]);
            }
        } else {
            if (((BinaryTreeNode *)array->nodeAddressArray[j])->node->quantityOfCharacters <= pivot) {
                i++;
                swap(&array->nodeAddressArray[i], &array->nodeAddressArray[j]);
            }
        }
    }

    swap(&array->nodeAddressArray[i + 1], &array->nodeAddressArray[high]);
    return i + 1;
}

void quickSort(DynamicArray *array, int low, int high, int flag) {
    if (low < high) {
        int pi = partition(array, low, high, flag);
        quickSort(array, low, pi - 1, flag);
        quickSort(array, pi + 1, high, flag);
    }
}

void *pop(DynamicArray *array, int index) {
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
    array->capacity = 0;
    array->nodeAddressArray = NULL;

    array->printArray = printArray;
    array->push = push;
    array->freeArray = freeArray;
    array->quickSort = quickSort;
    array->pop = pop;
}