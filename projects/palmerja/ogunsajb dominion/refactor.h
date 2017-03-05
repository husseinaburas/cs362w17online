#ifndef _REFACTOR_H
#define _REFACTOR_H

#include "dominion.h"

void playAdventurer(struct gameState *state, int currentPlayer, int drawntreasure);
void playSmithy(struct gameState *state, int currentPlayer, int handPos);
void playCouncil_room(struct gameState *state, int currentPlayer, int handPos);
void playVillage(struct gameState *state, int currentPlayer, int handPos);
void playGreat_hall(struct gameState *state, int currentPlayer, int handPos);

#endif