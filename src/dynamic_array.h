#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 8
#define TEST(testValue,comparason,message) {if (testValue == comparason) {perror(message); exit(EXIT_FAILURE);}}

typedef struct LetterNode {
    char character;
    size_t quantityOfCharacters;
} LetterNode;

typedef struct DynamicArray {
    size_t size;
    size_t capacity;

    void **nodeAddressArray;
    void (* push)(struct DynamicArray *, void *);
    void (* freeArray)(struct DynamicArray *);
    void (* printArray)(struct DynamicArray *);
    void (* quickSort)(struct DynamicArray *, int, int);
    LetterNode *(*pop)(struct DynamicArray *, int);

} DynamicArray;

void initLetterNode(LetterNode *node, char letter);
void initDynamicArray(DynamicArray *array);
void growArray(DynamicArray *array);
void push(DynamicArray *array, void *address);
void freeArray(DynamicArray *array);
void printArray(DynamicArray *array);
int partation(DynamicArray *array, int low, int high);
void quickSort(DynamicArray *array, int low, int high);
void swap(void **a, void **b);
LetterNode *pop(DynamicArray *array, int index);

#endif