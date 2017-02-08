/*
 * cardtest2.c
 *
 
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
	int seed = 1000;
	int numPlayers = 2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};

    struct gameState G;
	initializeGame(numPlayers, k, seed, &G);
	G.deckCount[0] = 0;
	G.discardCount[0] = 0;
	G.handCount[0] = 0;

    // initialize player 1 deck with golds.
    for (i = 0; i < deckSize; i++)
    {
	G.deck[0][i] = gold;
	G.deckCount[0]++;
    }

    // initialize player 1 discard with coppers
    for (i = 0; i < discardSize; i++)
    {
	G.discard[0][i] = copper;
	G.discardCount[0]++;
    }

    // initialize player 1 hand with silvers
    for (i = 0; i < 5; i++)
    {
	G.hand[0][i] = silver;
	G.handCount[0]++;
    }

	G.hand[0][0] = smithy; // smithy needs to play smithy from hand to activate

	printf("Starting hand:\n");
	for (i = 0; i< G.handCount[0]; i++){
		printf("%d ", G.hand[0][i]);
	}
	printf("\n");
	
	int startHandCount = G.handCount[0];
	int totalCards = G.handCount[0] + G.deckCount[0] + G.discardCount[0];

	// run playSmithy
    playSmithy(&G, 0);

	// Unit Test 1 -> Check that we have the correct number of treasure cards in hand
    printf("Number of cards in hand = %d, expected = %d\n", G.handCount[0], startHandCount + 3 - 1);
	asserttrue(G.handCount[0], startHandCount + 3 - 1);
	printf("Showing current cards in hand...\n");
	for (i = 0; i< G.handCount[0]; i++){
		printf("%d ", G.hand[0][i]);
	}
	printf("\nTotal cards for player 1 = %d, expected = %d\n", G.handCount[0] + G.deckCount[0] + G.discardCount[0], totalCards);
	asserttrue(G.handCount[0] + G.deckCount[0] + G.discardCount[0], totalCards);
	printf("\n\n");

	return 0;
}

void asserttrue(int val1, int val2)
{
    if (val1 != val2)
	printf("TEST FAILED \n");
    else
	printf("TEST PASSED \n");
}