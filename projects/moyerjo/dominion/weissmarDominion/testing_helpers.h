#ifndef _TESTINGHELPERS_H
#define _TESTING_HELPERS_H

#include "dominion.h"

int compareGameState(int player, struct gameState *state1, struct gameState *state2); 
int cardNumbersConstant(int player, struct gameState *state1, struct gameState *state2);
int supplyUnchanged(struct gameState *state1, struct gameState *state2);
int treasureMapSupplyUnchanged(struct gameState *state, struct gameState *state2);
int scoreForRefactor(int player, struct gameState *state);
void randomSetup(struct gameState *state);
void addCards(int card, int numToAdd, struct gameState *state);
void shuffleCards(int curPlayer, int deckSection, struct gameState * state);
int validateAdventurerDraw(int curPlayer, struct gameState *state1, struct gameState *state2);
int testFlags(struct gameState *state1, struct gameState *state2);

#endif
