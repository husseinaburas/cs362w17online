/************************
** Author: Eddie C. Fox
** Date: February 7, 2017
** Description: Unit testing for function.
************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


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

	struct gameState game;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	int seed = 777;
	int numPlayers = 2;
	int thisPlayer = 0; // current player

	printf("-------- UNIT TEST 2 ----------\n");
	printf("Testing numHandCards() function.\n");
	printf("Test can be found at unittest2.c\n");

	initializeGame(numPlayers, k, seed, &game);

	game.whoseTurn = thisPlayer; // Set turn to current player

	// When the game is done being initialized, the current players hand should have 5 cards. 

	asserttrue((numHandCards(&game)), 5);

	int i;

	for (i = 0; i < 20; i++)
	{
		game.handCount[0] = i; // Try change the number of cards player 1 has and test it against both the loop control variable and the numHandCards() function.

		asserttrue(game.handCount[0], i);
		asserttrue(numHandCards(&game), i);
		asserttrue(numHandCards(&game), game.handCount[0]);

		printf("Hand of player 1 has %d cards.\n", numHandCards(&game));
	}

	printf("Ending turn, then testing card hand numbers.\n");

	endTurn(&game);

	// Check to see if the number of cards derrived from the numHandCards() function becomes 5 again. 

	asserttrue(numHandCards(&game), 5);

	// Here we basically do the same thing we did with player 1 with player 2 instead, to make sure the function can properly change the player
	// in between turns from player 1 to player 2. 

	for (i = 0; i < 20; i++)
	{
		game.handCount[1] = i; // Try change the number of cards player 1 has and test it against both the loop control variable and the numHandCards() function.

		asserttrue(game.handCount[1], i);
		asserttrue(numHandCards(&game), i);
		asserttrue(numHandCards(&game), game.handCount[1]);

		printf("Hand of player 2 has %d cards.\n", numHandCards(&game));
	}

	printf("Testing of numHandCards() is finished.\n");
	return 0;
}