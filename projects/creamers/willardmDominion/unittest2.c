/* -----------------------------------------------------------------------
 * Stephanie Creamer - CS 362, Winter 2017
 * Assignment 3
 * unittest2.c - Testing isGameOver function
 * Test 1: Province cards and supply cards are full
 * Test 2: Supply cards are depleted, province cards are not
 * Test 3: Province cards are depleted and supply cards are not
 * Test 4: Province and supply cards are depleted
 *
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o devassert.o rngs.o
 *      gcc -o unittest2 -g unittest2.c dominion.o rngs.o devassert.o $(CFLAGS)

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
    int testResults[4] = {-1};
    int numPlayers = 3;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
        
    printf ("TESTING isGameOver():\n");
#if (NOISY_TEST == 1)
        printf("\nTEST 1: Province and supply cards are not empty.\n");
#endif
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayers, k, seed, &G); // initialize a new game
    //initialize all supply cards to 5
    for (int i = 0; i < 25; i++)
    {
        G.supplyCount[i] = 5;
    }
    //initialize provinces to 5
    G.supplyCount[province] = 5;
    testResults[0] = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Game is "); 
    if (testResults[0] == 0)
    {
        printf ("not ");
    }
    printf ("over.\n");
#endif
    testResults[0] = asserttrue(testResults[0], 0);

#if (NOISY_TEST == 1)
        printf("\nTEST 2: Supply cards are depleted but Province cards are not.\n");
#endif
    //setting up test 1 - player 1 will win
    for (int i = 0; i < 25; i++)
    {
        G.supplyCount[i] = 0;
    }
    //initialize provinces to 5
    G.supplyCount[province] = 5;
    testResults[1] = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Game is "); 
    if (testResults[1] == 0)
    {
        printf ("not ");
    }
    printf ("over.\n");
#endif
    testResults[1] = asserttrue(testResults[1], 1);
#if (NOISY_TEST == 1)
        printf("\nTEST 3: Supply cards are not empty, province cards are.\n");
#endif
    for (int i = 0; i < 25; i++)
    {
        G.supplyCount[i] = 5;
    }
    //initialize provinces to 0
    G.supplyCount[province] = 0;
    testResults[2] = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Game is "); 
    if (testResults[2] == 0)
    {
        printf ("not ");
    }
    printf ("over.\n");
#endif
    testResults[2] = asserttrue(testResults[2], 1);
    
#if (NOISY_TEST == 1)
        printf("\nTEST 4: Supply cards and province cards are empty.\n");
#endif
    for (int i = 0; i < 25; i++)
    {
        G.supplyCount[i] = 0;
    }
    //initialize provinces to 0
    G.supplyCount[province] = 0;
    testResults[3] = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("Game is "); 
    if (testResults[3] == 0)
    {
        printf ("not ");
    }
    printf ("over.\n");
#endif
    testResults[3] = asserttrue(testResults[3], 1);

    
    
    
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