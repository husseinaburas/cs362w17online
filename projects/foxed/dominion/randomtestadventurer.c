/************************
** Author: Eddie C. Fox
** Date: February 19, 2017
** Description: Automated randomized testing for the Adventurer card. 
** This was the only mandatory card, so I figured I would do it first.
************************/

/* Standard includes */

#include "dominion.h"
#include "dominion_helpers.h"

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include "rngs.h"

#include <assert.h>

/* Included my assertrue function from the unit tests. Should still work here. */
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

/* This is primarily where the testing takes place. It is called by the main function after all the initial
argument handling and randomized seeding has been completed. */

void testAdventurer()
{
	/* We construct the game much as we did in the unit testing. */

	struct gameState game;
	int kingdom[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	printf("--------- TESTING ADVENTURER CARD --------\n");
	printf("test can be found in randomtestadventure.c\n\n");

	int gameSeed = rand(); /* Create a random seed to seed the initialize game with each test. */

	int numPlayers = (rand() % 3) + 2; // Generate a random number of players between 2 and 4. 

	initializeGame(numPlayers, kingdom, gameSeed, &game);

	int maxDeckSize = 20; /* This variable doesn't change during testing, but I put it here so others can configure as they wish. */
	int actualDeckSize = (rand() % maxDeckSize); /* The reason I don't add 1 is to test cases where there is nothing in the deck. */
	int discardCount = (rand() % maxDeckSize) + 1; /* Set to +1 so i can test counterintuitive tests where the discard number exceeds the number of cards in the deck.*/

	int i;
	int j;
	int k;

	/* Set up the decks and discard piles for every player. */

	for (i = 0; i < numPlayers; i++) 
	{
		game.deckCount[i] = actualDeckSize;

		for (j = 0; j < actualDeckSize - 1; j++)  /* For every player we make all but the last card a copper.*/
		{
			game.deck[i][j] = copper;
		}

		
		int randomKingdom = rand() % 10; /* Contains the index of the kingdom card that the last card in the deck is. It has an index from 0 to 9.  */
		
		game.deck[i][actualDeckSize - 1] = kingdom[randomKingdom];

		if (actualDeckSize < 5) 
		{
			game.discardCount[i] = discardCount;
			for (k = 0; k < discardCount; k++) 
			{
				game.discard[i][k] = copper; /* Test discarding in cases where deck size is less than 5, discarding all copper. */
			}
		}
	}

	/* Print various variables related to testing before getting into it. */

	printf("Number of players during this test: %d\n", numPlayers);
	printf("Random game seed chosen: %d\n", gameSeed); 
	printf("Deck size: %d\n", actualDeckSize);
	printf("Discard count: %d\n", discardCount);

	int currentPlayer = 0; 

	for (currentPlayer; currentPlayer < numPlayers; currentPlayer++)
	{
		int deckCount = game.deckCount[currentPlayer];
		int handCount = game.handCount[currentPlayer];

		printf("Deck count of player %d: %d\n Hand count of player %d: %d\n\n", currentPlayer + 1, deckCount, currentPlayer + 1, handCount);

		/* Update coins after playing adventurer and report total. */

		updateCoins(currentPlayer, &game, 0);
		printf("Coins player has before Adventurer card is played: %d\n", game.coins);

		/* Let the player play adventurer. */

		printf("Player %d is now playing Adventurer\n", currentPlayer + 1);
		asserttrue(playAdventurer(&game, currentPlayer), 0); /* Use assert function to make sure that adventurer executed successfully. */

		/* Update coins after playing adventurer and report total. */

		updateCoins(currentPlayer, &game, 0);
		printf("Coins player has after Adventurer card is played: %d\n", game.coins);

		int postDeckCount = game.deckCount[currentPlayer];
		int postHandCount = game.handCount[currentPlayer];

		printf("Deck count of player %d after adventurer: %d\n Hand count of player %d after adventurer: %d\n\n", currentPlayer + 1, postDeckCount, currentPlayer + 1, postHandCount);

		asserttrue(postHandCount, handCount + 2); /* Adventurer should have drawn 2 treasure cards by the time it finishes. */
	}
	
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("Correct syntax: <program_name> <seed> <number of tests>\n");
	}

	else
	{
		int seed = atoi(argv[1]);
		srand(seed); /* Seed the randomized tester based on the seed provided in the second parameter.*/

		int numberOfTests = atoi(argv[2]); /* Assign number of tests from 3rd parameter to variable to be passed to testing function.*/
		
		int i;

		for (i = 0; i < numberOfTests; i++)
		{
			testAdventurer();
		}
	}

	return 0;
}