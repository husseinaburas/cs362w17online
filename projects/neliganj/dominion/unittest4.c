#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int i, p, r;
	int cur_player = 0;
	int seed = 2000;
	int numPlayer = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine
			, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int testPassed = 1;

	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

	printf ("\nTESTING endTurn():\n");
	for (p = 0; p < numPlayer; p++)
	{
		#if (NOISY_TEST == 1)
			printf("end turn for player %d\n", p);
		#endif

		endTurn(&G);

		if (p < 3) {
			if (G.whoseTurn == cur_player + 1)
			{
				// pass
			}
			else
			{
				// fail
				testPassed = 0;
			}
		}
		else
		{
			if (G.whoseTurn == 0)
			{
				// pass
			}
			else
			{
				// fail
				testPassed = 0;
			}
		}

		cur_player++;
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
