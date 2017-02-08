/* -----------------------------------------------------------------------
 *
 *          cardtest1.c
 *          Unit Testing of Smithy Card 
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

 #define TESTCARD "smithy"

 void failedTest() {
    printf("!!!! FAILED TEST !!!!\n");
 }


int main() {
    int i;
    int newCards = 3;           // Num cards to be drawn when smithy called
    int discarded = 1;          // Discard smithy card when it's played

    // Default values for calling cardEffect
    int handpos = 0;

    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    
    struct gameState G, testG;

    // Initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);


    printf("---------------------- Testing card: %s ----------------------\n", TESTCARD);

    printf("-----------Test 1: Test current player receives 3 cards-----------\n");

    // copy the game state to a test case 
    memcpy(&testG, &G, sizeof(struct gameState));
    playSmithy(handpos, thisPlayer, &testG);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded)
        failedTest();
    
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
    if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - newCards)
        failedTest();

    printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
    if(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer] + discarded)
        failedTest();

    printf("-----------Check that other player's hands are not effected-------\n");
    
    printf("other player's hand count = %d, expected %d\n", testG.handCount[thisPlayer + 1], G.handCount[thisPlayer + 1]);
    if(testG.handCount[thisPlayer + 1] != G.handCount[thisPlayer + 1])
        failedTest();

    printf("other player's deck count = %d, expected = %d\n", testG.deckCount[thisPlayer + 1], G.deckCount[thisPlayer + 1]);
    if(testG.deckCount[thisPlayer + 1] != G.deckCount[thisPlayer + 1])
        failedTest();

    printf("-----------Check there is no change to the supply card piles-------\n");

    for (i=0; i<sizeof(testG.supplyCount)/sizeof(int); i++) {
        printf("supply card count = %d, expected = %d\n", testG.supplyCount[i], G.supplyCount[i]);
        if(testG.supplyCount[i] != G.supplyCount[i]) 
            failedTest();
            
    }

    printf("------------ Testing complete for: %s -----------------------\n", TESTCARD);

    return 0;
}
