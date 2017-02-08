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
	int testPassed = 1;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount, handPos, temp_actions, temp_hand_count;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

	printf ("\nTESTING playVillage():\n");

    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
			for (handPos = 0; handPos < handCount; handPos++)
			{
				#if (NOISY_TEST == 1)
					printf("Test player %d with %d cards in hand and Village card in hand pos %d.\n", p, handCount, handPos);
				#endif

				memset(&G, 23, sizeof(struct gameState));   // clear the game state
				r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
				G.handCount[p] = handCount;

				G.numActions = handPos;  // set varying number of temp_actions

				temp_actions = G.numActions;
				temp_hand_count = G.handCount[p];
				playVillage(&G, handPos);

				#if (NOISY_TEST == 1)
					printf("Expected num actions: %d; actual: %d\n", temp_actions + 2, G.numActions);
					printf("Expected hand count: %d; actual: %d\n\n", temp_hand_count, G.handCount[p]);
				#endif

				if ( ! ( (temp_actions + 2 == G.numActions) && (temp_hand_count == G.handCount[p]) ) )
				{
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
