

/*Thomas Mathew
CS 362
Assignment 3
*/

/*
int handCard(int handPos, struct gameState *state) 
{
int currentPlayer = whoseTurn(state);
return state->hand[currentPlayer][handPos];
}
*/



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//handCard returns the card in the current players hand
//hand is a two-dimensonal array of ints
//int hand[MAX_PLAYERS][MAX_HAND];

int test1() {

	int playerCount = 2;
	int newSeed = 500;
	int i = 0;
	int r;
	int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	
	//Initialize
	struct gameState* testGame = newGame();
	r = initializeGame(playerCount, k, newSeed, testGame);

	//It should be player "zero's" turn, since the game just started. Let's give them a few cards
	//Then check to see if the function is working

	testGame->hand[0][0] = 1;
	testGame->hand[0][1] = 5;

	int tester = handCard(0, testGame);
	assert(tester == 1);

	int tester2 = handCard(1, testGame);
	assert(tester2 == 5);


	return 0;
}