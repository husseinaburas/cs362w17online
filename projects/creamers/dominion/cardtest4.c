/* -----------------------------------------------------------------------
 * Stephanie Creamer - CS 362, Winter 2017
 * Assignment 3
 * cardtest3.c - Testing great_hall card function
 * Test 1: Play village, 1 card drawn from deck.
 * Test 2: Play village, verify action is the same before and after playing card.
 * Test 3: Play village, 0 cards in deck.
 * Test 4: Play village, verify action is the same before and after playing card.
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 *
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "devassert.h"
#include <stdlib.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    int numPlayers = 2;
    int testResults[4] = {-1};
    int testPlayer = 0;
    int preActionCount = 0, postActionCount = 0, preHandCount = 0, postHandCount = 0;
    
    struct gameState G;
#if (NOISY_TEST == 1)
        printf("\nTEST 1: Testing normal path of instructions; deck has sufficient cards.\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &G); // initialize a new game
         
    preHandCount = G.handCount[testPlayer];
    preActionCount = G.numActions;
    playVillage(&G, 0);
    postHandCount = G.handCount[testPlayer];
    postActionCount = G.numActions;
    
    //store test result -- count should be the same because drew one card and discarded village
    testResults[0] = asserttrue(preHandCount, postHandCount);

#if (NOISY_TEST == 1)
    printf("\nTEST 2: Play village, verify correct number of actions are returned.\n");
#endif
    
    //store test result -- number of actions should be the same; action gained replaces the action used to play the card
    testResults[1] = asserttrue(preActionCount+2, postActionCount);
    
#if (NOISY_TEST == 1)
    printf("\nTEST 3: Play village, insufficient number of cards are in deck.\n");
#endif
    //reset game
    memset(&G, 23, sizeof(struct gameState)); 
    initializeGame(numPlayers, k, seed, &G);
    G.hand[testPlayer][0] = village;
    
    preHandCount = G.handCount[testPlayer];
    preActionCount = G.numActions;
    G.deckCount[testPlayer] = 0;   
    playVillage(&G, 0);
    postActionCount = G.numActions;
    postHandCount = G.handCount[testPlayer];
    
    //store test result   
    testResults[2] = asserttrue(postHandCount, preHandCount); 
    
#if (NOISY_TEST == 1)
    printf("\nTEST 4: Play village with insufficient cards, verify correct number of actions is returned.\n");
#endif
    
    //store test result -- number of actions should be the same; action gained replaces the action used to play the card
    testResults[3] = asserttrue(preActionCount+2, postActionCount);

//assess test results
    for (int i = 0; i < 4; i++)
    {
        printf("Test %i has ", i+1);
        if (testResults[i] == 0)
        {
            printf("FAILED.\n");
        }
        else if (testResults[i] == 1)
        {
            printf("PASSED.\n");
        }
        else
        {
            printf("GONE HORRIBLY WRONG.\n");
        }
    }
    
    printf("All tests have completed!\n");
    return 0;
}