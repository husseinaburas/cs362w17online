/* -----------------------------------------------------------------------
 * Random Automated tests for playBaron()
 *
 * randomtestcard2: randomcardtest2.c dominion.o rngs.o
 *      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
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
    //int i;
    //int seed = 1000;
    srand(time(NULL));
    int seed = (rand() % 1000);
    
    //int maxBonus = 10;
    int p, i;
    //int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int numFailingTests = 0;
    int numPassedTests = 0;


    int numTimesToRunTests = 1000;
    int testTrial;

    printf ("\n--------TESTING playBaron()--------\n");


    for (testTrial = 0; testTrial < numTimesToRunTests; testTrial++) {
        printf("\n----Trial%d\n", testTrial);

        // Generate random settings
        // srand(time(NULL));
        // int seed = (rand() % 1000) + 1000;
        int numPlayer = rand() % 3 + 2; // randomly initialize a game with 2 - 4 players
        
        // Initialize the game
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game

        // Put a random number of estate cards in the supply
        G.supplyCount[estate] = rand() % 5;

        // Randomly decide where and how many estate card the player has
        for(p = 0; p < numPlayer; p++) {

            // Give the player a random number of cards in their hand
            G.handCount[p] = rand() % MAX_HAND + 1;

            // Give the player a random number of estate cards in random locations of their hand
            int numPlayerEstates = rand() % 3;
            int eachEstate = 0;
            for (eachEstate = 0; eachEstate < numPlayerEstates; eachEstate++) {
                int randomEstateLocation = rand() % G.handCount[p];
                G.hand[p][randomEstateLocation] = estate;
            }
        }
            
        for (p = 0; p < numPlayer; p++) {
            G.whoseTurn = p;
            int randomOptionChoice = rand() % 2;  // choose either 0 or 1

            

            // Count up estates and coins before play
            int numBuysBefore = G.numBuys;
            int numEstatesInSupplyBefore = supplyCount(estate, &G);//G.supplyCount[estate];
            int startingCoins = G.coins;
            int playerDeckCountBefore = G.deckCount[p];
            int playerDiscardCountBefore = G.discardCount[p];
            //int numberOfPlayedCardsBefore = G.playedCardCount;

            int numberOfEstatesInHandBefore = 0;
            for(i = 0; i < G.handCount[p]; i++) {
                if(G.hand[p][i] == estate) {
                    numberOfEstatesInHandBefore++;
                }   
            }

            int numberOfEstatesInDiscardBefore = 0;
            for(i = 0; i < G.discardCount[p]; i++) {
                if(G.discard[p][i] == estate) {
                    numberOfEstatesInDiscardBefore++;
                }   
            }

            // Play baron with random choice selected
            int retVal = playBaron(p, &G, randomOptionChoice);
            
            // Count up the number of estates after playing the baron
            //int numEstatesInSupplyAfter = supplyCount(estate, &G);//G.supplyCount[estate];
            int playerDeckCountAfter = G.deckCount[p];
            int playerDiscardCountAfter = G.discardCount[p];
            //int numberOfPlayedCardsAfter = G.playedCardCount;

            int numberOfEstatesInHandAfter = 0;
            for(i = 0; i < G.handCount[p]; i++) {
                if(G.hand[p][i] == estate) {
                    numberOfEstatesInHandAfter++;
                }   
            }

            int numberOfEstatesInDiscardAfter = 0;
            for(i = 0; i < G.discardCount[p]; i++) {
                if(G.discard[p][i] == estate) {
                    numberOfEstatesInDiscardAfter++;
                }   
            }

            // printf("The number of estates in their hand BEFORE is... %d\n", numberOfEstatesBefore);
            // printf("The number of estates in their hand AFTER is... %d\n", numberOfEstatesAfter);
            // printf("\nThe number of estates in the supply hand BEFORE is... %d\n", numEstatesInSupplyBefore);
            // printf("The number of estates in the supply hand After is... %d\n", numEstatesInSupplyAfter);


            // Check return value
            printf("Return value from playBaron should be 0");
            checkAssertion(0, retVal, &numFailingTests, &numPassedTests);

            // Check number of buys
            printf("The number of buys should have increased by 1");
            checkAssertion(G.numBuys, numBuysBefore +1, &numFailingTests, &numPassedTests);

            //The number of cards in player's deck should not change
            printf("The number of cards in the player's deck should not change");
            checkAssertion(playerDeckCountBefore, playerDeckCountAfter, &numFailingTests, &numPassedTests);

            
            // Note: The following two tests were removed because the functions that play cards do not handle
            // these actions.
            
            // Check the number of played cards
            // printf("The number of played cards should increase by one");
            // checkAssertion(numberOfPlayedCardsBefore + 1, numberOfPlayedCardsAfter, &numFailingTests, &numPassedTests);

            //TODO - Check that the baron is played


            // The player can only gain an estate if their choice was 0, and
            // there are some in the supply
            if (randomOptionChoice == 0 && supplyCount(estate, &G) > 0) {
                //expectedNumberOfEstatesAfter = numberOfEstatesBefore + 1;

                // If option was false, number of estates is supply should decrease
                printf("With the option set to false, the number of estates in the supply should decrease by 1");
                checkAssertion(numEstatesInSupplyBefore - 1, G.supplyCount[estate], &numFailingTests, &numPassedTests);    
            
                printf("With the option set to false, the number of estates in the player's hand should increase by 1,\n but only if there are estates in the supply.");
                checkAssertion(numberOfEstatesInHandBefore + 1, numberOfEstatesInHandAfter, &numFailingTests, &numPassedTests);

                //The number of coins should stay the same
                printf("With the option set to false, the player should NOT gain 4 coins");
                checkAssertion(startingCoins, G.coins, &numFailingTests, &numPassedTests);
            
            // If you choose to discard an estate, you must have at lease one in your hand
            } else if (randomOptionChoice > 0 && numberOfEstatesInHandBefore > 0) {
                printf("With the option set to true, the player should gain 4 coins");
                checkAssertion(startingCoins + 4, G.coins, &numFailingTests, &numPassedTests);

                printf("With the option set to true, the player should have an additional card in their discard");
                checkAssertion(playerDiscardCountBefore + 1, playerDiscardCountAfter, &numFailingTests, &numPassedTests);

                printf("With the option set to true, the number of estates in the player's hand should decrease by 1");
                checkAssertion(numberOfEstatesInHandBefore - 1, numberOfEstatesInHandAfter, &numFailingTests, &numPassedTests);

                //Todo - Player should have additional estate in discard pile
                printf("With the option set to true, the number of estates in the player's discard should increase by 1");
                checkAssertion(numberOfEstatesInDiscardBefore + 1, numberOfEstatesInDiscardAfter, &numFailingTests, &numPassedTests);

            }
        }
    }
    printf("-------------------------------------------------\n");
    printf("\nSummary: passed tests: %d\n", numPassedTests);
    printf("Summary: failed tests: %d\n\n", numFailingTests);
    printf("-------------------------------------------------\n");
    return 0;
}
