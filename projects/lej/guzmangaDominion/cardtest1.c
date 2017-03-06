#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "time.h"
#include "interface.h"

int testSmithyCard(){

  // initialize variables and gamestate
    struct gameState state;
    int players = 2;
    int test = -1;  // test set to -1 if testing fails to complete
    //int seed = 0;

    //seed = rand();

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};

    // test to see if game runs
    test = initializeGame(players, k, 3, &state);

    assert (test == 0);

    // testing smithyCard function
    //===========================================================
    test = -1; // reset test to -1

    int i;
    int handPos = 0;
    int found1, found2, found3, found4 = 0;

    // create 3 cards for smithy to draw
    // adventurer, council_room, and feast
    for(i=0; i<3; i++){
        state.deck[0][i] = k[i];
    }

    state.deckCount[0] = 3;


    // card that I currently have in hand
    state.hand[0][0] = smithy;
    state.handCount[0] = 1;


    //test = cardEffect(smithy, -1, -1, -1, &state, handPos, NULL);


    int currentPlayer = 0;

    test = smithyRefactor(&state, currentPlayer, handPos);
   
    // test that smithy card works
    if(test != 0){
        printf("\nsmithyCard failed\n");
            return 1;
    } else {
        printf("\nsmithyCard passed\n");
    }

    // test that the current hand count should be 3
    if(state.handCount[0] != 3){
        printf("\nhand count '3' failed\n");
            return 1;
    }else{
        printf("\nhand count '3' passed\n");
    }


    // test that the cards in hand should be adventurer, council_room, and feast

    for (i = 0; i <3; i++){

        if(state.hand[0][i] == adventurer){
            found1 = 1;
        }

        if(state.hand[0][i] == council_room){
            found2 = 1;
        }

        if(state.hand[0][i] == feast){
            found3 = 1;
        }

        if(state.hand[0][i] == gardens){
            found4 = 1;
        }
    }

    if (found1 != 1){
        printf("\nadventurer in hand failed\n");
            return 1;
    } else {
        printf("\nadventurer in hand passed\n");
    }

    if (found2 != 1){
        printf("\ncouncil_room in hand failed\n");
            return 1;
    } else {
        printf("\ncouncil_room in hand passed\n");
    }

    if (found3 != 1){
        printf("\nfeast in hand failed\n");
            return 1;
    } else {
        printf("\nfeast in hand passed\n");
    }


    // added a test to make sure that there's no other cards in hand
     if (found4 == 1){
        printf("\ngardens not in hand failed\n");
            return 1;
    } else {
        printf("\ngardens not in hand passed\n");
    }

    // test that there's no card left in the deck after running smithy's effect
    if(state.deckCount[0] != 0){
        printf("\ndeckCount '0' failed\n");
            return 1;
    } else {
        printf("\ndeckCount '0' passed\n");
    }


    printf ("\ntestSmithyCard COMPLETED.\n");
   
    return 0;
}


int main (){

	printf ("\nSTARTING cardtest1 TEST.\n");

	testSmithyCard();

	printf ("\nFINISHED cardtest1 TEST.\n\n");

	return 0;
}