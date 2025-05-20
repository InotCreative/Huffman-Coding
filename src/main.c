#include <stdio.h>
#include "dynamic_array.h"
#include "file_read.h"
#include "huffman.h"

int main(int argc, char const *argv[]) {
    DynamicArray array;
    //BinaryTreeNode *huffmanTree = NULL;;

    initDynamicArray(&array);
    countFileCharacters(&array, "test.txt");
    array.printArray(&array);

    pop(&array, 0);
    array.printArray(&array);

    array.freeArray(&array);
    
    return 0;
}
