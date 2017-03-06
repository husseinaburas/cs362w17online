#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "time.h"
#include "interface.h"

#define MAX_HAND 500

int testAdventurerCard(){

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

	// testing adventurerCard function
	//===========================================================
	test = -1; // reset test to -1

    int i;
    int handPos = 0;
    
    // feast -> great_hall
    for(i=2; i<8; i++){
        state.deck[0][i] = k[i];
    }

    // add 2 treasure cards for adventurer to draw
    state.deck[0][0] = copper;
    state.deck[0][1] = silver;

    // currently 7 cards in deck
    state.deckCount[0] = 9;


    // card that I currently have in hand
    state.hand[0][0] = adventurer;
    state.handCount[0] = 1;

    int cardDrawn;
    int z = 0;
    int drawntreasure = 0;
    int temphand[500];
    int currentPlayer = 0;


    test = adventurerRefactor(&cardDrawn, &drawntreasure, &state, &temphand, &z, &currentPlayer);
    //test = cardEffect(adventurer, -1, -1, -1, &state, handPos, NULL);

    // test that adventurer card works
    if(test != 0){
    	printf("\nadventurerCard failed\n");
            return 1;
    } else {
        printf("\nadventurerCard passed\n");
    }

    // test that the current hand count should be 3
    if(state.handCount[0] != 3){
    	printf("\nhandCount '3' failed\n");
            return 1;
    } else {
        printf("\nhandCount '3' passed\n");
    }


    for(i=0; i < state.handCount[0]; i++){

        if(state.hand[0][i] == copper) {
            printf("\ncopper found at position %d", i);
        }
    }

    for(i=0; i < state.handCount[0]; i++){

        if(state.hand[0][i] == silver) {
            printf("\nsilver found at position %d", i);
        }
    }

	printf ("\ntestAdventurerCard COMPLETED.\n");
	
    return 0;
}


int main (){

	printf ("\nSTARTING cardtest2 TEST.\n");

	testAdventurerCard();

	printf ("\nFINISHED cardtest2 TEST.\n\n");

	return 0;
}