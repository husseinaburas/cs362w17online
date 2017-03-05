/* Author: Elton Lee
 * randomtestcard2.c
 * random testing for council_room
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard2: randomtestcard2.c dominion.o rngs.o
 * 		gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS);
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "rngs.h"
#include "randomtestcard2.h"
#include "dominion.h"
#include "dominion_helpers.h"

int main(int argc, char *argv[])
{
	// seed program with user input or call srand with time(NULL)
	int test_seed;
	time_t t;
	if ( argc == 2) {
		test_seed = atoi(argv[1]);
	} else {
		test_seed = (unsigned) time(&t);
	}
	srand(test_seed);

	int i;
	int numPassedTests = 0;
	int numFailedTests = 0;
	for (i = 0; i < 1000; ++i){
		// Using rand to get a number = [min_number, max_number]
		// rand() % (max_number + 1 - min_number) + min_number
		int deckSize = rand() % (10 + 1);
		int discardSize = rand() % (10 + 1);
    	if (runCardTest(deckSize, discardSize) == -1){
			++numFailedTests;
		} else {
			++numPassedTests;
		}
	}
	printf("\nSeed used: %d\n", test_seed);
	printf("Number of passed test cases: %d\nNumber of failed tests case: %d\n", numPassedTests, numFailedTests);
    return 0;
}

int runCardTest(int deckSize, int discardSize)
{
    printf("\nRunning council_room test with %d cards in deck and %d in discard\n", deckSize, discardSize);
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

		G.hand[j][0] = council_room; // council_room needs to be played from hand
    }

    printf("Starting hand:\n");
    for (i = 0; i < G.handCount[0]; i++)
    {
		printf("%d ", G.hand[0][i]);
    }

    int startHandCount = G.handCount[0];
    int totalCards = G.handCount[0] + G.deckCount[0] + G.discardCount[0];
    int startNumBuys = G.numBuys;
    int startHandCountPlayer2 = G.handCount[1];
	int totalCardsPlayer2 = G.handCount[1] + G.deckCount[1] + G.discardCount[1];

    // run play council_room
    playCouncil_Room(&G, 0);

    // Check +4 cards to hand
	printf("\n-----TEST 1: CHECKING +4 TO HAND AND COUNCIL_ROOM NO LONGER IN HAND-----\n");
    printf("Number of cards in player 1's hand = %d, expected = %d\n", G.handCount[0], startHandCount + 4 - 1);
    asserttrue(G.handCount[0], startHandCount + 4 - 1);
    printf("Showing current cards in hand...\n");
    for (i = 0; i < G.handCount[0]; i++)
    {
		printf("%d ", G.hand[0][i]);
    }

    // Check +1 buy action
	printf("\n-----TEST 2: CHECK +1 BUY ADDED TO PLAYER 1-----\n");
    printf("Number of buys for player 1 = %d, expected = %d\n", G.numBuys, startNumBuys + 1);
    if (asserttrue(G.numBuys, startNumBuys + 1) == -1) return -1;
	
	// Check +1 card to player 2
	printf("-----TEST 3: CHECK OTHER PLAYER +1 CARD TO HAND-----\n");
    printf("Number of cards in player 2's hand = %d, expected = %d\n", G.handCount[1], startHandCountPlayer2 + 1);
    if (asserttrue(G.handCount[1], startHandCountPlayer2 + 1) == -1) return -1;
	
	// Check card total for players
	printf("-----TEST 4: CHECK DECK TOTALS FOR BOTH PLAYERS-----\n");
    printf("Total cards for player 1 = %d, expected = %d\n", G.handCount[0] + G.deckCount[0] + G.discardCount[0], totalCards);
    if (asserttrue(G.handCount[0] + G.deckCount[0] + G.discardCount[0], totalCards) == -1) return -1;
    printf("Total cards for player 2 = %d, expected = %d\n", G.handCount[1] + G.deckCount[1] + G.discardCount[1], totalCardsPlayer2);
    if (asserttrue(G.handCount[1] + G.deckCount[1] + G.discardCount[1], totalCardsPlayer2) == -1) return -1;

    return 0;
}

int asserttrue(int val1, int val2)
{
    if (val1 != val2) {
		printf("TEST FAILED \n");
		return -1;
	}
    else {
		printf("TEST PASSED \n");
		return 0;
	}
}