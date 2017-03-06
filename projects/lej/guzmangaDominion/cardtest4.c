#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "time.h"
#include "interface.h"

int testVillageCard(){

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

	// testing villageCard function
	//===========================================================
	test = -1; // reset test to -1

    int i;
    int handPos = 0;
    int numActions;

    numActions = state.numActions;
    
    state.deck[0][0] = baron;
    state.deckCount[0] = 1;

    // card that I currently have in hand
    state.hand[0][0] = village;
    state.handCount[0] = 1;

    test = cardEffect(village, -1, -1, -1, &state, handPos, NULL);

    // assert that village card works
    if(test != 0){
        printf("\nvillageCard failed\n");
            return 1;
    } else {
        printf("\nvillageCard passed\n");
    }

    // assert that the current hand count should be 1
    if(state.handCount[0] != 1){
    	printf("\nhand count '1' failed\n");
            return 1;
    } else {
        printf("\nhand count '1' passed\n");
    }

    // assert that the cards in hand should be baron
    if(state.hand[0][0] != baron){
        printf("\nbaron in hand failed\n");
            return 1;
    } else {
        printf("\nbaron in hand passed\n");
    }

    // assert that the number of actions should be +2 more
    if(state.numActions != (numActions + 2)){
        printf("\nnumActions failed\n");
            return 1;
    } else {
        printf("\nnumActions passed\n");
    }
    
	printf ("\ntestVillageCard COMPLETED.\n");
	
    return 0;
}


int main (){

	printf ("\nSTARTING cardtest4 TEST.\n");

	testVillageCard();

	printf ("\nFINISHED cardtest4 TEST.\n\n");

	return 0;
}