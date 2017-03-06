#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "time.h"
#include "interface.h"

int testSupplyCount(){

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

	// testing supplyCount function
	//===========================================================
	test = -1; // reset test to -1

	// manually set the supply of copper to 2
    state.supplyCount[copper] = 2;

    test = supplyCount(copper, &state);

    // assert that the supply count is 2
    if(test != 2){
    	printf("\nsupplyCount '2' failed\n");
    		return 1;
    } else {
    	printf("\nsupplyCount '2' passed\n");
    }

    // gain 2 copper cards
    gainCard(4, &state, 2, 0);
    gainCard(4, &state, 2, 0);

    test = supplyCount(copper, &state);

    // assert that the supply count is 0
    if(test != 0){
    	printf("\nsupplyCount '0' failed\n");
    		return 1;
    } else {
    	printf("\nsupplyCount '0' passed\n");
    }


	printf ("\ntestSupplyCount COMPLETED.\n");
	

    return 0;
}

int main (){

	printf ("\nSTARTING unittest3 TEST.\n");

	testSupplyCount();

	printf ("\nFINISHED unittest3 TEST.\n\n");

	return 0;
}