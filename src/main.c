#include <stdio.h>
#include "dynamic_array.h"
#include "file_handle.h"
#include "huffman.h"

int main(int argc, char const *argv[]) {
    DynamicArray array;
    //BinaryTreeNode *huffmanTree = NULL;;

    initDynamicArray(&array);
    
    BinaryTreeNode *root = buildHuffmanTree(&root, &array, "test.txt");

    printNode(root);

    array.printArray(&array);
    array.freeArray(&array);
    
    return 0;
}
