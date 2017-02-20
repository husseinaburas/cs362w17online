/************************
** Author: Eddie C. Fox
** Date: February 7, 2017
** Description: Unit testing for the Village card.
************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

typedef enum { false, true } bool; // Used for true and false.

								   // We were told to create our own assert function printing success and failure. The standard assert
								   // function can crash, and prevent coverage from being collected. 

int asserttrue(int left, int right)
{
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

	// Initial variable values. I need to bring these variables back because I don't have a refactored function with reduced parameters.

	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handpos = 0;
	int bonus = 0;

	int seed = 777;
	int numPlayers = 2;
	int thisPlayer = 0; // current player


	struct gameState game;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	printf("--------- TESTING VILLAGE CARD --------\n");
	printf("test can be found in cardtest3.c\n\n");

	// Initialize game

	initializeGame(numPlayers, k, seed, &game);

	game.whoseTurn = thisPlayer; // Set turn to current player
	game.numActions = 1; // Give them one action so they can play

	game.hand[0][0] = village; // Put village as the first card in the current players hand.
	game.handCount[0] = 1; // Set the players hand count to 1, as it now has 1 card. 

						   // Here we manually set each card in the deck so we can have more control in the future. 
						   // For village, the contents of the deck shouldn't matter, but this let's us adjust for debugging. 

	game.deck[0][0] = remodel;
	game.deck[0][1] = gold;
	game.deck[0][2] = curse;
	game.deck[0][3] = baron;
	game.deck[0][4] = copper;
	game.deck[0][5] = silver;

	game.deckCount[0] = 6; // Set deck Count appropriately. 

						   // No cards have been played yet and none have been discarded. Indicate as such.
	game.playedCardCount = 0;
	game.discardCount[0] = 0;

	asserttrue((cardEffect(village, choice1, choice2, choice3, &game, handpos, bonus)), 0); // Call card function while asserting it returns 0 when done.

	bool testsPassed = true;


	// The player should start with 1 card, draw 1, and then discard village, ending up with net +0 cards, having 1 card total in their hand.
	// Just like with adventurer, we test above and below for specificity. 

	if (game.handCount[0] > 1)
	{
		printf("Player drew too many cards or discarding does not work. FAILED. \n");
		printf("Hand Count: %d\n", game.handCount[0]);
		testsPassed = false;
	}

	if (game.handCount[0] < 1)
	{
		printf("Player didn't draw any cards. FAILED\n");
		printf("Hand Count: %d\n", game.handCount[0]);
		testsPassed = false;
	}

	// Village should be discarded.

	if (game.discardCount[0] != 1)
	{
		printf("Discard not working properly. FAILED\n");
		testsPassed = false;
	}

	// Only one card should have been played this game. 

	if (game.playedCardCount != 1)
	{
		printf("Village card not registered as played. FAILED\n");
		testsPassed = false;
	}

	// The deck started with 6 cards, so after drawing, the deck should have 5 cards. 

	if (game.deckCount[0] != 5)
	{
		printf("Improper deck count. FAILED\n");
		testsPassed = false;
	}

	asserttrue(game.handCount[0], 1);
	asserttrue(game.discardCount[0], 1);
	asserttrue(game.playedCardCount, 1);
	asserttrue(game.deckCount[0], 5);

	if (testsPassed == true)
	{
		printf("All tests passed.\n");
	}

	return 0;
}