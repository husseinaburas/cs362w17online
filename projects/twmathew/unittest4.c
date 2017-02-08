
/*Thomas Mathew
CS 362
Assignment 3
*/


/*
int isGameOver(struct gameState *state) {
	int i;
	int j;

	//if stack of Province cards is empty, the game ends
	if (state->supplyCount[province] == 0)
	{
		return 1;
	}

	//if three supply pile are at 0, the game ends
	j = 0;
	for (i = 0; i < 25; i++)
	{
		if (state->supplyCount[i] == 0)
		{
			j++;
		}
	}
	if (j >= 3)
	{
		return 1;
	}

	return 0;
}
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//newGame() always starts with player 0.

int test4() {



	int playerCount = 2;
	int newSeed = 500;
	int i = 0;
	int r;
	int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };


	//check if province stack is empty
	struct gameState* testGame = newGame();
	r = initializeGame(playerCount, k, newSeed, testGame);
	testGame->supplyCount[province] = 0;
	int testOne = isGameOver(testGame);
	assert(testOne == 1);

	// check if three supply piles are at 0. Picked 2, 4, and 7 arbitrarily
	struct gameState* testGame2 = newGame();
	r = initializeGame(playerCount, k, newSeed, testGame2);
	testGame2->supplyCount[2] == 0;
	testGame2->supplyCount[4] == 0;
	testGame2->supplyCount[7] == 0;
	int testTwo = isGameOver(testGame2);
	//assert(testTwo == 1);

	//check a game that just started. The game should NOT be over.
	struct gameState* testGame3 = newGame();
	r = initializeGame(playerCount, k, newSeed, testGame3);
	int testThree = isGameOver(testGame3);
	assert(testThree == 0);

	//It should be player "zero's" turn, since the game just started. Let's check.
	int resultWhose = whoseTurn(testGame);
	assert(i == resultWhose);

	return 0;
}