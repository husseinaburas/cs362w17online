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
	int seed = time(NULL);
	int numPlayer = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine
			, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int testPassed = 1;

	printf ("\nTESTING shuffle():\n");
	for (p = 0; p < numPlayer; p++)
	{

		#if (NOISY_TEST == 1)
			printf("Test player %d deck shuffle\n", p);
		#endif

		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

		int temp_deck[MAX_HAND];
		memcpy(temp_deck, G.deck[p], sizeof(int) * G.deckCount[p]);


		r = shuffle(p, &G);
		int same_count = 0;

		for (i = 0; i < G.deckCount[p]; i++)
		{
			if (temp_deck[i] == G.deck[p][i]) {
				same_count++;
			}
		}
		double percent_same = ((float)same_count / (float)G.deckCount[p]) * 100;
		#if (NOISY_TEST == 1)
			printf("%d of %d cards in same position after shuffle: %g%%\n", same_count, G.deckCount[p], percent_same);
		#endif

		if (percent_same < 99)
		{
			// pass
		}
		else
		{
			// fail
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
