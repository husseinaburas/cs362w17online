/* Author: Elton Lee
 * cardtest1.c
 * unit test for adventurer
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include "randomtestadventurer.h"

int main( int argc, char *argv[])
{
	// seed program with user input or call srand with time(NULL)
	int test_seed;
	if ( argc == 2) {
		test_seed = atoi(argv[1]);
		srand(test_seed);
	} else {
		srand(time(NULL));
	}

	int i;
    // Using rand to get a number = [min_number, max_number]
	// rand() % (max_number + 1 - min_number) + min_number
	int deckTreasure = rand() % (6 + 1 - 4) + 4; // enum 4-6 represents copper, silver, gold
	int deckTreasureCount = rand() % (130 + 1);  // initialize deck with copper, silver, or gold
	int deckSize = rand() % ((200-deckTreasureCount) + 1);  // initialize deck with 0 - 200 cards
	int discardTreasure = rand() % (2 + 1);  // initialize discard pile with copper, silver, or gold
	int discardTreasureCount = rand() % (130 + 1); // intialize discard with 0 - 130 treasure cards
	int discardCount = rand() % ((200 - discardTreasureCount) + 1); // initialize discard with 0 to 200 treasure cards
	int numFailedTests = 0;
	int numPassedTests = 0;
	for (i = 0; i < 1000; ++i)
		runCardTest(deckTreasure, deckTreasureCount, deckSize, discardTreasure, discardTreasureCount, discardCount, &numFailedTests, &numPassedTests);

	printf("Number of unit tests passed: %d\nNumber of unit tests failed: %d\n", numPassedTests, numFailedTests);
    return 0;
}

int runCardTest(int deckTreasure, int deckTreasureCount, int deckSize, int discardTreasure, int discardTreasureCount, int discardSize, int* numFailedTests, int* numPassedTests)
{
	printf("RUNNING playAdventurer WITH %d TREASURES(enum = %d) IN DECK AND %d TREASURES(enum = %d) DISCARD\n", deckTreasureCount, deckTreasure, discardTreasureCount, discardTreasure);
	int i;
	int seed = 1000;
	int numPlayers = 2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};
	int expectedTreasure = discardTreasureCount + deckTreasureCount; // holds the amount of treasure that we will draw
	if (expectedTreasure > 2){
		expectedTreasure = 2;
	}
    struct gameState G;
	initializeGame(numPlayers, k, seed, &G);
	G.deckCount[0] = 0;

    // initialize player 1 deck.
    for (i = 0; i < deckTreasureCount; i++)
    {
	G.deck[0][i] = deckTreasure;
	G.deckCount[0]++;
    }

    for (i = G.deckCount[0]; i < deckSize; i++)
    {
	G.deck[0][i] = smithy;
	G.deckCount[0]++;
    }

    // initialize player 1 discard
    for (i = 0; i < discardTreasureCount; i++)
    {
	G.discard[0][i] = discardTreasure;
	G.discardCount[0]++;
    }
    for (i = G.discardCount[0]; i < discardSize; i++)
    {
	G.discard[0][i] = smithy;
	G.discardCount[0]++;
    }

    // initialize player 1 hand
    G.hand[0][0] = adventurer;
	G.hand[0][1] = gold;
	G.hand[0][2] = silver;
    G.hand[0][3] = smithy;
   	G.hand[0][4] = adventurer;
    G.handCount[0] = 5;
	printf("Starting hand:\n");
	for (i = 0; i< G.handCount[0]; i++){
		printf("%d ", G.hand[0][i]);
	}
	printf("\n");
	
	int startHandCount = G.handCount[0];
	int totalCards = G.handCount[0] + G.deckCount[0] + G.discardCount[0];

	// run playAdventurer
    playAdventurer(&G);

	// Unit Test 1 -> Check that we have the correct number of treasure cards in hand
	printf("-----TEST 1: CHECK +2 TREASURE CARD TO HAND AND ADVENTURER NO LONGER IN HAND-----\n");
    printf("Number of cards in hand = %d, expected = %d\n", G.handCount[0], startHandCount + expectedTreasure - 1);
	if (asserttrue(G.handCount[0], startHandCount + expectedTreasure - 1) == 0){
		*numFailedTests = *numFailedTests + 1;
	} else {
		*numPassedTests = *numPassedTests + 1;
	}
	;
	printf("Showing current cards in hand...\n");
	for (i = 0; i< G.handCount[0]; i++){
		printf("%d ", G.hand[0][i]);
	}
	printf("\n");

	printf("-----TEST 2: CHECK TOTAL CARDS FOR PLAYER 1 HAS NOT CHANGED-----\n");
	printf("Total cards for player 1 = %d, expected = %d\n", G.handCount[0] + G.deckCount[0] + G.discardCount[0], totalCards);
	if (asserttrue(G.handCount[0] + G.deckCount[0] + G.discardCount[0], totalCards) == 0){
		*numFailedTests = *numFailedTests + 1;
	} else {
		*numPassedTests = *numPassedTests + 1;

	}
	printf("\n\n");

	return 0;
}

int asserttrue(int val1, int val2)
{
    if (val1 != val2) {
		printf("TEST FAILED \n");
		return 0;
	}
    else {
		printf("TEST PASSED \n");
		return 1;
	}
}