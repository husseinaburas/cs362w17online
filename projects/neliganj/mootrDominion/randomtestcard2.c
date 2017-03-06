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
		fprintf(stderr, "usage: randomtestcard2 [(int)seed]");
		exit(1);
	}

	int handPos, p, i, r, j, preBuyCount, postBuyCount, handCount;
	int testCycles = 10000;
	int numPlayer = 4;
	int preHandCount[numPlayer];
	int postHandCount[numPlayer];
	int maxHandCount = 5;
	int maxBuyCount = 3;
	int randomSeed = atoi(argv[1]);
	int k[10] = {adventurer, council_room, feast, gardens, mine
			, remodel, smithy, village, baron, great_hall};
	struct gameState G;

	int testPassed = 1;
	printf ("RANDOM TESTING playCouncil_Room():\n");

	for (i = 0; i < testCycles; i++)
	{
		memset(&G, 23, sizeof(struct gameState));          // clear the game state
		r = initializeGame(numPlayer, k, randomSeed, &G);  // initialize a new game

		p = (rand() % numPlayer);                          // set turn to random player
		for (j = 0; j < numPlayer; j++)
		{
			handCount = (rand() % maxHandCount) + 1;
			G.handCount[j] = handCount;                    // set the number of cards on hand for each player: 1 - maxHandCount
			preHandCount[j] = handCount;
		}
		G.numBuys = (rand() % maxBuyCount) + 1;	           // set the number of Buys: 1 - maxBuyCount;
		preBuyCount = G.numBuys;
		G.whoseTurn = p;
		handPos = (rand() % G.handCount[p]);               // set hand position of Village card: 0 - handCount

		if (NOISY_TEST)
		{
			printf("Number of Buys available before playCouncil_Room(): %d\n", G.numBuys);
			printf("Card player: %d\n", p);
			for (j = 0; j < numPlayer; j++)
			{
				printf("Cards in hand for player %d before playCouncil_Room(): %d\n", j, G.handCount[j]);
			}
			printf("\n");
		}

		playCouncil_Room(&G, handPos);

		for (j = 0; j < numPlayer; j++)
		{
			postHandCount[j] = G.handCount[j];
		}
		postBuyCount = G.numBuys;

		if (NOISY_TEST)
		{
			printf("Number of Buys available after playCouncil_Room(): %d\n", postBuyCount);
			for (j = 0; j < numPlayer; j++)
			{
				printf("Cards in hand for player %d after playCouncil_Room(): %d\n", j, postHandCount[j]);
			}
		}

		// Check if tests were passed...
		for (j = 0; j < numPlayer; j++)
		{
			if (j == p) // test for the player who played the card
			{
				if (preHandCount[j] + 4 == postHandCount[j])
				{
					// test passed
				}
				else
				{
					// test failed
					testPassed = 0;
				}
			}
			else // test for the other players
			{
				if (preHandCount[j] + 1 == postHandCount[j])
				{
					// test passed
				}
				else
				{
					// test failed
					testPassed = 0;
				}
			}
		}

		if (preBuyCount + 1 == postBuyCount)
		{
			// test passed
		}
		else
		{
			// test failed
			testPassed = 0;
		}

		if (NOISY_TEST)
		{
			printf("\n\n");
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

