/* -----------------------------------------------------------------------
 *
 *          unittest1.c
 *          Unit Testing discardCard()
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

 #define TESTFUNCTION "discardCard()"

 void failedTest() {
    printf("!!!! FAILED TEST !!!!\n");
 }

int main() {
    // Some initialization variables
    int handpos = 0;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    
    struct gameState G, testG;

    // Initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);


    printf("---------------------- Testing card: %s ----------------------\n", TESTFUNCTION);

    printf("--Test 1: Test that current player's hand count decreases by 1 with no trash flag --\n");

    // copy the game state to a test case 
    memcpy(&testG, &G, sizeof(struct gameState));
    int trashFlag = 0;
    int discarded = 1;
    discardCard(handpos, currentPlayer, &G, trashFlag);
    printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer] - discarded, G.handCount[currentPlayer]);
    if(testG.handCount[currentPlayer] - discarded != G.handCount[currentPlayer])
        failedTest();

    printf("played card count = %d, expected %d\n", testG.playedCardCount + discarded, G.playedCardCount);
    if(testG.playedCardCount + discarded != G.playedCardCount)
        failedTest();

    printf("--Test 2: Test that current player's hand count decreases by 1 with trash flag --\n");

    // copy the game state to a test case 
    memcpy(&testG, &G, sizeof(struct gameState));
    trashFlag = 1;
    discardCard(handpos, currentPlayer, &G, trashFlag);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer] - discarded, G.handCount[currentPlayer]);
    if(testG.handCount[currentPlayer] - discarded != G.handCount[currentPlayer])
        failedTest();

    printf("played card count = %d, expected %d\n", testG.playedCardCount, G.playedCardCount);
    if(testG.playedCardCount != G.playedCardCount)
        failedTest();

    printf("-----Test 3: Test discarded card is replaced by last card in hand-----\n");
    printf("card at handpos = %d, expected %d\n", testG.hand[currentPlayer][testG.handCount[currentPlayer] - 1], G.hand[currentPlayer][handpos]);
    if(testG.hand[currentPlayer][testG.handCount[currentPlayer] - 1] != G.hand[currentPlayer][handpos])
        failedTest();

    printf("card in discarded position = %d, expected -1\n", G.hand[currentPlayer][G.handCount[currentPlayer]]);
    if (G.hand[currentPlayer][testG.handCount[currentPlayer]] != -1) 
        failedTest();


    printf("------------ Testing complete for: %s -----------------------\n", TESTFUNCTION);
    return 0;
}
