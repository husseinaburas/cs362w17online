/*  James Le
 *  CS 362
 *  Assignment 4
 *  Ali Aburas
 *  To compile and output to file: 
 *  make randomtestcard2.out
 */


#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "time.h"
#include "interface.h"
#include <string.h> 
#include <math.h>

int myAssert(int c, char *s){

    if(!c) {
        printf("Assertion failed: %s\n", s);
        if(0) {
                exit(1);
        }
        return 1;
    } 

    else {
        printf("Assertion passed: %s\n", s);
    }
    return 0;
}

/*
Great Hall Card Effect: +1 Card, +1 Action
*/

int randomGreatHall(){

  // initialize variables and gamestate

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};

    struct gameState state;
    int players = 2;
    int testErrors = 0;  
    int player = 0;
    int handCount = 0;
    int maxTest = 50000;

    int seed;
    int rseed;
    int numActions;
    int totalCount;
    int r;

    rseed = time(NULL);
    srand(rseed);


    while(maxTest){

        printf("\n================================================================");
        printf("\nTest Remaining: %d\n", maxTest);
        printf("================================================================\n");

        players = rand() % 3 + 2;
        seed = rand();

        r = initializeGame(players, k, seed, &state);
        myAssert(r == 0, "Initializing game");

        // generate random deck, discard, and hand count
        state.deckCount[player] = rand() % MAX_DECK;
        state.discardCount[player] = rand() % MAX_DECK;
        state.handCount[player] = rand() % MAX_HAND;

        // place great hall card in the player's hand
        state.hand[player][0] = great_hall;


        totalCount = state.deckCount[player] + state.discardCount[player] + state.handCount[player];


        printf("\nBefore Card Effect\n");
        printf("Hand Count: %d\n", state.handCount[player]);
        printf("Deck Count: %d\n", state.deckCount[player]);
        printf("Discard Count: %d\n", state.discardCount[player]);
        printf("Total Count: %d\n\n", totalCount);
        

        handCount = state.handCount[player];
        numActions = state.numActions;

    
        // activate great hall card's effect
        r = cardEffect(great_hall, -1, -1, -1, &state, 0, 0);



        myAssert(r == 0, "Great Hall Card Effect");
        if(r!=0){
            testErrors++;
        }


        r = myAssert(handCount == state.handCount[player], "handCount");
        if(r!=0){
            testErrors++;
        }



        r = myAssert(state.numActions == numActions + 1, "numActions");
        if(r!=0){
            testErrors++;
        }

        totalCount = state.deckCount[player] + state.discardCount[player] + state.handCount[player];

        printf("\nAfter Card Effect\n");
        printf("Hand Count: %d\n", state.handCount[player]);
        printf("Deck Count: %d\n", state.deckCount[player]);
        printf("Discard Count: %d\n", state.discardCount[player]);
        printf("Total Count: %d\n\n", totalCount);
     
        maxTest--;
    }


    if(testErrors > 0){
        printf("There were %d errors.\n", testErrors);
    }

    else{
        printf("\nTEST SUCCESS\n");
    }

    return 0;
}


int main (){

    printf ("\nSTARTING RANDOM CARD TEST GREAT HALL.\n");

    randomGreatHall();

    printf ("\nFINISHED RANDOM CARD TEST GREAT HALL.\n\n");

    return 0;
}