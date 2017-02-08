/* -----------------------------------------------------------------------
 * Unit tests for isGameOver() function
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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

    printf ("\n--------TESTING isGameOver()--------\n");
    for (p = 0; p < numPlayer; p++) {
        // Initialize the game
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game

        // G.supplyCount[province] = 10;
        printf("A new game has been intitialized...isGameOver() should return 0");
        checkAssertion(0, isGameOver(&G), &numFailingTests, &numPassedTests);

        G.supplyCount[province] = 0;
        printf("No more provinces are available in the supply...isGameOver() should return 1");
        checkAssertion(1, isGameOver(&G), &numFailingTests, &numPassedTests);

        G.supplyCount[province] = 10;
        printf("10 Provinces have been added...isGameOver() should return 0");
        checkAssertion(0, isGameOver(&G), &numFailingTests, &numPassedTests);

        G.supplyCount[0] = 0;
        printf("One supply piles is empty...isGameOver() should return 0");
        checkAssertion(0, isGameOver(&G), &numFailingTests, &numPassedTests);

        G.supplyCount[1] = 0;
        printf("Two supply piles are empty...isGameOver() should return 0");
        checkAssertion(0, isGameOver(&G), &numFailingTests, &numPassedTests);

        G.supplyCount[2] = 0;
        printf("Three supply piles are empty...isGameOver() should return 1");
        checkAssertion(1, isGameOver(&G), &numFailingTests, &numPassedTests);    
    }
    printf("\nSummary: passed tests: %d\n", numPassedTests);
    printf("Summary: failed tests: %d\n\n", numFailingTests);
    return 0;
}
