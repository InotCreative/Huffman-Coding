#include <stdio.h>
#include "dynamic_array.h"
#include "file_handle.h"
#include "huffman.h"

void printHuffmanTree(BinaryTreeNode *root, int depth) {
    if (root == NULL) return;

    printHuffmanTree(root->right, depth + 1);

    for (int i = 0; i < depth; i++) {
        printf("    ");
    }

    if (root->node->character == '\0')
        printf("[INT] (%ld)\n", root->node->quantityOfCharacters);  // Internal node
    else
        printf("'%c' (%ld)\n", root->node->character, root->node->quantityOfCharacters);  // Leaf node

    // Print left subtree
    printHuffmanTree(root->left, depth + 1);
}

int main(int argc, char const *argv[]) {
    DynamicArray huffmanArray = buildHuffmanTree("test.txt");
    huffmanArray.printArray(&huffmanArray, 1);

    BinaryTreeNode *root = (BinaryTreeNode *)huffmanArray.nodeAddressArray[0];
    printHuffmanTree(root, 0);

    finalCleanup(&huffmanArray);
    return 0;
}
