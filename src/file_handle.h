#ifndef FILE_HANDLE_H
#define FILE_HANDLE_H

#include <stdio.h>
#include "dynamic_array.h"
#include "huffman.h"

void countFileCharacters(DynamicArray *array, const char *filePath);
void encode(DynamicArray *huffmanArray, const char *inputFilePath, const char *outputFilePath);
void decode(const char *inputFilePath);

#endif