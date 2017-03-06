/* -----------------------------------------------------------------------
 * Stephanie Creamer - CS 362, Winter 2017
 * Assignment 3
 * cardtest1.c - Testing adventurer card function
 * Test 1: Only one treasure in deck, verify only one is added to hand (also forces shuffle)
 * Test 2: No treasures in deck.
 * Test 3: Treasure in discard and not deck or hand (this is to test that the deck is shuffled).
 *
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
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

void resetHand(struct gameState *state, int testPlayer, int card)
{
    for (int i = 0; i < state->handCount[testPlayer]; i++)
    {
        state->hand[testPlayer][i] = card;
    }  
}

void coinCount(struct gameState *state, int* coins, int testPlayer)
{
    for (int i = 0; i < state->handCount[testPlayer]; i++)
    {
        if ((state->hand[testPlayer][i]) == copper)
            coins[0]++;
        if ((state->hand[testPlayer][i]) == silver)
            coins[1]++;
        if ((state->hand[testPlayer][i]) == gold)
            coins[2]++;
    }  
}

int main() {
    int seed = 1000;
    int numPlayers = 2;
    int testResults[2] = {-1};
    int testPlayer = 0;
    int numCoins = 3;
    int preCardGoldCount = 0, postCardGoldCount = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    //keep track of coins
    int* coinCounter = malloc(numCoins * sizeof(int));
    for (int i = 0; i < numCoins; i++)
    {
        coinCounter[i] = 0;
    }
    //int k[6] = {curse, estate, duchy, province, great_hall, gardens};
    struct gameState G;
    
    printf ("TESTING adventurer card:\n");
#if (NOISY_TEST == 1)
    printf("\nTEST 1: Only 1 treasure in deck.\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &G); // initialize a new game
    
    //get coins in hand
    coinCount(&G, coinCounter, 0);
    preCardGoldCount = coinCounter[2];
 
    //put one gold on top of deck
    G.deck[testPlayer][0] = gold;

    //set all other cards to a non-treasure card
    for (int i = 1; i < G.deckCount[0]; i++)
    {
        G.deck[testPlayer][i] = k[0];
    }
    
    playAdventurer(&G);
    
    //get coins in new hand
    coinCount(&G, coinCounter, 0);
    postCardGoldCount = coinCounter[2];
    
    //store test result
    testResults[0] = asserttrue(postCardGoldCount+1, preCardGoldCount);
    
#if (NOISY_TEST == 1)
    printf("\nTEST 2: 0 treasures in deck.\n");
#endif  
    
    //resetting test parameters to handful of copper
    resetHand(&G, 0, copper);
    preCardGoldCount = 0;
    postCardGoldCount = 0;

    coinCount(&G, coinCounter, 0);
    preCardGoldCount = coinCounter[2];
    
    //set all other cards to a non-treasure card
    for (int i = 0; i < MAX_DECK; i++)
    {
        G.deck[0][i] = k[0];
    }
    playAdventurer(&G);
    coinCount(&G, coinCounter, 0);
    postCardGoldCount = coinCounter[2];
    
    testResults[1] = asserttrue(postCardGoldCount, preCardGoldCount);

#if (NOISY_TEST == 1)
    printf("\nTEST 3: 1 gold treasures in discard.\n");
#endif  
    
    //resetting test parameters to handful of copper
    resetHand(&G, 0, copper);
    preCardGoldCount = 0;
    postCardGoldCount = 0;
    
    coinCount(&G, coinCounter, 0);
    preCardGoldCount = coinCounter[2];
        
    //set all other cards to a non-treasure card
    for (int i = 0; i < MAX_DECK; i++)
    {
        G.deck[0][i] = k[0];
    }
    
    //set gold on top of discard
    G.discard[testPlayer][0] = gold;
    
    playAdventurer(&G);
    coinCount(&G, coinCounter, 0);
    postCardGoldCount = coinCounter[2];
        
    testResults[2] = asserttrue(postCardGoldCount+1, preCardGoldCount);
    
    
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