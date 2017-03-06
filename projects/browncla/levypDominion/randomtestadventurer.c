/* -----------------------------------------------------------------------
 * Random Unit tests for playAdventurer() function
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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
    srand(time(NULL));
    int seed = (rand() % 1000) + 1000;
    int p, i;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int numFailingTests = 0;
    int numPassedTests = 0;

    int numTimesToRunTests = 1000;
    int testTrial;
    

    printf ("\n--------TESTING Adventurer Card--------\n");
    
    for(testTrial = 0; testTrial < numTimesToRunTests; testTrial++) {
        // Initialize the game
        int numPlayer = rand() % 3 + 2; // randomly initialize a game with 2 - 4 players
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game
        
        // Test adventurer card for each player
        for (p = 0; p < numPlayer; p++) {
            printf("--Player %d\n", p);
            G.whoseTurn = p;

            // G.deckCount[p] = floor(Random() * MAX_DECK);
            // G.discardCount[p] = floor(Random() * MAX_DECK);
            
            // Give the player a random number of cards in their hand
            G.handCount[p] = rand() % MAX_HAND;
            
            int numberOfTreasuresBefore = 0;
            for(i = 0; i < G.handCount[p]; i++) {
                if(G.hand[p][i] == copper || G.hand[p][i] == silver || G.hand[p][i] == gold) {
                    numberOfTreasuresBefore++;
                }   
            }

            // int numberOfCardsInDeckBefore = G.deckCount[p];
            // int numberOfDiscardedCardsBefore = G.discardCount[p];
            int numberInHandBefore = G.handCount[p];
            int playerDeckCountBefore = G.deckCount[p];
            int playerDiscardCountBefore = G.discardCount[p];

            // Play Adventurer Card    
            int retVal = playAdventurer(p, &G);
            int numberOfTreasuresAfter = 0;

            int numberInHandAfter = G.handCount[p];
            int playerDeckCountAfter = G.deckCount[p];
            int playerDiscardCountAfter = G.discardCount[p];

            // printf("numberInHandBefore%d\n", numberInHandBefore);
            // printf("numberInHandAfter%d\n", numberInHandAfter);
            // printf("playerDeckCountBefore%d\n", playerDeckCountBefore);
            // printf("playerDeckCountAfter%d\n", playerDeckCountAfter);
            // printf("playerDiscardCountBefore%d\n", playerDiscardCountBefore);
            // printf("playerDiscardCountAfter%d\n", playerDiscardCountAfter);

            //printf("Checking hand after playing adventurer...\n");
            for(i = 0; i < G.handCount[p]; i++) {
                if(G.hand[p][i] == copper || G.hand[p][i] == silver || G.hand[p][i] == gold) {
                    numberOfTreasuresAfter++;
                }   
            }

            int testValue = 0;
        
            
            testValue = checkAssertion(numberOfTreasuresBefore + 2, numberOfTreasuresAfter, &numFailingTests, &numPassedTests);
            if (testValue == 0) {
                printf("playAdventurer should increase the number of treasure cards by 2 -- FAILED");

                printf("\nnumberInHandBefore%d\n", numberInHandBefore);
                printf("numberInHandAfter%d\n", numberInHandAfter);
                printf("playerDeckCountBefore%d\n", playerDeckCountBefore);
                printf("playerDeckCountAfter%d\n", playerDeckCountAfter);
                printf("playerDiscardCountBefore%d\n", playerDiscardCountBefore);
                printf("playerDiscardCountAfter%d\n", playerDiscardCountAfter);
            }
            else {
                printf("playAdventurer should increase the number of treasure cards by 2 -- PASSED");   
            }

            
            testValue = checkAssertion(numberInHandBefore + 2, numberInHandAfter, &numFailingTests, &numPassedTests);
            if (testValue == 0){
                printf("playAdventurer should increase the handcount by 2 -- FAILED");

                printf("numberInHandBefore%d\n", numberInHandBefore);
                printf("numberInHandAfter%d\n", numberInHandAfter);
                printf("playerDeckCountBefore%d\n", playerDeckCountBefore);
                printf("playerDeckCountAfter%d\n", playerDeckCountAfter);
                printf("playerDiscardCountBefore%d\n", playerDiscardCountBefore);
                printf("playerDiscardCountAfter%d\n", playerDiscardCountAfter);    
            } 
            else {
                printf("playAdventurer should increase the handcount by 2 -- PASSED");    
            }

            
            int deckDecreased = 0;
            if(playerDeckCountAfter < playerDeckCountBefore) {
                deckDecreased = 1;
            }
            testValue = checkAssertion(1, deckDecreased, &numFailingTests, &numPassedTests);
            if (testValue == 0) {
                printf("playAdventurer should decrease the player's deck count -- FAILED");

                printf("numberInHandBefore%d\n", numberInHandBefore);
                printf("numberInHandAfter%d\n", numberInHandAfter);
                printf("playerDeckCountBefore%d\n", playerDeckCountBefore);
                printf("playerDeckCountAfter%d\n", playerDeckCountAfter);
                printf("playerDiscardCountBefore%d\n", playerDiscardCountBefore);
                printf("playerDiscardCountAfter%d\n", playerDiscardCountAfter);
            }
            else {
                printf("playAdventurer should decrease the player's deck count -- PASSED");
            }

            
            testValue = checkAssertion(0, retVal, &numFailingTests, &numPassedTests);
            if (testValue == 0) {
                printf("playAdventurer() should return 0 -- FAILED");

                printf("numberInHandBefore%d\n", numberInHandBefore);
                printf("numberInHandAfter%d\n", numberInHandAfter);
                printf("playerDeckCountBefore%d\n", playerDeckCountBefore);
                printf("playerDeckCountAfter%d\n", playerDeckCountAfter);
                printf("playerDiscardCountBefore%d\n", playerDiscardCountBefore);
                printf("playerDiscardCountAfter%d\n", playerDiscardCountAfter);
            }
            else {
                printf("playAdventurer() should return 0 -- PASSED");
            }
        }    
    }

    
    printf("\nSummary: passed tests: %d\n", numPassedTests);
    printf("Summary: failed tests: %d\n\n", numFailingTests);
    return 0;
}

