/* -----------------------------------------------------------------------
 * Stephanie Creamer - CS 362, Winter 2017
 * Assignment 3
 * cardtest3.c - Testing great_hall card function
 * Test 1: Play great_hall, 1 card drawn from deck.
 * Test 2: Play great_hall, verify action is the same before and after playing card.
 * Test 3: Play great_hall, 0 cards in deck.
 * Test 4: Play great_hall, verify action is the same before and after playing card.
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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

void replaceCard(struct gameState *state, int testPlayer, int pos)
{
    state->hand[testPlayer][pos] = great_hall;
}

void initializeHand(struct gameState *state, int testPlayer)
{
    for (int i = 0; i < state->handCount[testPlayer]; i++)
    {
        state->hand[testPlayer][i] = adventurer;
    }
}

int main() {
    int seed = 1000;
    int numPlayers = 2;
    int testResults[4] = {-1};
    int testPlayer = 0;
    int great_hallPos = 0;
    int preActionCount = 0, postActionCount = 0, preHandCount = 0, postHandCount = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    printf ("TESTING great hall card:\n");
#if (NOISY_TEST == 1)
    printf("\nTEST 1: Play great hall, sufficient number of cards are in deck.\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &G); // initialize a new game
    printf("Actions: %i\n", G.numActions);
    //put great_hall in hand
    replaceCard(&G, testPlayer, great_hallPos);
    preHandCount = G.handCount[testPlayer];
    preActionCount = G.numActions;
    playCard(great_hallPos, 0, 0 , 0, &G);
    
    postHandCount = G.handCount[testPlayer];
    postActionCount = G.numActions;
    //store test result -- count should be the same because drew one card and discarded great hall
    testResults[0] = asserttrue(preHandCount, postHandCount);

#if (NOISY_TEST == 1)
    printf("\nTEST 2: Play great_hall, verify corrrect number of actions are returned.\n");
#endif
    
    //store test result -- number of actions should be the same; action gained replaces the action used to play the card
    testResults[1] = asserttrue(preActionCount, postActionCount);
    
#if (NOISY_TEST == 1)
    printf("\nTEST 3: Play great_hall, insufficient number of cards are in deck.\n");
#endif
    initializeGame(numPlayers, k, seed, &G);
    preHandCount = G.handCount[testPlayer];
    preActionCount = G.numActions;
    G.deckCount[testPlayer] = 2;
    replaceCard(&G, testPlayer, great_hallPos);
    
    playCard(great_hallPos, 0, 0 , 0, &G);
    postActionCount = G.numActions;
    postHandCount = G.handCount[testPlayer];
    
    //store test result
    testResults[2] = asserttrue(postHandCount, preHandCount); 
    
#if (NOISY_TEST == 1)
    printf("\nTEST 4: Play great_hall with insufficient cards, verify correct number of actions is returned.\n");
#endif
    
    //store test result -- number of actions should be the same; action gained replaces the action used to play the card
    testResults[3] = asserttrue(preActionCount, postActionCount);

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
