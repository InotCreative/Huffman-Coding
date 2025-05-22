#include <stdio.h>
#include "dynamic_array.h"
#include "file_handle.h"
#include "huffman.h"

int main(int argc, char const *argv[]) {
    DynamicArray huffmanCodeArray = initHuffmanCode("test.txt");
    DynamicArray huffmanTree = buildHuffmanTree("test.txt");

    generateHuffmanCodes(&huffmanCodeArray, &huffmanTree);

    for (int i = 0; i < huffmanCodeArray.size; i++) {
        HuffmanCode *code = (HuffmanCode *)huffmanCodeArray.nodeAddressArray[i];
        
        printf("CHARACTER: %c | CODE: %s", code->letter, code->code);
    }

    huffmanTreeCleanup(&huffmanTree);
    huffmanArrayCleanup(&huffmanCodeArray);
    return 0;
}