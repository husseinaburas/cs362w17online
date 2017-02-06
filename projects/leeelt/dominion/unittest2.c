/* -----------------------------------------------------------------------
 * Author: Elton Lee
 * Date: 2-4-2017
 * unittest1.c
 * unit test for discardCard function
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main()
{
    int seed = 1000;
    int numPlayer = 2;
    int i;
    int p;
    int playedCard;
    int currentHandCount;
    int testHandCount = 5;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf("TESTING discardCoins():\n");
    for (p = 0; p < numPlayer; p++)
    {
        printf("\nRunning unittest2 for player %d\n", p + 1);
        for (i = 0; i < testHandCount; i++)
        {
            printf("\nTesting card in position %d\n", i);
            memset(&G, 23, sizeof(struct gameState)); // clear the game state
            initializeGame(numPlayer, k, seed, &G);   // initialize a new game

            // Test a. handPos = 0, trashFlag = 0
            initTest(&G, p);
            currentHandCount = G.handCount[p];
            playedCard = G.hand[p][i];
            printf("Test a. handPos = %d, trashFlag = 0\n", i);
            discardCard(i, p, &G, 0);
            printf("played count = %d, expected = %d\n", G.playedCardCount, 1);
            printf("played card enum = %d, expected = %d\n", G.playedCards[0], playedCard);
            printf("hand count = %d, expected = %d\n", G.handCount[p], currentHandCount - 1);
            assert(G.playedCardCount == 1);
            assert(G.playedCards[0] == playedCard);
            assert(G.handCount[p] == currentHandCount - 1);

            // Test b. trashFlag = 1
            initTest(&G, p);
            currentHandCount = G.handCount[p];
            printf("Test b. handPos = %d, trashFlag = 1\n", i);
            discardCard(i, p, &G, 1);
            printf("played count = %d, expected: %d\n", G.playedCardCount, 0);
            printf("hand count = %d, expected = %d\n", G.handCount[p], currentHandCount - 1);
            assert(G.playedCardCount == 0);
            assert(G.handCount[p] == currentHandCount - 1);
        }
    }

    printf("All tests passed!\n");
    return 0;
}

// function to initialize hand with pre-set 5 cards.
int initTest(struct gameState *G, int p)
{
    G->handCount[p] = 5;
    G->hand[p][0] = silver;
    G->hand[p][1] = gold;
    G->hand[p][2] = adventurer;
    G->hand[p][3] = smithy;
    G->hand[p][4] = copper;
    G->playedCardCount = 0;
    return 0;
}