/* -----------------------------------------------------------------------
 * Unit tests for playAdventurer() function
 *
 * cardtest1: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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
    int seed = 1000;
    int numPlayer = 2;
    int p, i;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int numFailingTests = 0;
    int numPassedTests = 0;
    

    printf ("\n--------TESTING Adventurer Card--------\n");
    for (p = 0; p < numPlayer; p++) {
        G.whoseTurn = p;
        // Initialize the game
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game
        
        int numberOfTreasuresBefore = 0;
        for(i = 0; i < MAX_HAND; i++) {
            if(G.hand[p][i] == copper || G.hand[p][i] == silver || G.hand[p][i] == gold) {
                numberOfTreasuresBefore++;
            }   
        }
        int retVal = playAdventurer(p, &G);
        int numberOfTreasuresAfter = 0;

        //printf("Checking hand after playing adventurer...\n");
        for(i = 0; i < MAX_HAND; i++) {
            if(G.hand[p][i] == copper || G.hand[p][i] == silver || G.hand[p][i] == gold) {
                numberOfTreasuresAfter++;
            }   
        }
    
        printf("playAdventurer should increase the number of treasure cards by 2");
        checkAssertion(2, numberOfTreasuresAfter - numberOfTreasuresBefore, &numFailingTests, &numPassedTests);

        printf("playAdventurer() should return 0");
        checkAssertion(0, retVal, &numFailingTests, &numPassedTests);
    }
    printf("\nSummary: passed tests: %d\n", numPassedTests);
    printf("Summary: failed tests: %d\n\n", numFailingTests);
    return 0;
}

