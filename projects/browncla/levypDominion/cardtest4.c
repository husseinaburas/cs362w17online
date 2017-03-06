/* -----------------------------------------------------------------------
 * Unit tests for playMine()
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
    int handCount;
    //int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int numFailingTests = 0;
    int numPassedTests = 0;
    int adventurers[MAX_HAND];
    int coppers[MAX_HAND];
    //int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        adventurers[i] = adventurer;
        coppers[i] = copper;
        //golds[i] = gold;
    }

    printf ("\n--------TESTING playMine()--------\n");
    for (p = 0; p < 1; p++) {
        // Initialize the game
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.whoseTurn = p;

        // attempt to trash a non-treasure card
        handCount = 5;
        memcpy(G.hand[0], adventurers, sizeof(int) * handCount); // set all the cards to adventurers
        int retVal = playMine(p, &G, 0, 0, 0);
        printf("Attempting to trash a non-treasure card should not be possible.  The return value should be -1");
        checkAssertion(-1, retVal, &numFailingTests, &numPassedTests);

        // attempt to trash a copper and take gold
        memcpy(G.hand[0], coppers, sizeof(int) * handCount); // set all the cards to coppers
        retVal = playMine(p, &G, 0, gold, 0);
        printf("Attempting to trash a copper and take a gold is not possible.  The return value should be -1");
        checkAssertion(-1, retVal, &numFailingTests, &numPassedTests);

        // Play a card that is not in the deck
        retVal = playMine(p, &G, 0, curse -1, 0);
        printf("Attempting to take a card that is not in the deck (less than curse).  The return value should be -1");
        checkAssertion(-1, retVal, &numFailingTests, &numPassedTests);

        // Play a card that is not in the deck
        retVal = playMine(p, &G, 0, treasure_map + 1, 0);
        printf("Attempting to take a card that is not in the deck (greater than treasure_map).  The return value should be -1");
        checkAssertion(-1, retVal, &numFailingTests, &numPassedTests);

        // Make a valid play

        memcpy(G.hand[0], coppers, sizeof(int) * handCount); // set all the cards to coppers
        //printf("First card before...%d\n", G.hand[0][0]);
        int numberOfCoppersBefore = 0;
        for(i = 0; i < MAX_HAND; i++) {
            if(G.hand[p][i] == copper) {
                numberOfCoppersBefore++;
            }   
        }

        int numberOfSilversBefore = 0;
        for(i = 0; i < MAX_HAND; i++) {
            if(G.hand[p][i] == silver) {
                numberOfSilversBefore++;
            }   
        }

        retVal = playMine(p, &G, 0, silver, 0);

        int numberOfCoppersAfter = 0;
        for(i = 0; i < MAX_HAND; i++) {
            if(G.hand[p][i] == copper) {
                numberOfCoppersAfter++;
            }   
        }

        int numberOfSilversAfter = 0;
        for(i = 0; i < MAX_HAND; i++) {
            if(G.hand[p][i] == silver) {
                numberOfSilversAfter++;
            }   
        }
        printf("Trash a copper and gain a silver. There should be one less copper");
        checkAssertion(numberOfCoppersBefore - 1, numberOfCoppersAfter, &numFailingTests, &numPassedTests);

        printf("Trash a copper and gain a silver. There should be one more silver");
        checkAssertion(numberOfSilversBefore + 1, numberOfSilversAfter, &numFailingTests, &numPassedTests);

    }
    printf("\nSummary: passed tests: %d\n", numPassedTests);
    printf("Summary: failed tests: %d\n\n", numFailingTests);
    return 0;
}
