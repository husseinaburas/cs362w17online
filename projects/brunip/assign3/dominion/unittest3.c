/*
  unit test for whoseTurn() 
  */ 



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>



int main() {
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Unit: whosCard() ----------------\n");

	
	// ----------- TEST 1: Testing Player 0 Turn --------------
	printf("TEST 1: Testing Player 0 Turn\n");
    G.whoseTurn = 0;
	printf("Whose Turn?? = %d, expected = 0\n", whoseTurn(&G));
	assert(whoseTurn(&G) == 0);
	
	// ----------- TEST 2: Testing Player 1 Turn --------------
	printf("TEST 1: Testing Player 1 Turn\n");
	// changing player turn
    G.whoseTurn = 1;
	printf("Whose Turn?? = %d, expected = 1\n", whoseTurn(&G));
	assert(whoseTurn(&G) == 1);
	
	
	printf("\n >>>>> SUCCESS: Testing complete for unittest3 <<<<<\n\n");
	return 0;
}

