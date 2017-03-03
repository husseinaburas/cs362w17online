/* -----------------------------------------------------------------------
 * Unit tests for playSmithy() function
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
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
    int seed = 1000;
    int numPlayer = 2;
    int p;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int numFailingTests = 0;
    int numPassedTests = 0;
    

    printf ("\n--------TESTING smithy card--------\n");
    for (p = 0; p < numPlayer; p++) {
        G.whoseTurn = p;
        // Initialize the game
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game
        
        int numberOfCardsBeforeSmithy = G.handCount[p];
        printf("Playing smithy() should increase the current player's hand by 3 cards");
        int retVal = playSmithy(p, &G, 1);
        checkAssertion(numberOfCardsBeforeSmithy + 3, G.handCount[p], &numFailingTests, &numPassedTests);

        printf("Smithy() should return 0");
        checkAssertion(0, retVal, &numFailingTests, &numPassedTests);
    }
    printf("\nSummary: passed tests: %d\n", numPassedTests);
    printf("Summary: failed tests: %d\n\n", numFailingTests);
    return 0;
}

