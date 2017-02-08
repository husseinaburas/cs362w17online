/* -----------------------------------------------------------------------
 * Unit tests for buyCard() function
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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
    int p;
    //int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int numFailingTests = 0;
    int numPassedTests = 0;

    printf ("\n--------TESTING buyCard()--------\n");
    for (p = 0; p < numPlayer; p++) {
        // Initialize the game
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game

        // Buy a smithy
        int currentBuys = G.numBuys;
        int currentCoins = G.coins;
        buyCard(smithy, &G);

        // Check that the user has one less buy after a purchase
        printf("Number of buys for the player should be reduced by one after a purchase");
        checkAssertion(currentBuys - 1, G.numBuys, &numFailingTests, &numPassedTests);

        // Check that the user has less money after a purchase
        printf("Amount of coins for the player should be reduced after a purchase");
        checkAssertion(1, G.coins < currentCoins, &numFailingTests, &numPassedTests);

        // Check that the player can't buy a card if they don't have enough money
        G.numBuys = 1;
        G.coins = 3;
        printf("Attempting to purchase a card without enough money should not be possible");
        checkAssertion(-1, buyCard(smithy, &G), &numFailingTests, &numPassedTests);

        // Check that the player can't buy a card when they have no buys left
        G.numBuys = 0;
        G.coins = 5;
        printf("Attempting to purchase a card without any buys left should not be possible");
        checkAssertion(-1, buyCard(smithy, &G), &numFailingTests, &numPassedTests);

        // Players shouldn't be able to buy cards that are not in the supply
        G.numBuys = 1;
        G.coins = 5;
        printf("Attempting to purchase a card that is not in the supply should not be possible");
        checkAssertion(-1, buyCard(minion, &G), &numFailingTests, &numPassedTests);       
    }
    printf("\nSummary: passed tests: %d\n", numPassedTests);
    printf("Summary: failed tests: %d\n\n", numFailingTests);
    return 0;
}
