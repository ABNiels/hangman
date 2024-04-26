
#include "engine.h"
#include "interfaces.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Status run() {
    GameState gamestate;
    if(initPhase(&gamestate) == SUCCESS) {
        while(displayPhase(&gamestate) == SUCCESS && 
              guessPhase(&gamestate) == SUCCESS &&
              (gamestate.status & 3) == 0 // win/lose
        );
        displayPhase(&gamestate);
    }

    free(gamestate.word);

    return SUCCESS;
}

Status initPhase(GameState *gamestate) {
    Status status = SUCCESS;
    char wordBuffer[MAX_WORD_SIZE];

    if(getRandomWord(wordBuffer, &(gamestate->wordLength)) == SUCCESS) {
        // Setup word
        free(gamestate->word);
        gamestate->word = calloc(gamestate->wordLength + 1, sizeof(char));

        // letters contains a bitmap of the letters in the word
        gamestate->letters = 0;
        uint8_t i;
        for(i=0; i < gamestate->wordLength; i++ ) {
            gamestate->word[i] = wordBuffer[i];
            gamestate->letters |= 1 << (wordBuffer[i] - 'a');
        }
        gamestate->word[i] = wordBuffer[i]; // We're keeping the null terminator just in case
    }
    else { status = FAILURE; }
    gamestate->guesses = 0;
    gamestate->status = 0;

    return status;
}

Status displayPhase(GameState *gamestate) {
    clearScreen();
    printGuesses(gamestate->guesses);
    printImage(__builtin_popcount(gamestate->guesses)-__builtin_popcount(gamestate->guesses & gamestate->letters));
    printWord(gamestate->word, gamestate->wordLength, gamestate->guesses);
    switch(gamestate->status){
        case GAME_LOST:
            printf("You lost! The word was '%s'\n", gamestate->word);
            break;
        case GAME_WON:
            printf("Congratulations! You Win!\n");
            break;
        case INVALID_INPUT:
            printf("Hmmm. Rethink that guess...\n");
            break;
        default:
            break;

    }
    return SUCCESS;
}

Status guessPhase(GameState *gamestate) {
    char *inputBuffer = malloc(gamestate->wordLength);
    uint8_t guessSize;
    printf("Guess a letter or word: ");
    if(parseInputBuffer(inputBuffer, gamestate->wordLength+1, &guessSize) == SUCCESS) {
        // Guessed a character
        if(guessSize == 1) {
            gamestate->guesses |= (1 << (inputBuffer[0] - 'a'));
            if(((gamestate->letters & gamestate->guesses) ^ gamestate->letters) == 0) { // All letters in the word have been guessed
                gamestate->status = GAME_WON; 
            }
            else if(__builtin_popcount(gamestate->guesses)-__builtin_popcount(gamestate->guesses & gamestate->letters) >= MAX_GUESSES) { // Ran out of guesses
                gamestate->status = GAME_LOST; 
            }
        }
        // Guessed a word
        else if(guessSize == gamestate->wordLength) {
            if(strcmp(inputBuffer, gamestate->word) == 0) {
                gamestate->status = GAME_WON;
                uint8_t i;
                for(i=0;i<guessSize;i++){
                    gamestate->guesses |= 1 << (gamestate->word[i] - 'a');
                }
            }
            else { // Lose if you guess wrong
                gamestate->status = GAME_LOST;
            }
        }
        // Guessed something stupid
        else {
            gamestate->status = INVALID_INPUT;
        }
    }
    else {
        gamestate->status = INVALID_INPUT;
    }

    return SUCCESS;
}