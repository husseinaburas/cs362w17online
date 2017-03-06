
/*Thomas Mathew
CS 362
Assignment 3
*/


/*
int whoseTurn(struct gameState *state) {
	return state->whoseTurn;
}
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//newGame() always starts with player 0.

int test2() {

	int playerCount = 2;
	int newSeed = 500;
	int i = 0;
	int r;
	int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	
	struct gameState* testGame = newGame();
	r = initializeGame(playerCount, k, newSeed, testGame);

	//It should be player "zero's" turn, since the game just started. Let's check.
	int resultWhose = whoseTurn(testGame);
	assert(i == resultWhose);

	return 0;
}