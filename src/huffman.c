#include "huffman.h"

DynamicArray buildHuffmanTree(const char *filePath) {
    DynamicArray lettersAndFrequency;
    initDynamicArray(&lettersAndFrequency);

    countFileCharacters(&lettersAndFrequency, filePath);
    lettersAndFrequency.quickSort(&lettersAndFrequency, 0, lettersAndFrequency.size - 1, 0);

    DynamicArray treeArray;
    initDynamicArray(&treeArray);

    for (int i = 0; i < lettersAndFrequency.size; i++) {
        LetterNode *ln = (LetterNode *)lettersAndFrequency.nodeAddressArray[i];
        BinaryTreeNode *btn = malloc(sizeof(BinaryTreeNode));
        btn->left = NULL;
        btn->right = NULL;
        btn->node = ln;
        treeArray.push(&treeArray, btn);
    }


    while (treeArray.size > 1) {
        BinaryTreeNode *left = (BinaryTreeNode *)treeArray.pop(&treeArray, 0);
        BinaryTreeNode *right = (BinaryTreeNode *)treeArray.pop(&treeArray, 0);

        BinaryTreeNode *merged = malloc(sizeof(BinaryTreeNode));
        merged->left = left;
        merged->right = right;
        merged->node = malloc(sizeof(LetterNode));
        merged->node->character = '\0';
        merged->node->quantityOfCharacters = left->node->quantityOfCharacters + right->node->quantityOfCharacters;

        treeArray.push(&treeArray, merged);
        treeArray.quickSort(&treeArray, 0, treeArray.size - 1, 1);
    }

    free(lettersAndFrequency.nodeAddressArray);
    return treeArray;
}

void freeBinaryTreeNodes(BinaryTreeNode *root) {
    if (root == NULL) return;

    freeBinaryTreeNodes(root->left);
    freeBinaryTreeNodes(root->right);

    if (root != NULL) {
        free(root->node);
    }

    free(root);
}

void finalCleanup(DynamicArray *array) {
    freeBinaryTreeNodes((BinaryTreeNode *)array->nodeAddressArray[0]);
    free(array->nodeAddressArray);
}