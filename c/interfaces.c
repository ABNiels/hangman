#include "interfaces.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define _isLowerAlpha(c) (c >= 'a' && c <= 'z')
#define _isUpperAlpha(c) (c >= 'A' && c <= 'Z')
#define _toLowerAlpha(c) (c + 0x20)


const char *asciiArt[] = {
    "   .-\"`'\"-.",
    "  /        \\",
    "  |        |",
    "  /'---'--`\\",
    " |          |",
    " \\.--.---.-./",
    " (_.--._.-._)",
    "   \\=-=-=-/",
    "    \\=-=-/",
    "     \\=-/",
    "      \\/"
};

uint8_t guessesToRows[MAX_GUESSES+1] = {11,10,8,6,4,2,0};


Status parseInputBuffer(char *returnBuffer, uint8_t returnBufferLength, uint8_t *returnStringLength) {
    Status status = SUCCESS;
    char currentChar = '_';
    uint8_t localLength = 0;

    while((currentChar = getchar()) != '\n' && localLength < returnBufferLength - 1) { // Leave room for \0
        if (_isLowerAlpha(currentChar)) {
            returnBuffer[localLength++] = currentChar;
        }
        else if (_isUpperAlpha(currentChar)) {
            returnBuffer[localLength++] = _toLowerAlpha(currentChar);
        }
        else {
            localLength = 0;
            status = FAILURE;
            break;
        }
    }

    *returnStringLength = localLength;

    // Zero out remaining buffer
    for(; localLength < *returnStringLength; localLength++) {
        returnBuffer[localLength] = '\0';
    }
    // Burn stdin
    if(currentChar != '\n') {
        while(getchar() != '\n');
    }
    return status;
}


Status getRandomWord(char *returnBuffer, uint8_t *returnStringSize) {

    FILE *fp = fopen(WORD_FILE, "r");
    char word[MAX_WORD_SIZE];
    uint32_t lineNumber = 0;
    Status status = SUCCESS;

    srand(time(NULL));

    // Reservoir sampling
    while(fgets(word, MAX_WORD_SIZE, fp) != NULL) {
        lineNumber++;
        if(rand() % lineNumber == 0) {
            memset(returnBuffer, 0, MAX_WORD_SIZE);
            strcpy(returnBuffer, word);
        }
    }

    fclose(fp);

    char *tmp;

    // Strip new lines
    if((tmp=strchr(returnBuffer, '\n')) != NULL) { *tmp = '\0'; }
    if((tmp=strchr(returnBuffer, '\r')) != NULL) { *tmp = '\0'; }

    // Lazy way with some assumptions - use at your own risk
    //*((uint16_t *)strchr(returnBuffer, '\r')) = 0;

    if(returnBuffer[0] == '\0') { 
        status = FAILURE;
        *returnStringSize = 0;    
    }
    else {
        *returnStringSize = strlen(returnBuffer);
    }

    return status;
}

Status printGuesses(uint32_t guesses) {
    char letter;
    printf("Previous guesses: ");
    while(guesses) {
        letter = __builtin_ctz(guesses);
        guesses ^= (uint32_t)(1 << letter);
        printf("%c ", letter + 'a');
    }
    printf("\n");
    return SUCCESS;
}

void printImage(uint8_t numGuesses) {
    // Print the ascii art disappearing with each incorrect guess
    uint8_t i, linesToSkip = guessesToRows[0] - guessesToRows[numGuesses];
    printf("\n");
    for(i=0; i<linesToSkip; i++) {
        printf("\n");
    }
    for(i=0; i<guessesToRows[numGuesses]; i++) {
        printf("%s\n", asciiArt[i+linesToSkip]);
    }
}


void printWord(char *word, uint8_t length, uint32_t mask) {
    uint8_t i;
    printf("\n");
    for(i = 0; i<length; i++) {
        if((1 << (word[i]-'a')) & mask) {
            printf("%c ", word[i]);
        }
        else { printf("_ "); }
    }
    printf("\n");
}