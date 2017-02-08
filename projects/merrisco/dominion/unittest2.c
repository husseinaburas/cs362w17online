/* 
Program: unittest1.c
Author: Scott Merrill
Date: 02/05/17

Description: This program is designed as a test case for buyCard(). 
Preconditions: gamestate is initialized properly.
Postconditions: Printout  to the screen the results of the tests. 
*/


/***************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
    int testCoins = 0;
    int dummy = 0;
    int supply;

    int seed = 101;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    /************************************************************************************/
    G.coins = 4;
    testCoins = G.coins;
    dummy = G.handCount[thisPlayer];
    supply = G.supplyCount[4];
    buyCard(4,&G);
    if(G.handCount[thisPlayer] == dummy)
        printf("buyCard(): PASS for card added to hand\n");
    else
        printf("buyCard(): FAIL for card added to hand\n");

    if(G.coins == testCoins)
        printf("buyCard(): PASS for coins removed\n");
    else
        printf("buyCard(): FAIL for coins removed\n");

    if(G.numBuys == 0)
        printf("buyCard(): PASS for buys being decremented\n");
    else
        printf("buyCard(): FAIL for buys being decremented\n");

    if(supply == G.supplyCount[4])
        printf("buyCard(): FAIL for supplyCount being decremented\n");
    else
        printf("buyCard(): FAIL for supplyCount being decremented\n");

    return 0;
}
