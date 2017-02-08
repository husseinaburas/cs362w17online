/* -----------------------------------------------------------------------
 * Unit tests for endTurn() function
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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

    printf ("\n--------TESTING endTurn()--------\n");
    for (p = 0; p < numPlayer; p++) {
        // Initialize the game
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.whoseTurn = p;

        // Check return value
        printf("endTurn() should return 0");
        int returnValue = endTurn(&G);
        checkAssertion(0, returnValue, &numFailingTests, &numPassedTests);

        // Check that the current player has no cards left in their hand
        printf("After calling endTurn() the current player should have a handcount of 0");
        checkAssertion(0, G.handCount[p], &numFailingTests, &numPassedTests);

        if(p == 0) {
            // After endTurn() is called for player 0, it should advance to player 1
            printf("After calling endTurn() the player should advance");
            checkAssertion(1, G.whoseTurn, &numFailingTests, &numPassedTests);

        } else if (p == numPlayer - 1) {
            // After endTurn() is called for the last player, it should advance to player 0
            printf("After calling endTurn() on the last player, it should advance to the first player");
            checkAssertion(0, G.whoseTurn, &numFailingTests, &numPassedTests);
        }

        // Check that state is reset
        printf("After calling endTurn() the outpostPlayed should be 0");
        checkAssertion(0, G.outpostPlayed, &numFailingTests, &numPassedTests);

        printf("After calling endTurn() the phase should be 0");
        checkAssertion(0, G.phase, &numFailingTests, &numPassedTests);

        printf("After calling endTurn() the numActions should be 1");
        checkAssertion(1, G.numActions, &numFailingTests, &numPassedTests);

        printf("After calling endTurn() the coins should be reset to 3");
        checkAssertion(3, G.coins, &numFailingTests, &numPassedTests);

        printf("After calling endTurn() the numBuys should be 1");
        checkAssertion(1, G.numBuys, &numFailingTests, &numPassedTests);
        
        printf("After calling endTurn() the playedCardCount should be 0");
        checkAssertion(0, G.playedCardCount, &numFailingTests, &numPassedTests);    
    }
    printf("\nSummary: passed tests: %d\n", numPassedTests);
    printf("Summary: failed tests: %d\n\n", numFailingTests);
    return 0;
}
