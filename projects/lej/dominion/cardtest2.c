#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "time.h"
#include "interface.h"

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
    
    // create 5 cards in deck
    // council_room, feast, gardens, mine, and remodel
    for(i=0; i<5; i++){
        state.deck[0][i] = k[i+1];
    }

    // add 2 treasure cards for adventurer to draw
    state.deck[0][5] = copper;
    state.deck[0][6] = silver;

    // currently 7 cards in deck
    state.deckCount[0] = 7;


    // card that I currently have in hand
    state.hand[0][0] = adventurer;
    state.handCount[0] = 1;


    test = cardEffect(adventurer, -1, -1, -1, &state, handPos, NULL);

    // test that adventurer card works
    if(test != 0){
    	printf("\nadventurerCard failed\n");
            return 1;
    } else {
        printf("\nadventurerCard passed\n");
    }

    // test that the current hand count should be 2
    if(state.handCount[0] != 2){
    	printf("\nhandCount '2' failed\n");
            return 1;
    } else {
        printf("\nhandCount '2' passed\n");
    }

    // test that the cards in hand should be copper and silver
    if(state.hand[0][0] != copper || state.hand[0][1] != copper){
    	printf("\ncopper in hand failed\n");
            return 1;
    } else {
        printf("\ncopper in hand passed\n");
    }
    
    if(state.hand[0][0] != silver || state.hand[0][1] != silver){
    	printf("\nsilver in hand failed\n");
            return 1;
    } else {
        printf("\nsilver in hand passed\n");
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