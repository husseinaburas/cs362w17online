/* -----------------------------------------------------------------------
 * Stephanie Creamer - CS 362, Winter 2017
 * Assignment 3
 * unittest3.c - Testing isGameOver function
 * Test 1: Province cards and supply cards are full
 * Test 2: Supply cards are depleted, province cards are not
 * Test 3: Province cards are depleted and supply cards are not
 * Test 4: Province and supply cards are depleted
 *
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o devassert.o rngs.o
 *      gcc -o unittest3 -g unittest3.c dominion.o rngs.o devassert.o $(CFLAGS)

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
    int testResults[3] = {-1};
    int count;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
        
    printf ("TESTING fullDeckCount():\n");

    for (int numPlayers = 2; numPlayers <= 4; numPlayers++)
    {
        #if (NOISY_TEST == 1)
        printf("\nTEST %i: Number of players is %i.\n", numPlayers-1, numPlayers);
#endif
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayers, k, seed, &G); // initialize a new game
        count = 0;
    for (int i = 0; i < numPlayers; i++)
    {
        count += fullDeckCount(i, copper, &G);
    }
    testResults[numPlayers-2] = asserttrue(count, 7*numPlayers);
    }
    
    for (int i = 0; i < MAX_PLAYERS; i++)
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