#ifndef INTERFACES_H
#define INTERFACES_H

#include <stdint.h>
#include <stdio.h>

#define MAX_WORD_SIZE 16
#define WORD_FILE "words.txt"
#define MAX_GUESSES 6

typedef enum {
    SUCCESS = 0,
    FAILURE = 1,
} Status;

Status parseInputBuffer(char *returnBuffer, uint8_t returnBufferLength, uint8_t *returnStringSize);

Status getRandomWord(char *returnBuffer, uint8_t *returnStringSize);

Status printGuesses(uint32_t guesses);
void printImage(uint8_t numGuesses);
void printWord(char *word, uint8_t length, uint32_t mask);

#define clearScreen()  printf("\x1b[2J\x1b[H")


extern const char *asciiArt[];
extern uint8_t guessesToRows[MAX_GUESSES+1];
#endif