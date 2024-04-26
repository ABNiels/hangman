#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include "interfaces.h"

#define GAME_WON 1
#define GAME_LOST 2
#define INVALID_INPUT 4

typedef struct {
    char *word; // Word to guess
    uint8_t wordLength; // Length of word
    uint32_t guesses; // bitmap of guesses
    uint32_t letters; // bitmap of word letters
    uint8_t status; // various status messages for printing and win condition
} GameState;

Status initPhase(GameState *gamestate);
Status guessPhase();
Status displayPhase();
Status run();


#endif