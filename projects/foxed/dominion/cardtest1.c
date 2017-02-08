/************************
** Author: Eddie C. Fox
** Date: February 7, 2017
** Description: Unit testing for the Smithy card. This card is mandatory to test, and simpler than most,
** so I figured I would test it first. This test is based off the first case in the cardtest4.c sample given to us.
** The main difference is that smithy gives 3 cards instead of 2. 
************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

// We were told to create our own assert function printing success and failure. The standard assert
// function can crash, and prevent coverage from being collected. 

int asserttrue(int left, int right)
{
	int thisPlayer = 0;
	if (left == right)
	{
		printf("Test PASSED\n");
	}

	else
	{
		printf("Test FAILED\n");
	}
}

int main()
{
	
	// Initial variable values.

	int newCards = 0;
	int extraCoins = 0;
	int discarded = 1;
	int shuffled = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handpos = 0;
	int bonus = 0;

	int seed = 777;
	int numPlayers = 2;
	

	// Here we adopt the sample card tests technique of creating two gamestates, and copying over an untouched gamestate after
	// every test. And also comparing the modified gamestate to the original gamestate plus what modifications should have occured.

	struct gameState original, test;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	printf("--------- TESTING SMITHY CARD --------\n");
	printf("test can be found in cardtest1.c\n\n");

	// Initialize game

	initializeGame(numPlayers, k, seed, &original);
	memcpy(&test, &original, sizeof(struct gameState)); // Copy over untouched game state to the test.

	asserttrue((cardEffect(smithy, choice1, choice2, choice3, &test, handpos, bonus)), 0); // Call card function while asserting it returns 0 when done.

	newCards = 3;

	int thisPlayer;
	printf("Hand Count = %d, Expected = %d\n", test.handCount[thisPlayer], original.handCount[thisPlayer] + newCards - discarded);
	printf("Deck Count = %d, Expected = %d\n", test.deckCount[thisPlayer], original.deckCount[thisPlayer] - newCards + shuffled);
	printf("coins = %d, expected = %d\n", test.coins, original.coins + extraCoins);

	asserttrue(test.handCount[thisPlayer], (original.handCount[thisPlayer] + newCards - discarded));
	asserttrue(test.deckCount[thisplayer], (original.deckCount[thisPlayer] - newCards + shuffled));
	asserttrue(test.coins, (original.coins + extraCoins));

	return 0;
}