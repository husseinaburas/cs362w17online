/* -----------------------------------------------------------------------
 * Random Automated tests for playSmithy() function
 *
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "testUtilities.h"
#include <time.h>
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
int main() {
    // int seed = 1000;
    srand(time(NULL));
    int seed = (rand() % 1000) + 1000;
    //int numPlayer = 2;
    int p;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int numFailingTests = 0;
    int numPassedTests = 0;

    int numTimesToRunTests = 1000;
    int testTrial;
    

    printf ("\n--------TESTING smithy card--------\n");

    for(testTrial = 0; testTrial < numTimesToRunTests; testTrial++) {
        // Initialize the game
        int numPlayer = rand() % 3 + 2; // randomly initialize a game with 2 - 4 players
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game

        for (p = 0; p < numPlayer; p++) {
            G.whoseTurn = p;
            
            int numberOfHandCardsBeforeSmithy = G.handCount[p];
            int playerDeckCountBefore = G.deckCount[p];
            int playerDiscardCountBefore = G.discardCount[p];
            
            // Play Smithy from a random position
            int smithyPos = rand() % MAX_HAND;
            int retVal = playSmithy(p, &G, smithyPos);


            int numberOfHandCardsAfterSmithy = G.handCount[p];
            int playerDeckCountAfter = G.deckCount[p];
            int playerDiscardCountAfter = G.discardCount[p];

            // printf("numberOfHandCardsBeforeSmithy%d\n", numberOfHandCardsBeforeSmithy);
            // printf("numberOfHandCardsAfterSmithy%d\n", numberOfHandCardsAfterSmithy);
            // printf("playerDeckCountBefore%d\n", playerDeckCountBefore);
            // printf("playerDeckCountAfter%d\n", playerDeckCountAfter);
            // printf("playerDiscardCountBefore%d\n", playerDiscardCountBefore);
            // printf("playerDiscardCountAfter%d\n", playerDiscardCountAfter);
            
            printf("Playing smithy() should increase the current player's hand by 2 cards (3 are gained but smithy is moved to played cards)");
            checkAssertion(numberOfHandCardsBeforeSmithy + 2, G.handCount[p], &numFailingTests, &numPassedTests);

            printf("Playing smithy() should not change the player's discard count");
            checkAssertion(playerDiscardCountBefore, G.discardCount[p], &numFailingTests, &numPassedTests);

            printf("Playing smithy() should reduce the player's deck count by 3 cards");
            checkAssertion(playerDeckCountBefore - 3, G.deckCount[p], &numFailingTests, &numPassedTests);

            printf("Smithy() should return 0");
            checkAssertion(0, retVal, &numFailingTests, &numPassedTests);
        }
    }
    printf("\nSummary: passed tests: %d\n", numPassedTests);
    printf("Summary: failed tests: %d\n\n", numFailingTests);
    return 0;
}

