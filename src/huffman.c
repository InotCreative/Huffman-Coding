#include "huffman.h"

void init(BinaryTreeNode *tree) {
    tree->node  = NULL;
    tree->left  = NULL;
    tree->right = NULL;
}

void buildHuffmanTree(BinaryTreeNode **tree, DynamicArray *array, const char *filePath) {
    countFileCharacters(array, filePath);
    //array->printArray(array);
    
    array->quickSort(array, 0, array->size - 1);
    //array->printArray(array);

    while (array->size > 1) {
        LetterNode *left = array->pop(array, 0);
        LetterNode *right = array->pop(array, 0);
    }
}