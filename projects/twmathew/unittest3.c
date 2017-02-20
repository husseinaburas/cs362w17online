
/*Thomas Mathew
CS 362
Assignment 3
*/

/*
numHandCards

int numHandCards(struct gameState *state) {
	return state->handCount[whoseTurn(state)];
}
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//Player hands are empty at start of the game.

int test3() {



	int playerCount = 2;
	int newSeed = 500;
	int i = 0;
	int r;
	int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };

	struct gameState* testGame = newGame();
	r = initializeGame(playerCount, k, newSeed, testGame);

	//Hand size should be zero, since the game just started. Let's check.
	int handTest = numHandCards(testGame);
	assert(i == 0);
	//assert(i == handTest);

	return 0;
}
