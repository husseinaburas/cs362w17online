#ifndef _TESTINGHELPERS_H
#define _TESTING_HELPERS_H

#include "dominion.h"

int compareGameState(int player, struct gameState *state1, struct gameState *state2); 
int cardNumbersConstant(int player, struct gameState *state1, struct gameState *state2);
int supplyUnchanged(struct gameState *state1, struct gameState *state2);
int treasureMapSupplyUnchanged(struct gameState *state, struct gameState *state2);
int scoreForRefactor(int player, struct gameState *state);

#endif
