/* -----------------------------------------------------------------------
 *
 *          cardtest3.c
 *          Unit testing of Village Card             
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

 #define TESTCARD "village"

 void failedTest() {
    printf("**** FAILED TEST ****\n");
 }

int main() {
    int i;


    // Default values for calling cardEffect
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    
    struct gameState G, testG;

    // Initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);


    printf("---------------------- Testing card: %s ----------------------\n", TESTCARD);

    printf("--Test 1: After player draws card and plays discarded card, hand count should remain unchanged--\n");

    // copy the game state to a test case 
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
    int newCards = 1;
    int newActions = 2;
    int discarded = 1;

    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded)
        failedTest();

    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
    if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - newCards)
        failedTest();

    printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
    if(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer] + discarded)
        failedTest();


    printf("--Test 1: After player draws card and plays discarded card, hand count should remain unchanged--\n");
    printf("num actions = %d, expected = %d\n", testG.numActions, G.numActions + newActions);
    if(testG.numActions != G.numActions + newActions)
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


    return 0;
}