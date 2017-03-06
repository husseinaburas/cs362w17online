/*  James Le
 *  CS 362
 *  Assignment 4
 *  Ali Aburas
 *  To compile and output to file: 
 *  make randomtestcard1.out
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
Mine Card Effect: You may trash a Treasure from
your hand. Gain a Treasure to your hand costing
up to 3 more than it.
*/

int randomMine(){

  // initialize variables and gamestate

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};

    struct gameState state;
    int players = 2;
    int testErrors = 0;  
    int player = 0;
    int handCount = 0;
    int maxTest = 150;

    int seed;
    int rseed;
    int totalCount;
    int treasureCountBefore;
    int treasureCountAfter;
    int i, r;

    rseed = time(NULL);
    srand(rseed);


    while(maxTest){

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

        // place mine card in the player's hand
        state.hand[player][0] = mine;



        int upgradeCard;
        int treasureFound;
        int notFound = 1;


        for(i=0; i < state.handCount[player]; i++){

            if(state.hand[player][i] == copper){

                treasureFound = state.hand[player][i];

                notFound = 0;
                 break;
            }

            else if(state.hand[player][i] == silver){

                treasureFound = state.hand[player][i];

                notFound = 0;
                break;
            }

            else if(state.hand[player][i] == gold){

                treasureFound = state.hand[player][i];

                notFound = 0;
                break;
            }

        }


        if(notFound == 1){
            printf("no treasure cards in hand\n");
        }
        else{
            printf("treasure card found\n");
        }


        // card upgrades to any cards in the deck
        upgradeCard = rand() % treasure_map;


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

     

        // activate mine card's effect
        r = cardEffect(mine, treasureFound, upgradeCard, -1, &state, 0, 0);



        myAssert(r == 0, "Mine Card Effect");
        if(r!=0){
            testErrors++;
        }



        for(i=0; i < state.handCount[player]; i++){
 
            if(state.hand[player][i] == copper ||
               state.hand[player][i] == silver ||
               state.hand[player][i] == gold) {

                treasureCountAfter++;
            }
        }


        r = myAssert((handCount - 1) == state.handCount[player], "handCount");

        if(r!=0){
            testErrors++;
        }


        r = myAssert(treasureCountBefore == treasureCountAfter, "Treasures");

        if(r!=0){
            testErrors++;
        }


        totalCount = state.deckCount[player] + state.discardCount[player] + state.handCount[player];

        printf("\nAfter Card Effect\n");
        printf("Hand Count: %d\n", state.handCount[player]);
        printf("Deck Count: %d\n", state.deckCount[player]);
        printf("Discard Count: %d\n", state.discardCount[player]);
        printf("Total Count: %d\n", totalCount);
        printf("Treasure Count After: %d\n", treasureCountAfter);

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

    printf ("\nSTARTING RANDOM CARD TEST MINE.\n");

    randomMine();

    printf ("\nFINISHED RANDOM CARD TEST MINE.\n\n");

    return 0;
}