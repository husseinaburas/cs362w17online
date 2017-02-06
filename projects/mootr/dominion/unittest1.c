/**
 * Title:	Unit test for whoseTurn() function
 * Author: Richard Moot
 * Description:	Tests proper functionality of whoseTurn function. Runs through
 * 	several scenarios to ensure that it is returning the correct values from
 * 	the state of the game.
 */
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

	// Testing that the whoseTurn is returning the correct number from testState
	printf("==============\tSTART\tTESTING\twhoseTurn()\t==============\n");
	UNIT_ASSERT((currentPlayer == testState->whoseTurn), "TEST CASE:\tReturn correct player's turn\t\tRESULT:");

	// Manually adjusting testState->whoseTurn to ensure correct value is being returned
	currentPlayer = 1;
	UNIT_ASSERT((currentPlayer != whoseTurn(testState)), "TEST CASE:\twhoseTurn() unchanged 2nd call\t\tRESULT:");

	// Checking the after the endTurn function is run, that whoseTurn is not returning the previous player
	currentPlayer = whoseTurn(testState);
	endTurn(testState);
	UNIT_ASSERT((currentPlayer != whoseTurn(testState)), "TEST CASE:\tPlayer turn changed after endTurn()\tRESULT:");

	printf("==============\tEND\tTESTING\twhoseTurn()\t==============\n");

	return 0;
}
