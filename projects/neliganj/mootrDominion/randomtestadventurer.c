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
		fprintf(stderr, "usage: randomtestadventurer [(int)seed]");
		exit(1);
	}

	int handCount, p, i, r, j, preDeckTreasureCount, preHandTreasureCount, postDeckTreasureCount, postHandTreasureCount, curCard;
	int testCycles = 10000;
	int numPlayer = 4;
	int maxHandCount = 5;
	int randomSeed = atoi(argv[1]);
	int k[10] = {adventurer, council_room, feast, gardens, mine
			, remodel, smithy, village, baron, great_hall};
	struct gameState G;

	int testPassed = 1;
	printf ("RANDOM TESTING playAdventurer():\n");

	for (i = 0; i < testCycles; i++)
	{
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, randomSeed, &G); // initialize a new game
		p = (rand() % numPlayer);
		handCount = (rand() % maxHandCount) + 1;
		G.handCount[p] = handCount;                 // set the number of cards on hand
		G.whoseTurn = p;

		if (NOISY_TEST)
		{
			printf("Cards in hand for player %d: %d\n", p, G.handCount[p]);
			printf("Cards in deck for player %d: %d\n", p, G.deckCount[p]);
		}

		preHandTreasureCount = 0;
		for (j = 0; j < G.handCount[p]; j++)
		{	curCard = G.hand[p][j];
			if (curCard == 4 || curCard == 5 || curCard == 6) // tally treasure cards in deck
			{
				preHandTreasureCount++;
			}
		}

		preDeckTreasureCount = 0;
		for (j = 0; j < G.deckCount[p]; j++)
		{	curCard = G.deck[p][j];
			if (curCard == 4 || curCard == 5 || curCard == 6) // tally treasure cards in deck
			{
				preDeckTreasureCount++;
			}
		}

		if (NOISY_TEST)
		{
			printf("Treasure cards in hand before playAdventurer(): %d\n", preHandTreasureCount);
			printf("Treasure cards in deck before playAdventurer(): %d\n", preDeckTreasureCount);
		}

		playAdventurer(&G);

		postHandTreasureCount = 0;
		for (j = 0; j < G.handCount[p]; j++)
		{	curCard = G.hand[p][j];
			if (curCard == 4 || curCard == 5 || curCard == 6) // tally treasure cards in deck
			{
				postHandTreasureCount++;
			}
		}

		postDeckTreasureCount = 0;
		for (j = 0; j < G.deckCount[p]; j++)
		{	curCard = G.deck[p][j];
			if (curCard == 4 || curCard == 5 || curCard == 6) // tally treasure cards in deck
			{
				postDeckTreasureCount++;
			}
		}

		if (NOISY_TEST)
		{
			printf("Treasure cards in hand after playAdventurer(): %d\n", postHandTreasureCount);
			printf("Treasure cards in deck after playAdventurer(): %d\n\n", postDeckTreasureCount);
		}

		// Check if tests were passed...
		if (preDeckTreasureCount > 2 && postHandTreasureCount == preHandTreasureCount + 2)
		{
			// test passed
		}
		else if (preDeckTreasureCount > 2 && postHandTreasureCount != preHandTreasureCount + 2)
		{
			// test failed
			testPassed = 0;
		}

		if (preDeckTreasureCount > 2 && postDeckTreasureCount == preDeckTreasureCount - 2)
		{
			// test passed
		}
		else if (preDeckTreasureCount == 1 && postDeckTreasureCount == 0 && postHandTreasureCount == preHandTreasureCount + 1)
		{
			// test passed
		}
		else if (preDeckTreasureCount == 0 && postDeckTreasureCount == 0 && postHandTreasureCount == preHandTreasureCount)
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

