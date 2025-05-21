#ifndef FILE_HANDLE_H
#define FILE_HANDLE_H

#include <stdio.h>
#include "dynamic_array.h"

void countFileCharacters(DynamicArray *array, const char *filePath);
void writeToFile(const char *inputFilePath, const char *outputFilePath);

#endif