#include "huffman.h"

BinaryTreeNode *buildHuffmanTree(BinaryTreeNode **tree, DynamicArray *array, const char *filePath) {
    countFileCharacters(array, filePath);
    
    array->quickSort(array, 0, array->size - 1);

    while (array->size > 1) {
        LetterNode *letterOne = array->pop(array, 0);
        LetterNode *letterTwo = array->pop(array, 0);

        BinaryTreeNode *left = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
        TEST(left, NULL, "malloc");
        left->left = NULL;
        left->right = NULL;
        left->node = letterOne;

        BinaryTreeNode *right = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
        TEST(right, NULL, "malloc");
        right->left = NULL;
        right->right = NULL;
        right->node = letterTwo;

        BinaryTreeNode *mergedNode = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
        TEST(mergedNode, NULL, "malloc");

        // Allocate a new LetterNode for the merged node
        mergedNode->node = (LetterNode *)malloc(sizeof(LetterNode));
        TEST(mergedNode->node, NULL, "malloc");

        mergedNode->left = left;
        mergedNode->right = right;
        mergedNode->node->character = -1; // internal node
        mergedNode->node->quantityOfCharacters = letterOne->quantityOfCharacters + letterTwo->quantityOfCharacters;

        // Insert while keeping array sorted by quantityOfCharacters
        bool inserted = false;
        for (int i = 0; i < array->size; i++) {
            LetterNode *current = ((BinaryTreeNode *)array->nodeAddressArray[i])->node;
            if (current->quantityOfCharacters >= mergedNode->node->quantityOfCharacters) {
                array->nodeAddressArray[i] = mergedNode;
                inserted = true;
                break;
            }
        }

        if (!inserted) {
            array->push(array, mergedNode);
        }
    }

    if (array->size == 1) {
        return (BinaryTreeNode *)array->nodeAddressArray[0];
    }

    return NULL; // fallback if something goes wrong
}

void printNode(BinaryTreeNode *root) {
    if (root == NULL) {
        printf("EMPTY NODE\n");
        return;
    }

    if (root->node->character == -1) {
        printf("Root node: Internal node with count = %ld\n", root->node->quantityOfCharacters);
    } else {
        printf("Root node: Leaf node with character = '%c' and count = %ld\n", root->node->character, root->node->quantityOfCharacters);
    }
}

void generateHuffmanCode(BinaryTreeNode **tree, DynamicArray *array) {
    HuffmanCodebook codebook;
    initDynamicArray(codebook.array);
    codebook.node = NULL;


}