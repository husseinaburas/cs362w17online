/* -----------------------------------------------------------------------
 * Stephanie Creamer - CS 362, Winter 2017
 * Assignment 4
 * randomcardtest1.c - Testing smithy card function
 * Test 1: Play smithy, 3 cards drawn from deck.
 * Test 2: Play smithy, verify smithy is removed from hand.
 * Test 3: Play smithy, less than 3 cards in deck.
 * Include the following lines in your makefile:
 *
 * randomcardtest1: randomcardtest1.c dominion.o rngs.o
 *      gcc -o randomcardtest1 -g  randomcardtest1.c dominion.o rngs.o $(CFLAGS)
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

int main(int argc, char* argv[]) {
    if (argc == 1)
    {
        printf("usage: ./randomcardtest1 <seed>\n");
        return (EXIT_FAILURE);
    }
    int seed = atoi(argv[1]);
    srand(seed);
    int numPlayers;
    int testResults[3] = {-1};
    int testPlayer;

    int preHandCount = 0, postHandCount = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    do {
        numPlayers = rand() % 4;
    }
    while (numPlayers < 2);
    testPlayer = rand() % numPlayers;
    printf ("TESTING smithy card:\n");
#if (NOISY_TEST == 1)
    printf("\nTEST 1: Play smithy, sufficient number of cards are in deck.\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &G); // initialize a new game
    //setting hands for all players after player 0 -- initalize game only sets hand for player 0
    for (int i = 1; i < numPlayers; i++)
    {
        G.handCount[i] = G.handCount[0];
        int j = 0;
        while(j < G.handCount[i])
        {
            drawCard(i, &G);
            j++;
        }
        
    }
    int randSmithyPos = rand() % G.handCount[testPlayer];
    
    //put smithy in hand
    replaceSmithy(&G, testPlayer, randSmithyPos);
    preHandCount = G.handCount[testPlayer];
    playSmithy(&G, randSmithyPos);
    
    postHandCount = G.handCount[testPlayer];
    
    //store test result
    testResults[0] = assertfalse(postHandCount, preHandCount);

#if (NOISY_TEST == 1)
    printf("\nTEST 2: Play smithy, verify smithy is removed from hand.\n");
#endif
    
    preHandCount = G.handCount[testPlayer];
    G.deckCount[testPlayer] = 2;
    
    randSmithyPos = rand() % G.handCount[testPlayer];
    replaceSmithy(&G, testPlayer, randSmithyPos);
    
    playSmithy(&G, randSmithyPos);
    
    postHandCount = G.handCount[testPlayer];
    
    //store test result
    testResults[1] = assertfalse(G.hand[testPlayer][randSmithyPos], k[6]);
    
#if (NOISY_TEST == 1)
    printf("\nTEST 3: Play smithy, insufficient number of cards are in deck.\n");
#endif
    
    preHandCount = G.handCount[testPlayer];
    G.deckCount[testPlayer] = rand() % 2;
    randSmithyPos = rand() % G.handCount[testPlayer];
    replaceSmithy(&G, testPlayer, randSmithyPos);
    
    playSmithy(&G, randSmithyPos);
    
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
    return (EXIT_SUCCESS);
}