/*  James Le
 *  CS 362
 *  Assignment 4
 *  Ali Aburas
 *  To compile and output to file: 
 *  make randomtestadventurer.out
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
Adventurer Card Effect: Reveal cards from your deck
until you reveal 2 Treasure cards. Put those Treasure
cards into your hand and discard the other revealed cards.
*/

int randomAdventurer(){

  // initialize variables and gamestate

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};

    struct gameState state;
    int players = 2;
    int testErrors = 0;  
    int player = 0;
    int handCount = 0;
    int maxTest = 150;
    int counter = 0;


    int errorsHere;
    int seed;
    int rseed;
    int totalCount;
    int treasureCountBefore;
    int treasureCountAfter;
    int i, r;

    int storeError[2000];

    rseed = time(NULL);
    srand(rseed);


    while(maxTest){

        errorsHere = 0;
        printf("\n================================================================");
        printf("\nTest Remaining: %d\n", maxTest);
        printf("================================================================\n");
        treasureCountAfter = 0;
        treasureCountBefore = 0;

        players = rand() % 3 + 2;
        seed = rand();

        r = initializeGame(players, k, seed, &state);
        myAssert(r == 0, "Initializing game");

        // generate random deck, discard, and hand count
        state.deckCount[player] = rand() % MAX_DECK;
        state.discardCount[player] = rand() % MAX_DECK;
        state.handCount[player] = rand() % MAX_HAND;

        // place adventurer card in the player's hand
        state.hand[player][0] = adventurer;

        // count the amount of treasure cards in the player's hand
        for(i=0; i < state.handCount[player]; i++){

            if(state.hand[player][i] == copper ||
               state.hand[player][i] == silver ||
               state.hand[player][i] == gold) {

                treasureCountBefore++;
            }
        }


        totalCount = state.deckCount[player] + state.discardCount[player] + state.handCount[player];

        printf("\nBefore Card Effect\n");
        printf("Hand Count: %d\n", state.handCount[player]);
        printf("Deck Count: %d\n", state.deckCount[player]);
        printf("Discard Count: %d\n", state.discardCount[player]);
        printf("Total Count: %d\n", totalCount);
        printf("Treasure Count Before: %d\n\n", treasureCountBefore);


        handCount = state.handCount[player];



        r = cardEffect(adventurer, -1, -1, -1, &state, 0, 0);

       

        myAssert(r == 0, "Adventurer Card Effect");

        if(r!=0){
            testErrors++;
            errorsHere = 1;
        }


        for(i=0; i < state.handCount[player]; i++){
 
            if(state.hand[player][i] == copper ||
               state.hand[player][i] == silver ||
               state.hand[player][i] == gold) {

                treasureCountAfter++;
            }
        }

        
        r = myAssert((handCount + 2) == state.handCount[player], "handCount");

        if(r!=0){
            testErrors++;
            errorsHere = 1;
        }


        r = myAssert((treasureCountBefore + 2) == treasureCountAfter ||
                     (treasureCountBefore + 1) == treasureCountAfter, "Treasures");

        if(r!=0){
            testErrors++;
            errorsHere = 1;
        }


        totalCount = state.deckCount[player] + state.discardCount[player] + state.handCount[player];

        printf("\nAfter Card Effect\n");
        printf("Hand Count: %d\n", state.handCount[player]);
        printf("Deck Count: %d\n", state.deckCount[player]);
        printf("Discard Count: %d\n", state.discardCount[player]);
        printf("Total Count: %d\n", totalCount);
        printf("Treasure Count After: %d\n", treasureCountAfter);


        if(errorsHere == 1){
            storeError[counter] = maxTest;
            counter++;
        }

        maxTest--;
    }


    if(testErrors > 0){
        printf("\nThere were %d errors total.\n", testErrors);
        printf("\nErrors found in test # \n");

        for(i=0; i<counter; i++){
            printf("%d\n", storeError[i]);
        }
    } 

    else{
        printf("\nTEST SUCCESS\n");
    }


    return 0;
}


int main (){

	printf ("\nSTARTING RANDOM CARD TEST ADVENTURER.\n");

	randomAdventurer();

	printf ("\nFINISHED RANDOM CARD TEST ADVENTURER.\n\n");

	return 0;
}