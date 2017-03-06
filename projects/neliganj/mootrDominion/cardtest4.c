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
    int numPlayer = 4;
    int p, r, handCount, handPos, temp_num_buys, temp_hand_count_0, temp_hand_count_1, temp_hand_count_2, temp_hand_count_3;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

	printf ("\nTESTING playCouncil_Room():\n");

	for (handCount = 1; handCount <= maxHandCount; handCount++)
	{
		for (handPos = 0; handPos < handCount; handPos++)
		{
			#if (NOISY_TEST == 1)
				printf("Test player 0 with %d cards in hand and Council Room card in hand pos %d.\n", handCount, handPos);
				for (i = 1; i < numPlayer; i++)
				{
					printf("Player %d: %d cards\n", i, G.handCount[i]);
				}
				printf("\n");
			#endif

			memset(&G, 23, sizeof(struct gameState));   // clear the game state
			r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
			for (i = 0; i < numPlayer; i++)
			{
				G.handCount[i] = handCount;
			}

			temp_hand_count_0 = G.handCount[0];
			temp_hand_count_1 = G.handCount[1];
			temp_hand_count_2 = G.handCount[2];
			temp_hand_count_3 = G.handCount[3];

			G.numBuys = handPos; // vary number of buy actions available

			playCouncil_Room(&G, handPos);

			#if (NOISY_TEST == 1)
				printf("Expected num buy actions: %d; actual: %d\n", handPos + 1, G.numBuys);
				printf("Expected player 0 hand count: %d; actual: %d\n", temp_hand_count_0 + 3, G.handCount[0]);
				printf("Expected player 1 hand count: %d; actual: %d\n", temp_hand_count_1 + 1, G.handCount[1]);
				printf("Expected player 2 hand count: %d; actual: %d\n", temp_hand_count_2 + 1, G.handCount[2]);
				printf("Expected player 3 hand count: %d; actual: %d\n\n", temp_hand_count_3 + 1, G.handCount[3]);
			#endif

			if ( ! ( (temp_hand_count_0 + 3 == G.handCount[0]) && (temp_hand_count_1 + 1 == G.handCount[1]) && 
			         (temp_hand_count_2 + 1 == G.handCount[2]) && (temp_hand_count_3 + 1 == G.handCount[3]) ) ) 
			{
				testPassed = 0;
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
