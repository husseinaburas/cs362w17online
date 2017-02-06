#include "dominion.c"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "rngs.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define UNIT_ASSERT(conditional, message) \
	if(!conditional) {printf("%s FAIL\n", message);} \
	else {printf("%s PASS\n", message);}

int main(int argv, char** argc){
	struct gameState* testState = newGame();
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randomSeed = 1000;
	int players = 3;

	initializeGame(players, kingdomCards, randomSeed, testState);
	int currentPlayer = whoseTurn(testState);

	printf("======= TESTING whoseTurn() =======\n");
	UNIT_ASSERT((currentPlayer == testState->whoseTurn), "TEST CASE:\tReturn correct player's turn\t\tRESULT:");

	currentPlayer = 1;
	UNIT_ASSERT((currentPlayer != whoseTurn(testState)), "TEST CASE:\twhoseTurn() unchanged 2nd call\t\tRESULT:");

	currentPlayer = whoseTurn(testState);
	endTurn(testState);
	UNIT_ASSERT((currentPlayer != whoseTurn(testState)), "TEST CASE:\tPlayer turn changed after endTurn()\tRESULT:");

	return 0;
}
