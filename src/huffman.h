#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "dynamic_array.h"
#include "file_handle.h"

#include <stdbool.h>
#include <string.h>

typedef struct BinaryTreeNode {
    LetterNode *node;

    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

typedef struct HuffmanCode {
    char letter;
    char *code;
} HuffmanCode;

DynamicArray buildHuffmanTree(const char *filePath);
void freeBinaryTreeNodes(BinaryTreeNode *root);
void huffmanTreeCleanup(DynamicArray *array);
void huffmanArrayCleanup(DynamicArray *array);
DynamicArray initHuffmanCode(const char *filePath);
void traverseHuffmanTree(BinaryTreeNode *node, char *prefix, int depth, DynamicArray *huffmanCodes);
void generateHuffmanCodes(DynamicArray *huffmanCodes, DynamicArray *huffmanTreeRoot);
int getHuffmanLength(BinaryTreeNode *root);

#endif