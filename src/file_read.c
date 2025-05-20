#include "file_read.h"

void countFileCharacters(DynamicArray *array, const char *filePath) {
    FILE *inputFile = fopen("test.txt", "r+");
    TEST(inputFile, NULL, "fopen");

    LetterNode *letter = NULL;
    char fileCharacter;

    while ((fileCharacter = fgetc(inputFile)) != EOF) {
        if (array->size == 0) {
            LetterNode *letter = (LetterNode *)malloc(sizeof(LetterNode));
            TEST(letter, NULL, "malloc");
            initLetterNode(letter, fileCharacter);
            
            array->push(array, letter);
        } else {
            int found = 0;
            for (int i = 0; i < array->size; i++) {
                if (((LetterNode *)array->nodeAddressArray[i])->character == fileCharacter) {
                    ((LetterNode *)array->nodeAddressArray[i])->quantityOfCharacters++;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                letter = (LetterNode *)malloc(sizeof(LetterNode));
                TEST(letter, NULL, "malloc");
                initLetterNode(letter, fileCharacter);
                array->push(array, letter);
            }
        }
    }
    
    fclose(inputFile);
}