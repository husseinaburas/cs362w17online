#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "time.h"
#include "interface.h"

int testMineCard(){

  // initialize variables and gamestate
    struct gameState state;
    int players = 2;
    int test = -1;  // test set to -1 if testing fails to complete
    int seed = 0;

    seed = rand();

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};

    // test to see if game runs
    test = initializeGame(players, k, seed, &state);

    assert (test == 0);

	// testing mineCard function
	//===========================================================
	test = -1; // reset test to -1

    int i;
    int handPos = 0;
    
    // card that I currently have in hand
    state.hand[0][0] = mine;
    state.hand[0][1] = copper;
    state.handCount[0] = 2;

    test = cardEffect(mine, 1, 5, -1, &state, handPos, NULL);

    // assert that mine card works
    if(test != 0){
        printf("\nmineCard failed\n");
            return 1;
    } else {
        printf("\nmineCard passed\n");
    }

    // assert that the current hand count should be 1
    // note: test failed because I bugged mineCard function, gainCard will trash card instead so hand is empty
    if(state.handCount[0] != 1){
    	printf("\nhandCount '1' failed\n");
            return 1;
    } else {
        printf("\nhandCount '1' passed\n");
    }

    // assert that the cards in hand should be silver
    if(state.hand[0][0] != silver){
        printf("\nsilver in hand failed\n");
            return 1;
    } else {
        printf("\nsilver in hand passed\n");
    }
  
	printf ("\ntestMineCard COMPLETED.\n");
	

    return 0;
}


int main (){

	printf ("\nSTARTING cardtest3 TEST.\n");

	testMineCard();

	printf ("\nFINISHED cardtest3 TEST.\n\n");

	return 0;
}