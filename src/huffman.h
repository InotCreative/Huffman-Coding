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

typedef struct HuffmanCodebook {
    BinaryTreeNode *node;
    DynamicArray *array;
} HuffmanCodebook;

BinaryTreeNode *buildHuffmanTree(BinaryTreeNode **tree, DynamicArray *array, const char *filePath);
void generateHuffmanCode(BinaryTreeNode **tree, DynamicArray *array);
void freeHuffmanTree(BinaryTreeNode *tree);
void printNode(BinaryTreeNode *root);

#endif