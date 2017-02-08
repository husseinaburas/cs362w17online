/* Author: Elton Lee
 * cardtest4.c
 * unit test for feast
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "cardtest4.h"

int main()
{
    runCardTest(council_room);
    runCardTest(copper);
	//runCardTest(adventurer); // causes an infinite loop
    return 0;
}

int runCardTest(int chosenCard)
{
    printf("Running feast using enum #%d card, cost = %d\n", chosenCard, getCost(chosenCard));
    int i;
    int j;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};
	int deckSize = 10;
	int discardSize = 10;

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

		G.hand[j][0] = feast; // set feast to the first card in hand
    }
    printf("Starting hand:\n");
    for (i = 0; i < G.handCount[0]; i++)
    {
		printf("%d ", G.hand[0][i]);
    }
    printf("\n");

	printf("Starting discard:\n");
    for (i = 0; i < G.discardCount[0]; i++)
    {
		printf("%d ", G.discard[0][i]);
    }
    printf("\n");
    int startHandCount = G.handCount[0];
	int startDiscardCount = G.discardCount[0];
    int totalCards = G.handCount[0] + G.deckCount[0] + G.discardCount[0];
    int initialSupplyCount = G.supplyCount[chosenCard];

    // run play feast
    playFeast(&G, chosenCard);

	// Check that feast has been trashed.
	printf("-----TEST 1: CHECKING FEAST HAS BEEN TRASHED ----\n");
	printf("Number of cards in player 1's hand = %d, expected = %d\n", G.handCount[0], startHandCount-1);
    asserttrue(G.handCount[0], startHandCount-1);
    printf("Showing current cards in hand...\n");
    for (i = 0; i < G.handCount[0]; i++)
    {
		printf("%d ", G.hand[0][i]);
    }

    // Check new card obtained has been placed in the discard pile.
	printf("\n-----TEST 2: CHECKING SELECTED CARD IS IN DISCARD PILE-----\n");
    printf("Number of cards in player 1's discard = %d, expected = %d\n", G.discardCount[0], startDiscardCount + 1);
    asserttrue(G.discardCount[0], startDiscardCount + 1);
    printf("Showing current cards in discard...\n");
    for (i = 0; i < G.discardCount[0]; i++)
    {
		printf("%d ", G.discard[0][i]);
    }

    // Check player has right total cards
	printf("\n-----TEST 3: CHECKING PLAYER 1 HAS THE RIGHT AMOUNT OF CARDS-----\n");
    printf("Total cards for player 1 = %d, expected = %d\n", G.handCount[0] + G.deckCount[0] + G.discardCount[0], totalCards);
    asserttrue(G.handCount[0] + G.deckCount[0] + G.discardCount[0], totalCards);

    // Checking supply has right num of cards
    printf("-----TEST 4: CHECKING SUPPLY OF enum#%d HAS 1 LESS CARD-----\n", chosenCard);
    printf("supply = %d, expected = %d\n", G.supplyCount[chosenCard], initialSupplyCount - 1);
    asserttrue(G.supplyCount[chosenCard], initialSupplyCount - 1);

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