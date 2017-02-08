/* Author: Elton Lee
 * cardtest2.c
 * unit test for smithy 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "cardtest2.h"

int main()
{
    runCardTest(5, 0);
    runCardTest(0, 5);
    runCardTest(1, 5);
    return 0;
}

int runCardTest(int deckSize, int discardSize)
{
    printf("Running smithy test with %d cards in deck and %d cards in discard\n", deckSize, discardSize);
    int i;
	int j;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};

    struct gameState G;
    initializeGame(numPlayers, k, seed, &G);

    for (j = 0; j < numPlayers; j++)
    {
	G.deckCount[j] = 0;
	G.discardCount[j] = 0;
	G.handCount[j] = 0;

	// initialize player j deck with golds.
	for (i = 0; i < deckSize; i++)
	{
	    G.deck[j][i] = gold;
	    G.deckCount[j]++;
	}

	// initialize player j discard with coppers.
	for (i = 0; i < discardSize; i++)
	{
	    G.discard[j][i] = copper;
	    G.discardCount[j]++;
	}

	// initialize player j hand with silvers
	for (i = 0; i < 5; i++)
	{
	    G.hand[j][i] = silver;
	    G.handCount[j]++;
	}

	G.hand[0][0] = smithy; // smithy needs to play smithy from hand to activate
    }

    printf("Starting hand:\n");
    for (i = 0; i < G.handCount[0]; i++)
    {
	printf("%d ", G.hand[0][i]);
    }
    printf("\n");

    int startHandCount = G.handCount[0];
    int totalCards = G.handCount[0] + G.deckCount[0] + G.discardCount[0];
	int totalCardsPlayer2 = G.handCount[1] + G.deckCount[1] + G.discardCount[1];

    // run playSmithy
    playSmithy(&G, 0);

    // Check +3 to hand and smithy is gone
    printf("-----TEST 1: CHECK +3 CARDS TO HAND AND SMITHY NO LONGER IN HAND-----\n");
    printf("Number of cards in hand = %d, expected = %d\n", G.handCount[0], startHandCount + 3 - 1);
    asserttrue(G.handCount[0], startHandCount + 3 - 1);
    printf("Showing current cards in hand...\n");
    for (i = 0; i < G.handCount[0]; i++)
    {
	printf("%d ", G.hand[0][i]);
    }

	// Check that 3 drawn cards came from player 1's deck.
	printf("-----TEST 2: CHECK THAT 3 DRAWN CARDS CAME FROM PLAYER 1's DECK-----\n");
	printf("Number of cards in deck + discard = %d, expected = %d\n", G.deckCount[0] + G.discardCount[0], totalCards - startHandCount - 3);
	asserttrue(G.deckCount[0] + G.discardCount[0], totalCards - startHandCount - 3);

	// Check card total for players
	printf("-----TEST 3: CHECK DECK TOTALS FOR BOTH PLAYERS-----\n");
    printf("Total cards for player 1 = %d, expected = %d\n", G.handCount[0] + G.deckCount[0] + G.discardCount[0], totalCards);
    asserttrue(G.handCount[0] + G.deckCount[0] + G.discardCount[0], totalCards);
    printf("Total cards for player 2 = %d, expected = %d\n", G.handCount[1] + G.deckCount[1] + G.discardCount[1], totalCardsPlayer2);
    asserttrue(G.handCount[1] + G.deckCount[1] + G.discardCount[1], totalCardsPlayer2);

    return 0;
}

void asserttrue(int val1, int val2)
{
    if (val1 != val2)
	printf("TEST FAILED \n");
    else
	printf("TEST PASSED \n");
}