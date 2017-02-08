/************************
** Author: Eddie C. Fox
** Date: February 7, 2017
** Description: Unit testing for the Council Room card.
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

	
	int handpos = 0;

	int seed = 777;
	int numPlayers = 2;
	int thisPlayer = 0; // current player


	struct gameState game;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	printf("--------- TESTING COUNCIL ROOM CARD --------\n");
	printf("test can be found in cardtest4.c\n\n");

	// Initialize game

	initializeGame(numPlayers, k, seed, &game);

	game.whoseTurn = thisPlayer; // Set turn to current player
	game.numActions = 1; // Give them one action so they can play
	game.numBuys = 1; // Give them one buy point so we can see if this card gives them a second one. 

	game.hand[0][0] = council_room; // Put Council Room as the first card in the current players hand.
	game.handCount[0] = 1;         // Set the players hand count to 1, as it now has 1 card. 

	game.handCount[1] = 1; // Give the second player one card to start off with. 

// Here we manually set each card in the deck so we can have more control in the future. 
// For Council Room, the contents of the deck shouldn't matter, but this let's us adjust for debugging. 

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

	asserttrue((playCouncil_Room(&game, thisPlayer, 0)), 0);

	bool testsPassed = true;


	// The player should start with 1 card, draw 4, and then discard Council Room, ending up with net +3 cards, having 4 cards total in their hand.
	// Just like with adventurer, we test above and below for specificity. 

	if (game.handCount[0] > 4)
	{
		printf("Player drew too many cards or discarding does not work. FAILED. \n");
		printf("Hand Count: %d\n", game.handCount[0]);
		testsPassed = false;
	}

	if (game.handCount[0] < 4)
	{
		printf("Player didn't draw enough cards. FAILED\n");
		printf("Hand Count: %d\n", game.handCount[0]);
		testsPassed = false;
	}

	// Current player should have another buy point, bringing them to two. 

	if (game.numBuys != 2)
	{
		printf("Buy points improperly incremented. FAILED\n");
		printf("Buy points : %d\n", game.numBuys);
		testsPassed = false;
	}

	// Second player should have 2 cards, as they started with one and this card draws them another one. 

	if (game.handCount[1] != 2)
	{
		printf("Second player recieved improper or none amount of cards. FAILED\n");
		printf("Number of cards of second player: %d\n", game.handCount[1]);
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

	// The deck started with 6 cards, so after drawing, the deck should have 2 cards. 

	if (game.deckCount[0] != 2)
	{
		printf("Improper deck count. FAILED\n");
		testsPassed = false;
	}

	asserttrue(game.handCount[0], 4);
	asserttrue(game.handCount[1], 2);
	asserttrue(game.numBuys, 2);
	assertture(game.discardCount[0], 1);
	asserttrue(game.playedCount, 1);
	asserttrue(game.deckCount[0], 2);

	if (testsPassed == true)
	{
		printf("All tests passed.\n");
	}

	return 0;
}