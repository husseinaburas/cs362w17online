#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    int testPassed = 1;

    // arrays of all coppers, silvers, golds, and adventurers
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int adventurers[MAX_HAND];

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
        adventurers[i] = adventurer;
    }

    printf ("TESTING updateCoins():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
                #if (NOISY_TEST == 1)
                    printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
				#endif

                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand

                // all coppers test
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);
                #if (NOISY_TEST == 1)
                    printf("Coppers: G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
				#endif

				// check if the number of coins is correct
                if (G.coins == handCount * 1 + bonus)
				{
					// pass
				}
				else
				{
                    testPassed = 0;
				}

                // all silvers test
                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(p, &G, bonus);
                #if (NOISY_TEST == 1)
                    printf("Silvers: G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
                #endif

				// check if the number of coins is correct
				if (G.coins == handCount * 2 + bonus)
				{
                    // pass
				}
				else
				{
					// fail
                    testPassed = 0;
				}

                // all golds test
                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(p, &G, bonus);
                #if (NOISY_TEST == 1)
                    printf("Golds: G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
                #endif

				// check if the number of coins is correct
				if (G.coins == handCount * 3 + bonus)
				{
                    // pass
				}
				else
				{
                    // fail
                    testPassed = 0;
				}

                // no treasure coins test
                memcpy(G.hand[p], adventurers, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(p, &G, bonus);
                #if (NOISY_TEST == 1)
                    printf("None: G.coins = %d, expected = %d\n", G.coins, handCount * 0 + bonus);
                #endif

				// check if the number of coins is correct
				if (G.coins == handCount * 0 + bonus)
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
