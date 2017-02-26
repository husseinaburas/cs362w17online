/* -----------------------------------------------------------------------
 *
 *          unittest1.c
 *          Unit Testing scoreFor()
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

 #define TESTFUNCTION "scoreFor()"

 void failedTest() {
    printf("!!!! FAILED TEST !!!!\n");
 }

int main() {
    // Some initialization variables
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    
    struct gameState G;

    // Initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);


    printf("---------------------- Testing card: %s ----------------------\n", TESTFUNCTION);

    printf("--Test 1: If player has no cards, score for should be 0 --\n");
    G.handCount[currentPlayer] = 0;
    G.deckCount[currentPlayer] = 0;
    G.discardCount[currentPlayer] = 0;
    printf("current score = %d, expected 0\n", scoreFor(currentPlayer, &G));
    if(scoreFor(currentPlayer, &G) != 0)
        failedTest();

    printf("--Test 2: Test results from cards in hand / test negative score will not break function--\n");
    G.handCount[currentPlayer] = 5;
    G.hand[currentPlayer][0] = curse;
    G.hand[currentPlayer][1] = curse;
    G.hand[currentPlayer][2] = curse;
    G.hand[currentPlayer][3] = curse;
    G.hand[currentPlayer][4] = curse;
    printf("current score = %d, expected -5\n", scoreFor(currentPlayer, &G));
    if(scoreFor(currentPlayer, &G) != -5)
        failedTest();

    printf("--Test 3: Test results from cards in hand - mixed card types--\n");
    G.handCount[currentPlayer] = 5;
    G.hand[currentPlayer][0] = copper;
    G.hand[currentPlayer][1] = gold;
    G.hand[currentPlayer][2] = estate;
    G.hand[currentPlayer][3] = curse;
    G.hand[currentPlayer][4] = province;
    printf("current score = %d, expected 6\n", scoreFor(currentPlayer, &G));
    if(scoreFor(currentPlayer, &G) != 6)
        failedTest();


    printf("--Test 4: Test results from cards in deck - mixed card types--\n");
    G.handCount[currentPlayer] = 0;
    G.deckCount[currentPlayer] = 3;
    G.deck[currentPlayer][0] = copper;
    G.deck[currentPlayer][1] = curse;
    G.deck[currentPlayer][2] = province;
    printf("current score = %d, expected 5\n", scoreFor(currentPlayer, &G));
    if(scoreFor(currentPlayer, &G) != 5)
        failedTest();


    printf("--Test 5: Test results from cards in discard - mixed card types--\n");
    G.deckCount[currentPlayer] = 0;
    G.deck[currentPlayer][0] = -1;          // Set card values to -1. After finding bug, also realized when deckCount = 0, cards still stored in the array
    G.deck[currentPlayer][1] = -1;
    G.deck[currentPlayer][2] = -1;
    G.discardCount[currentPlayer] = 3;
    G.discard[currentPlayer][0] = copper;
    G.discard[currentPlayer][1] = estate;
    G.discard[currentPlayer][2] = province;
    printf("current score = %d, expected 7\n", scoreFor(currentPlayer, &G));
    if(scoreFor(currentPlayer, &G) != 7)
        failedTest();

    /******************************************************************************
    *
    * Could do additional tests to see the interaction of the different things being counted though, each piece has been 
    * tested individually at this point and it has been seen that depending on if the sizes of discardCount and deckCount are 
    * different from one another, the function is going to return the right value or not.
    *
    ********************************************************************************/


    printf("------------ Testing complete for: %s -----------------------\n", TESTFUNCTION);
    return 0;
}
