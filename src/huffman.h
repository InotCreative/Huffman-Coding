#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "dynamic_array.h"
#include "file_read.h"

typedef struct BinaryTreeNode {
    LetterNode *node;

    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

void init(BinaryTreeNode *tree);
void buildHuffmanTree(BinaryTreeNode **tree, DynamicArray *array, const char *filePath);

#endif