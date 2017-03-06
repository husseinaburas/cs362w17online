#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: randomtestcard1 [(int)seed]");
		exit(1);
	}

	int handPos, handCount, actionCount, deckCount, p, i, r, j, preActionCount, preDeckCardCount, preHandCardCount, postActionCount, postDeckCardCount, postHandCardCount, curCard;
	int testCycles = 10000;
	int numPlayer = 4;
	int maxHandCount = 5;
	int maxDeckCount = 15;
	int maxActionCount = 3;
	int randomSeed = atoi(argv[1]);
	int k[10] = {adventurer, council_room, feast, gardens, mine
			, remodel, smithy, village, baron, great_hall};
	struct gameState G;

	int testPassed = 1;
	printf ("RANDOM TESTING playVillage():\n");

	for (i = 0; i < testCycles; i++)
	{
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, randomSeed, &G); // initialize a new game
		p = (rand() % numPlayer);
		handCount = (rand() % maxHandCount) + 1;        // set the number of cards on hand: 1 - maxHandCount
		deckCount =(rand() % (maxDeckCount + 1));		// set the number of cards in the deck: 0 - maxDeckCount
		actionCount = (rand() % maxActionCount) + 1;	// set the number of Actions: 1 - maxActionCount
		handPos = (rand() % handCount);                 // set hand position of Village card: 0 - handCount
		G.handCount[p] = handCount;
		G.deckCount[p] = deckCount;
		G.numActions = actionCount;
		G.whoseTurn = p;

		if (NOISY_TEST)
		{
			printf("Cards in hand for player %d: %d\n", p, G.handCount[p]);
			printf("Cards in deck for player %d: %d\n", p, G.deckCount[p]);
			printf("Number of Actions available: %d\n", G.numActions);
		}

		preHandCardCount = G.handCount[p];
		preDeckCardCount = G.deckCount[p];
		preActionCount = G.numActions;

		playVillage(&G, handPos);

		postHandCardCount = G.handCount[p];
		postDeckCardCount = G.deckCount[p];
		postActionCount = G.numActions;

		if (NOISY_TEST)
		{
			printf("Cards in hand after playVillage(): %d\n", postHandCardCount);
			printf("Cards in deck after playVillage(): %d\n", postDeckCardCount);
			printf("Number of Actions available after playVillage(): %d\n\n", postActionCount);
		}

		// Check if tests were passed...
		if (preDeckCardCount > 0 && postHandCardCount == preHandCardCount + 1 && postDeckCardCount == preDeckCardCount - 1)
		{
			// test passed
		}
		else if ( preDeckCardCount > 0 && (postHandCardCount != preHandCardCount + 1 || postDeckCardCount != preDeckCardCount - 1) )
		{
			// test failed
			testPassed = 0;
		}

		if (preActionCount + 2 == postActionCount)
		{
			// test passed
		}
		else
		{
			// test failed
			testPassed = 0;
		}
	}


	if (testPassed == 1)
	{
		printf("TEST PASSED\n\n");
	}
	else
	{
		printf("TEST FAILED\n\n");
	}

	return 0;
}

