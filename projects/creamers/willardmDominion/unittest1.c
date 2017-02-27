/* -----------------------------------------------------------------------
 * Stephanie Creamer - CS 362, Winter 2017
 * Assignment 3
 * unittest1.c - Testing getWinners function
 * Test 1: Happy path test - one person has the highest score, the rest have different values
 * Test 2: Tied scores with players
 * Test 3: Players all have negative scores
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
    int numPlayers = 3;
    int testResults[3] = {-1};
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    //int k[6] = {curse, estate, duchy, province, great_hall, gardens};
    struct gameState G;
    int* players = malloc(numPlayers * sizeof(int));
    for (int i = 0; i < numPlayers; i++)
    {
        players[i] = i;
    }
    
    printf ("TESTING getWinners():\n");
#if (NOISY_TEST == 1)
        printf("\nTEST 1: Testing normal winning configuration: Player 0 has highest score.\n");
#endif
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayers, k, seed, &G); // initialize a new game
    for (int i = 0; i < numPlayers; i++)
    {
        G.handCount[i] = 5;
    }
    //setting up test 1 - player 0 will win
    for (int j = 0; j < MAX_HAND; j++)
    {
        G.hand[0][j] = province;
        G.hand[1][j] = estate;
        G.hand[2][j] = k[0];
    }
    getWinners(players, &G);
#if (NOISY_TEST == 1)
    printf("Player %i has won!\n", players[1]); 
#endif
    testResults[0] = asserttrue(players[1], 0);

#if (NOISY_TEST == 1)
        printf("\nTEST 2: Testing ties: Players 1 and 2 have the highest score.\n");
#endif
    //setting up test 1 - player 1 will win
    for (int j = 0; j < MAX_HAND; j++)
    {
        G.hand[0][j] = k[0];
        G.hand[1][j] = estate;
        G.hand[2][j] = estate;
    }
    
    getWinners(players, &G);
#if (NOISY_TEST == 1)
    printf("Player %i has won!\n", players[1]); 
#endif
    testResults[1] = asserttrue(players[1], 1);
    
#if (NOISY_TEST == 1)
        printf("\nTEST 3: Players have negative scores: Player 1 has highest score.\n");
#endif
    //setting up test 1 - player 1 will win
    for (int j = 0; j < MAX_HAND; j++)
    {
        G.hand[0][j] = curse;
        G.hand[1][j] = province;
        G.hand[2][j] = curse;
    }
    
    getWinners(players, &G);
#if (NOISY_TEST == 1)
    printf("Player %i has won!\n\n", players[1]); 
#endif
    testResults[2] = asserttrue(players[1], 1);

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
    free(players);
    return 0;
}