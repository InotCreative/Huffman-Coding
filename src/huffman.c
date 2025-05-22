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
        TEST(btn, NULL, "MALLOC");
        btn->left = NULL;
        btn->right = NULL;
        btn->node = ln;
        treeArray.push(&treeArray, btn);
    }

    while (treeArray.size > 1) {
        /*
        Note:
            * A huffman tree will take the two smallest nodes, and merge them together to make an internal node.
            * Within a huffman tree only a leaf node will contain the character and frequency.
        */

        BinaryTreeNode *left = (BinaryTreeNode *)treeArray.pop(&treeArray, 0);
        BinaryTreeNode *right = (BinaryTreeNode *)treeArray.pop(&treeArray, 0);

        BinaryTreeNode *merged = malloc(sizeof(BinaryTreeNode));
        TEST(merged, NULL, "MALLOC");
        merged->left = left;
        merged->right = right;
        merged->node = malloc(sizeof(LetterNode));
        TEST(merged->node, NULL, "MALLOC");
        merged->node->character = '\0';
        merged->node->quantityOfCharacters = left->node->quantityOfCharacters + right->node->quantityOfCharacters;

        treeArray.push(&treeArray, merged);
        treeArray.quickSort(&treeArray, 0, treeArray.size - 1, 1);
    }

    return treeArray;
}

int getHuffmanLength(BinaryTreeNode *root) {
    if (root == NULL) return 0;

    int leftDepth = getHuffmanLength(root->left);
    int rightDepth = getHuffmanLength(root->right);

    return 1 + ((leftDepth > rightDepth) ? leftDepth : rightDepth);
}

DynamicArray initHuffmanCode(const char *filePath) {
    DynamicArray huffmanCodeArray;
    DynamicArray characterCounts;
    DynamicArray huffmanTree = buildHuffmanTree(filePath);

    initDynamicArray(&huffmanCodeArray);
    initDynamicArray(&characterCounts);

    countFileCharacters(&characterCounts, filePath);

    for (int i = 0; i < characterCounts.size; i++) {
        HuffmanCode *huffmanCode = (HuffmanCode *)malloc(sizeof(HuffmanCode));
        TEST(huffmanCode, NULL, "MALLOC");
        huffmanCode->code = NULL;
        huffmanCode->letter = ((LetterNode *)characterCounts.nodeAddressArray[i])->character;

        huffmanCodeArray.push(&huffmanCodeArray, huffmanCode);
    }

    characterCounts.freeArray(&characterCounts);
    return huffmanCodeArray;
}

void traverseHuffmanTree(BinaryTreeNode *node, char *prefix, int depth, DynamicArray *huffmanCodes) {
    if (node == NULL) return;

    if (node->left == NULL && node->right == NULL && node->node->character != '\0') {
        prefix[depth] = '\0';

        for (int i = 0; i < huffmanCodes->size; i++) {
            HuffmanCode *hc = (HuffmanCode *)huffmanCodes->nodeAddressArray[i];
            if (hc->letter == node->node->character) {
                hc->code = strdup(prefix);
                break;
            }
        }

        return;
    }

    prefix[depth] = '0';
    traverseHuffmanTree(node->left, prefix, depth + 1, huffmanCodes);

    prefix[depth] = '1';
    traverseHuffmanTree(node->right, prefix, depth + 1, huffmanCodes);
}

void generateHuffmanCodes(DynamicArray *huffmanCodes, DynamicArray *huffmanTreeRoot) {
    int sizeOfHuffmantree = getHuffmanLength(((BinaryTreeNode *)huffmanTreeRoot->nodeAddressArray[0]));

    char *prefix = (char *)malloc((sizeOfHuffmantree + 1) * sizeof(char));
    TEST(prefix, "NULL", "MALLOC");

    traverseHuffmanTree(((BinaryTreeNode *)huffmanTreeRoot->nodeAddressArray[0]), prefix, 0, huffmanCodes);

    free(prefix);
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

void huffmanTreeCleanup(DynamicArray *array) {
    freeBinaryTreeNodes((BinaryTreeNode *)array->nodeAddressArray[0]);
    free(array->nodeAddressArray);
}

void huffmanArrayCleanup(DynamicArray *array) {
    for (int i = 0; i < array->size; i++) {
        free(((HuffmanCode *)array->nodeAddressArray[i])->code);
    }

    array->freeArray(array);
}