/* -----------------------------------------------------------------------
 * Unit tests for playBaron()
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "testUtilities.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
int main() {
    //int i;
    int seed = 1000;
    int numPlayer = 2;
    //int maxBonus = 10;
    int p, i;
    //int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int numFailingTests = 0;
    int numPassedTests = 0;

    printf ("\n--------TESTING playBaron()--------\n");
    for (p = 0; p < 1; p++) {
        // Initialize the game
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.whoseTurn = p;

        // Play baron with choice set to 0 so that no estate cards are discarded
        int numBuysBefore = G.numBuys;
        int numEstatesInSupplyBefore = G.supplyCount[estate];
        int numberOfEstatesBefore = 0;
        for(i = 0; i < MAX_HAND; i++) {
            if(G.hand[p][i] == estate) {
                numberOfEstatesBefore++;
            }   
        }

        int retVal = playBaron(p, &G, 0);
        printf("Return value from playBaron should be 0");
        checkAssertion(0, retVal, &numFailingTests, &numPassedTests);

        printf("The number of buys should have increased by 1");
        checkAssertion(G.numBuys, numBuysBefore +1, &numFailingTests, &numPassedTests);

        printf("With the option set to false, the number of estates in the supply should decrease by 1");
        checkAssertion(numEstatesInSupplyBefore - 1, G.supplyCount[estate], &numFailingTests, &numPassedTests);

        int numberOfEstatesAfter = 0;
        for(i = 0; i < MAX_HAND; i++) {
            if(G.hand[p][i] == estate) {
                numberOfEstatesAfter++;
            }   
        }
        printf("With the option set to false, the number of estates in the player's hand should increase by 1");
        checkAssertion(numberOfEstatesBefore + 1, numberOfEstatesAfter, &numFailingTests, &numPassedTests);

        printf("With the option set to true, the player should gain 4 coins");
        int startingCoins = G.coins;
        playBaron(p, &G, 2);
        checkAssertion(startingCoins + 4, G.coins, &numFailingTests, &numPassedTests);
    }
    printf("\nSummary: passed tests: %d\n", numPassedTests);
    printf("Summary: failed tests: %d\n\n", numFailingTests);
    return 0;
}
