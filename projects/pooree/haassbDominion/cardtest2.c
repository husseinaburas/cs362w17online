/* -----------------------------------------------------------------------
 *
 *          cardtest2.c
 *          Unit Testing of Sea Hag Card 
 * 
 *      
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

 #define TESTCARD "sea_hag"

 void failedTest() {
    printf("**** FAILED TEST ****\n");
 }

int main() {
    int i;


    // Values for setting up a game
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    
    struct gameState G, testG;

    // Initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);


    printf("---------------------- Testing card: %s ----------------------\n", TESTCARD);

    printf("-----------Test 1: Test that current player's hand is unchanged other than discarding played card ----------\n");
    int discarded = 1;
    // copy the game state to a test case 
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(sea_hag, choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);
    if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] - discarded)
        failedTest();

    printf("-----------Test 2: Test that the other players' discarded a card----------\n");
    printf("card = %d, expected = %d\n", testG.discardCount[thisPlayer + 1], G.discardCount[thisPlayer + 1] + 1);
    if(testG.discardCount[thisPlayer + 1] != G.discardCount[thisPlayer + 1] + 1)
        failedTest();   

    printf("-----------Test 3: Test that the other player's hand has a curse card on top of their deck ----------\n");
    printf("card = %d, expected = %d\n", testG.deck[thisPlayer + 1][testG.deckCount[thisPlayer+1]--], curse);
    if(testG.deck[thisPlayer + 1][testG.deckCount[thisPlayer+1]--] != 0)
        failedTest();

    printf("-----------Test 4: Test that the other player's deck count remains unchanged----------\n");
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer + 1], G.deckCount[thisPlayer + 1]);
    if(testG.deckCount[thisPlayer + 1] != G.deckCount[thisPlayer + 1])
        failedTest();

    //This test became especially important after seeing strange behavior in the deck count for the player that isn't the current player
    printf("-----------Test 5: Test that the other player's HAND has same number of cards as initially----------\n");
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer + 1], G.handCount[thisPlayer + 1]);
    if(testG.handCount[thisPlayer + 1] != G.handCount[thisPlayer + 1])
        failedTest();

    printf("-----------Test 6: Check there there are fewer curse cards in supply -------\n");
    printf("curse card count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0] - 1);
        if(testG.supplyCount[0] != G.supplyCount[0] -1) 
            failedTest();
  

    printf("-----------Test 7: there is no change to the other supply card piles-------\n");
    for (i=1; i<sizeof(testG.supplyCount)/sizeof(int); i++) {
        printf("supply card count = %d, expected = %d\n", testG.supplyCount[i], G.supplyCount[i]);
        if(testG.supplyCount[i] != G.supplyCount[i]) 
            failedTest();       
    }


    return 0;
}
