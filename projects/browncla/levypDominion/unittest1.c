/* -----------------------------------------------------------------------
 * Unit tests for playCard() function
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    // arrays of all coppers or adventurers
    int coppers[MAX_HAND];
    int adventurers[MAX_HAND];
    int numFailingTests = 0;
    int numPassedTests = 0;
    handCount = 5;
    for (i = 0; i < handCount; i++)
    {
        adventurers[i] = adventurer;
    }

    printf ("\n--------TESTING playCard()--------\n");
    for (p = 0; p < numPlayer; p++) {
        // Initialize the game
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.handCount[p] = handCount;                 // set the number of cards on hand

        // Check that playcard results in the number of actions to be reduced
        memcpy(G.hand[0], adventurers, sizeof(int) * handCount); // set all the cards to adventurers
        G.phase = 0;
        G.numActions = 1;
        playCard(0, 0, 0, 0, &G);
        printf("Playcard should result in the number of actions begin reduced to 0");
        checkAssertion(0, G.numActions, &numFailingTests, &numPassedTests);
	

        // Check that playcard does not execute when a non-action card is played
        handCount = 5;
        memcpy(G.hand[0], coppers, sizeof(int) * handCount); // set all the cards to copper
        G.phase = 0;
        G.numActions = 1;
        playCard(0, 0, 0, 0, &G);
        printf("Attempting to play a copper (non-action card) should cause playCard() to exit early and return -1");
        checkAssertion(-1, playCard(0, 0, 0, 0, &G), &numFailingTests, &numPassedTests);

        // Check that playcard does not execute when the player is out of actions
        handCount = 5;
        memcpy(G.hand[0], coppers, sizeof(int) * handCount); // set all the cards to copper
        G.phase = 0;
        G.numActions = 0;
        playCard(0, 0, 0, 0, &G);
        printf("The current player has no more actions left, should cause playCard() to exit early and return -1");
        checkAssertion(-1, playCard(0, 0, 0, 0, &G), &numFailingTests, &numPassedTests);

        // Check that the playCard function does not execute when it is called in the buy phase
        G.phase = 1;
        printf("Game phase is %d, playCard() should exit early and return -1", G.phase);
        checkAssertion(-1, playCard(0, 0, 0, 0, &G), &numFailingTests, &numPassedTests);

        // Check that the playCard function does not execute when it is called in the cleanup phase
        G.phase = 2;
        printf("Game phase is %d, playCard() should exit early and return -1", G.phase);
        checkAssertion(-1, playCard(0, 0, 0, 0, &G), &numFailingTests, &numPassedTests);        
    }
    printf("\nSummary: passed tests: %d\n", numPassedTests);
    printf("Summary: failed tests: %d\n\n", numFailingTests);
    return 0;
}

