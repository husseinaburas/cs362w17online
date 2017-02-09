#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int i, p, r;
	int total_copper_count = 0;
	int total_gold_count = 0;
	int seed = 4000;
	int numPlayer = 4;
	int copper_card = 4;
	int gold_card = 6;
	int coppers[MAX_HAND];
	int golds[MAX_HAND];
	int testPassed = 1;
	for (i = 0; i < MAX_HAND; i++)
	{
		coppers[i] = copper;
		golds[i] = gold;
	}
	int k[10] = {adventurer, council_room, feast, gardens, mine
			, remodel, smithy, village, baron, great_hall};
	struct gameState G;

	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	int expected_copper_count = 28;  // expected count of all cards after initialing a 4 player game, minus 10 for player 3 who has golds
	int expected_gold_count = 10;

	printf ("\nTESTING fullDeckCount():\n");
	for (p = 0; p < numPlayer; p++)
	{
		if (p == 3)
		{
			memcpy(G.deck[p], golds, sizeof(int) * G.deckCount[p]); // set all the cards in deck to gold
			memcpy(G.hand[p], golds, sizeof(int) * G.deckCount[p]); // set all the cards in hand to gold
		}
		else
		{
			memcpy(G.deck[p], coppers, sizeof(int) * G.deckCount[p]); // set all the cards in deck to copper
			memcpy(G.hand[p], coppers, sizeof(int) * G.deckCount[p]); // set all the cards in hand to copper
		}


		// discard a card with and without trash flag
		discardCard(0, p, &G, 0);
		discardCard(0, p, &G, 1);

		int player_copper_count = fullDeckCount(p, copper_card, &G);
		int player_gold_count = fullDeckCount(p, gold_card, &G);

		#if (NOISY_TEST == 1)
			printf("Player %d copper count: %d\n", p, player_copper_count);
			printf("Player %d gold count: %d\n", p, player_gold_count);
		#endif

		total_copper_count += player_copper_count;
		total_gold_count += player_gold_count;
	}

	#if (NOISY_TEST == 1)
		printf("\nTotal copper count: %d\nExpected copper count: %d\n", total_copper_count, expected_copper_count);
	#endif

	if (expected_copper_count == total_copper_count)
	{
		// pass
	}
	else
	{
		// fail
		testPassed = 0;
	}

	#if (NOISY_TEST == 1)
		printf("Total gold count: %d\nExpected gold count: %d\n", total_gold_count, expected_gold_count);
	#endif

	if (expected_gold_count == total_gold_count)
	{
		// pass
	}
	else
	{
		// fail
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
