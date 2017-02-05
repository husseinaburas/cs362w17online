/* -----------------------------------------------------------------------
 * Stephanie Creamer - CS 362, Winter 2017
 * Assignment 3
 * unittest4.c - Testing scoreFor function
 * Test 1: Players have all positive cards
 * Test 2: Players have no points cards
 * Test 3: Players have all negative cards
 * Test 4: Players have a mix of value cards
 *
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o devassert.o rngs.o
 *      gcc -o unittest4 -g unittest4.c dominion.o rngs.o devassert.o $(CFLAGS)

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

#define PROVINCE_VALUE 6
#define ESTATE_VALUE 1
#define DUCHY_VALUE 3
#define CURSE_VALUE -1

int main() {
    int seed = 1000;
    int testResults[3] = {-1};
    int numPlayers = 2;
    int count = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
        
    printf ("TESTING scoreFor():\n");
#if (NOISY_TEST == 1)
        printf("\nTEST 1: Players have positive cards.\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &G); // initialize a new game
    G.handCount[0] = MAX_HAND;
    G.deckCount[0] = MAX_HAND;
    G.discardCount[0] = MAX_HAND;
    for (int j = 0; j < MAX_HAND; j++)
    {
        G.hand[0][j] = province;
        G.deck[0][j] = estate;
        G.discard[0][j] = duchy;
    }
    for (int i = 0; i < numPlayers; i++)
    {
        count = scoreFor(0, &G);
    }
    
    testResults[0] = asserttrue(count, MAX_HAND * (PROVINCE_VALUE + ESTATE_VALUE + DUCHY_VALUE));

#if (NOISY_TEST == 1)
        printf("\nTEST 2: Players have no scoring cards.\n");
#endif
    count = 0;
    for (int j = 0; j < MAX_HAND; j++)
    {
        G.hand[0][j] = smithy;
        G.deck[0][j] = adventurer;
        G.discard[0][j] = baron;
    }
    for (int i = 0; i < numPlayers; i++)
    {
        count = scoreFor(0, &G);
    }
    
    testResults[1] = asserttrue(count, 0);
    
#if (NOISY_TEST == 1)
        printf("\nTEST 3: Players have all negative cards.\n");
#endif
    count = 0;
    for (int j = 0; j < MAX_HAND; j++)
    {
        G.hand[0][j] = curse;
        G.deck[0][j] = curse;
        G.discard[0][j] = curse;
    }
    for (int i = 0; i < numPlayers; i++)
    {
        count = scoreFor(0, &G);
    }
    
    testResults[2] = asserttrue(count, 3 * MAX_HAND * (CURSE_VALUE));
    
#if (NOISY_TEST == 1)
    printf("\nTEST 4: Players have a mix of cards.\n");
#endif    
    count = 0;
    for (int j = 0; j < MAX_HAND; j++)
    {
        G.hand[0][j] = smithy;
        G.deck[0][j] = duchy;
        G.discard[0][j] = curse;
    }
    for (int i = 0; i < numPlayers; i++)
    {
        count = scoreFor(0, &G);
    }
    
    testResults[3] = asserttrue(count, MAX_HAND * (CURSE_VALUE + DUCHY_VALUE));  

    for (int i = 0; i < 4; i++)
    {
        printf("Test %i has ", i+1);
        if (testResults[i] == 0)
        {
            printf("FAILED.\n");
        }
        else
        {
            printf("PASSED.\n");
        }
    }
    
    printf("All tests have completed!\n");

    return 0;
}