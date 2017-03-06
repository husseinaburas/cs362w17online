#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "time.h"
#include "interface.h"

int testWhoseTurn(){

  // initialize variables and gamestate
	struct gameState state;
	int players = 2;
	int test = -1;	// test set to -1 if testing fails to complete
	int seed = 0;
	

	seed = rand();

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	            remodel, smithy, village, baron, great_hall};

	// test to see if game runs
	test = initializeGame(players, k, seed, &state);

	assert (test == 0);

    // testing whoseTurn function
    //===========================================================
	test = -1;	//reset test to -1

	test = whoseTurn(&state);

	// player 0's turn
	if(test != 0){
		printf("\nwhoseTurn player 0 failed\n");
			return 1;
	} else {
		printf("\nwhoseTurn player 0 passed\n");
	}

	endTurn(&state);

	test = whoseTurn(&state);

	// player 1's turn
	if(test != 1){
		printf("\nwhoseTurn player 1 failed\n");
			return 1;
	} else {
		printf("\nwhoseTurn player 1 passed\n");
	}

	printf ("\ntestWhoseTurn COMPLETED.\n");

	return 0;
}

int main (){

	printf ("\nSTARTING unittest2 TEST.\n");

	testWhoseTurn();

	printf ("\nFINISHED unittest2 TEST.\n\n");

	return 0;
}