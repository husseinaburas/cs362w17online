/* -----------------------------------------------------------------------
 * Stephanie Creamer - CS 362, Winter 2017
 * Assignment 3
 * cardtest2.c - Testing smithy card function
 * Test 1: Play smithy, 3 cards drawn from deck.
 * Test 2: Play smithy, verify smithy is removed from hand.
 * Test 3: Play smithy, less than 3 cards in deck.
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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

void replaceSmithy(struct gameState *state, int testPlayer, int pos)
{
    state->hand[testPlayer][pos] = smithy;
}

int main() {
    int seed = 1000;
    int numPlayers = 2;
    int testResults[3] = {-1};
    int testPlayer = 0;
    int smithyPos = 0;
    int preHandCount = 0, postHandCount = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    printf ("TESTING smithy card:\n");
#if (NOISY_TEST == 1)
    printf("\nTEST 1: Play smithy, sufficient number of cards are in deck.\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &G); // initialize a new game
    
    //put smithy in hand
    replaceSmithy(&G, testPlayer, smithyPos);
    preHandCount = G.handCount[testPlayer];
    playSmithy(&G, smithyPos);
    
    postHandCount = G.handCount[testPlayer];
    
    //store test result
    testResults[0] = assertfalse(postHandCount, preHandCount);

#if (NOISY_TEST == 1)
    printf("\nTEST 2: Play smithy, verify smithy is removed from hand.\n");
#endif
    
    preHandCount = G.handCount[testPlayer];
    G.deckCount[testPlayer] = 2;
    
    smithyPos = 3;
    replaceSmithy(&G, testPlayer, smithyPos);
    
    playSmithy(&G, smithyPos);
    
    postHandCount = G.handCount[testPlayer];
    
    //store test result
    testResults[1] = assertfalse(G.hand[testPlayer][smithyPos], k[6]);
    
#if (NOISY_TEST == 1)
    printf("\nTEST 3: Play smithy, insufficient number of cards are in deck.\n");
#endif
    
    preHandCount = G.handCount[testPlayer];
    G.deckCount[testPlayer] = 2;
    replaceSmithy(&G, testPlayer, smithyPos);
    
    playSmithy(&G, smithyPos);
    
    postHandCount = G.handCount[testPlayer];
    
    //store test result
    testResults[2] = assertfalse(postHandCount, preHandCount); 

//assess test results
    for (int i = 0; i < 3; i++)
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