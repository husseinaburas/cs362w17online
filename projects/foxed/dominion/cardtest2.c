/************************
** Author: Eddie C. Fox
** Date: February 7, 2017
** Description: Unit testing for the Adventurer card. This card is a mandatory card, but more complicated than
** Smithy, so I did it second.
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

void asserttrue(int left, int right)
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

	// Initial variable values.

	
	int seed = 777;
	int numPlayers = 2;
	int thisPlayer = 0; // current player

	// Because this test is more complicated, I just used a single game state. Perhaps an alternative game state would have been better,
	// but I was running lower on time at this point, and figured assertions on expected values with a single game state would be sufficient.
	// Also, this gives me more practice than just using the example method. 

	struct gameState game;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	printf("--------- TESTING ADVENTURER CARD --------\n");
	printf("test can be found in randomtestadventure.c\n\n");

	// Initialize game

	initializeGame(numPlayers, k, seed, &game);

	game.whoseTurn = thisPlayer; // Set turn to current player
	game.numActions = 1; // Give them one action so they can play

	game.hand[0][0] = adventurer; // Put adventurer as the first card in the current players hand.
	game.handCount[0] = 1; // Set the players hand count to 1, as it now has 1 card. 

						   // Here we manually set each card in the deck so we can have more control in the future. 
						   // We want to space the treasures out so we can test the discard function.

	// Deck from top to bottom is: Copper, mine, gardens, silver, gold. Adventurer is in the players hand, and their only card. 

	game.deck[0][0] = copper;
	game.deck[0][1] = mine;
	game.deck[0][2] = gardens;
	game.deck[0][3] = silver;
	game.deck[0][4] = gold;

	game.deckCount[0] = 5; // Set deck Count appropriately. 

	// No cards have been played yet and none have been discarded. Indicate as such.
	game.playedCardCount = 0;
	game.discardCount[0] = 0;
	
	asserttrue((playAdventurer(&game, thisPlayer)), 0); // Call the adventurer card function and assert that it returns 0. 
	
	// Adventurer is the only card in the hand, and it is discarded with all non-treasures after the card is played. Adventurer makes you draw
	// two treasures. Therefore if the hand count is not 2, there is a problem. We divide up the cases into too many and too little for more specificity.

	bool testsPassed = true;

	if (game.handCount[0] > 2) 
	{ 
		printf("Player drew too many cards or discarding does not work. FAILED. \n");
		printf("Hand Count: %d\n", game.handCount[0]);
		testsPassed = false;
	}

	
	if (game.handCount[0] < 2) 
	{
		printf("Player didn't draw enough cards. FAILED\n");
		printf("Hand Count: %d\n", game.handCount[0]);
		testsPassed = false;
	}

	
	// Adventurer + Mine + Gardens should be discarded. 

	if (game.discardCount[0] != 3) 
	{ 
		printf("Discard not working properly. FAILED\n");
		testsPassed = false;
	}

	// Although playing the card is an action, playAdventurer doesn't deduct action points. That's what playCard() does. 

	if (game.numActions != 1) 
	{  
		printf("playAdventurer() deducting action points when it shouldn't. FAILED\n");
		testsPassed = false;
	}

	asserttrue(game.handCount[0], 2);
	asserttrue(game.discardCount[0], 3);
	asserttrue(game.numActions, 1);

	if (testsPassed == true)
	{
		printf("All tests passed.\n");
	}
	
	return 0;
}