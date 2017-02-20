#ifndef TESTHELP_H
#define TESTHELP_H

#include "dominion.h"
#include "dominion_helpers.h"

void assertIsEqual(char *msg, int a, int b); //change to use void pointers
int assertIsValid(char *msg, int player, struct gameState *state);
void testCounts(int player, struct gameState *state, int handCtpre, int deckCtpre, int playedCtpre, int handCt, int deckCt, int playedCt);

#endif
