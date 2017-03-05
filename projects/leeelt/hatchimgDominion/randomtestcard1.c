/* Author: Elton Lee
 * randomtestcard1.c
 * random testing for smithy 
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 * 		gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS);
 */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "rngs.h"
#include "randomtestcard1.h"
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
		int deckSize = rand() % (30 + 1);
		int discardSize = rand() % (30 + 1);
    	if (runCardTest(deckSize, discardSize) == 1){
			++numFailedTests;
		} else {
			++numPassedTests;
		}
	}
	printf("\nSeed used: %d\n", test_seed);
	printf("Number of passed test cases: %d\nNumber of failed tests case: %d\n", numPassedTests, numFailedTests);

	return 0;
}


// Function: runCardTest()
// Description: Tests the smithy card. User provides a deck size and a discard size.
//				Returns 0 if test passed. Returns 1 if test failed.
int runCardTest(int deckSize, int discardSize)
{
    printf("Running smithy test with %d cards in deck and %d cards in discard\n", deckSize, discardSize);
    int i;
	int j;
	int test_failed_flag = 0;
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

    int startHandCount = G.handCount[0];
    int totalCards = G.handCount[0] + G.deckCount[0] + G.discardCount[0];
	int totalCardsPlayer2 = G.handCount[1] + G.deckCount[1] + G.discardCount[1];

    // run play_smithy
    play_smithy(&G, 0);

    // Check +3 to hand and smithy is gone
    printf("-----TEST 1: CHECK +3 CARDS TO HAND AND SMITHY NO LONGER IN HAND-----\n");
    printf("Number of cards in hand = %d, expected = %d\n", G.handCount[0], startHandCount + 3 - 1);
	printf("Showing current cards in hand...\n");
    for (i = 0; i < G.handCount[0]; i++)
    {
		printf("%d ", G.hand[0][i]);
    }
	printf("\n");
    if ( asserttrue(G.handCount[0], startHandCount + 3 - 1) == 1 ) test_failed_flag = 1;

	// Check that 3 drawn cards came from player 1's deck.
	printf("-----TEST 2: CHECK THAT 3 DRAWN CARDS CAME FROM PLAYER 1's DECK-----\n");
	printf("Number of cards in deck + discard = %d, expected = %d\n", G.deckCount[0] + G.discardCount[0], totalCards - startHandCount - 3);
	if (asserttrue(G.deckCount[0] + G.discardCount[0], totalCards - startHandCount - 3) == 1) test_failed_flag = 1;
	// Check card total for players
	printf("-----TEST 3: CHECK DECK TOTALS FOR BOTH PLAYERS-----\n");
    printf("Total cards for player 1 = %d, expected = %d\n", G.handCount[0] + G.deckCount[0] + G.discardCount[0], totalCards);
    asserttrue(G.handCount[0] + G.deckCount[0] + G.discardCount[0], totalCards);
    printf("Total cards for player 2 = %d, expected = %d\n", G.handCount[1] + G.deckCount[1] + G.discardCount[1], totalCardsPlayer2);
    if (asserttrue(G.handCount[1] + G.deckCount[1] + G.discardCount[1], totalCardsPlayer2) == 1) test_failed_flag = 1;
    return test_failed_flag;
}


// Function: asserttrue()
// Description: Implementation of isEqual for integers used for testing.
//				Returns 1 if values are equal. Else return 0.
int asserttrue(int val1, int val2)
{
    if (val1 != val2) {
		printf("TEST FAILED \n");
		return 1;
	}
    else {
		printf("TEST PASSED \n");
		return 0;
	}
}