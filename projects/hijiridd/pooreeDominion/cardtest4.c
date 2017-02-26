/* -----------------------------------------------------------------------
 *
 *          cardtest4.c
 *          
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

 #define TESTCARD "adventurer"

 void failedTest() {
    printf("**** FAILED TEST ****\n");
 }

int main() {
    int i;


    // Default values for calling cardEffect
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int discarded = 1, cardsGained = 2;;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    
    struct gameState G, testG, test2G;

    // Initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);


    printf("---------------------- Testing card: %s ----------------------\n", TESTCARD);

    printf("-----------Test 1: ----------\n");

    // copy the game state to a test case 
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded + cardsGained);
    if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] - discarded + cardsGained)
        failedTest();
    
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - cardsGained);
    if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - cardsGained)
        failedTest();

    printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
    if(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer] + discarded)
        failedTest();

    printf("-----------Check the drawn cards are treasure cards-------\n");
    //Set up player with no treasure cards
    test2G.hand[thisPlayer][0] = 1;
    test2G.hand[thisPlayer][1] = 1;
    test2G.hand[thisPlayer][2] = 1;
    test2G.hand[thisPlayer][3] = 1;
    test2G.hand[thisPlayer][4] = 1;
    test2G.deck[thisPlayer][0] = 1;
    test2G.deck[thisPlayer][1] = 1;
    test2G.deck[thisPlayer][2] = 1;
    test2G.deck[thisPlayer][3] = 1;
    test2G.deck[thisPlayer][4] = 1;
    cardEffect(adventurer, choice1, choice2, choice3, &test2G, handpos, &bonus);

    printf("a player with no treasure cards should be stuck in a while loop (infeasible in real game, but proof of found bug)");
    if((testG.hand[thisPlayer][test2G.handCount[thisPlayer]-1] < 4) || (test2G.hand[thisPlayer][test2G.handCount[thisPlayer]-1] > 6))
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