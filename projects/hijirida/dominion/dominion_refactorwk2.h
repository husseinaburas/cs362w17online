#ifndef _DOMINION_REFACTORWK2_H
#define _DOMINION_REFACTORWK2_H

#include "dominion.h"

int SmithyAction (int currentPlayer, struct gameState *state, int handPos);
int AdventurerAction (int currentPlayer, struct gameState *state, int handPos);
int VillageAction (int currentPlayer, struct gameState *state, int handPos);
int CouncilRoomAction (int currentPlayer, struct gameState *state, int handPos);
int CutPurseAction (int currentPlayer, struct gameState *state, int handPos);

#endif
