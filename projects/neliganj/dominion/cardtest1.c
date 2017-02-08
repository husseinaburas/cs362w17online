#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int i;
	int seed = 3000;
	int numPlayer = 2;
	int maxSmithys = 3;
	int p, r, handCount;
	int smithyCount;
	int k[10] = {adventurer, council_room, feast, gardens, mine
			, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int maxHandCount = 5;
	int testPassed = 1;

	// arrays of all coppers, silvers, golds, and adventurers
	int coppers[MAX_HAND];
	int smithys[MAX_HAND];

	for (i = 0; i < MAX_HAND; i++)
	{
		coppers[i] = copper;
		smithys[i] = smithy;
	}

	printf ("\nTESTING playSmithy():\n");
	for (p = 0; p < numPlayer; p++)
	{
		for (handCount = maxSmithys; handCount <= maxHandCount; handCount++)
		{
			for (smithyCount = 1; smithyCount <= maxSmithys; smithyCount++)
			{
				#if (NOISY_TEST == 1)
					printf("Test player %d with %d total cards and %d Smithy card(s).\n", p, handCount, smithyCount);
				#endif

				memset(&G, 23, sizeof(struct gameState));   // clear the game state
				r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
				G.handCount[p] = handCount;                 // set the number of cards on hand

				if (p == 1)
				{
					G.whoseTurn++;
				}

				memcpy(G.hand[p], smithys, sizeof(int) * smithyCount); // set smithy cards
				memcpy(G.hand[p + smithyCount], coppers, sizeof(int) * (handCount - smithyCount)); // set remaining cards to coppers

				if (smithyCount == 1)
				{
					playSmithy(&G, 0);  // play Smithy from 0 hand position
				}
				else
				{
					playSmithy(&G, 1);  // play Smithy from 1 hand position
				}

				int total_in_hand = 0;
				int smithys_in_hand = 0;
				for (i = 0; i <= G.handCount[p]; i++)
				{
					total_in_hand++;

					if (G.hand[p][i] == smithy)
					{
						smithys_in_hand++;
					}
				}

				#if (NOISY_TEST == 1)
					printf("Cards in hand after playSmithy() = %d, expected = %d\n", total_in_hand, handCount + 3);
				#endif

				#if (NOISY_TEST == 1)
					printf("Smithys in hand = %d, expected = %d\n", smithys_in_hand, smithyCount - 1);
				#endif

				if (total_in_hand == handCount + 3 && smithys_in_hand == smithyCount - 1)
				{
					// pass
				}
				else
				{
					// fail
					testPassed = 0;	
				}
			}
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
