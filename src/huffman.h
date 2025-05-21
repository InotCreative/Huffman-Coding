#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "dynamic_array.h"
#include "file_handle.h"
#include <stdbool.h>

typedef struct BinaryTreeNode {
    LetterNode *node;

    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

typedef struct HuffmanCode {
    char letter;
    char code[1024];
} HuffmanCode;

DynamicArray buildHuffmanTree(const char *filePath);
void freeBinaryTreeNodes(BinaryTreeNode *root);
void finalCleanup(DynamicArray *array);

#endif