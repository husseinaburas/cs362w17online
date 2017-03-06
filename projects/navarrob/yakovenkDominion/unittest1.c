//
// Created by Rob Navarro on 2/1/17.
//

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>



int main() {
    /*
     * Testing: int buyCard(int supplyPos, struct gameState *state)
     */
    printf("\n*** Unit Test 1: Testing buyCard ***\n");

    struct gameState G;
    int i;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    initializeGame(2, k, 2, &G);

    // Setting card values for each card to 10 for testing purposes.
    for (i = 0; i < 27; i++) {
        G.supplyCount[i] = 10;
    }

    // The card that is being bought is the estate card, which is worth 2 coins.
    G.whoseTurn = 1;
    G.numBuys = 0;
    G.coins = 2;
    printf("Testing that a card can't be bought if numBuys < 1\n");
    customAssert(buyCard(2, &G) == -1);

    G.numBuys = 1;
    G.coins = 2;
    printf("Testing that a card can be bought if numBuys >= 1\n");
    customAssert(buyCard(estate, &G) == 0);

    G.numBuys = 2;
    G.coins = 2;
    printf("Testing that buyCard fails if we attempt to buy card -1, which doesn't exist.\n");
    customAssert(buyCard(-1, &G) == -1);

    //27 cards total so card 28 should return an error
    G.numBuys = 1;
    G.coins = 2;
    printf("Testing that buyCard fails if we attempt to buy card 28, which shouldn't exist.\n");
    customAssert(buyCard(27, &G) == -1);

    //Set card total to 0 and attempt to buy
    G.numBuys = 1;
    G.coins =2;
    G.supplyCount[estate] = 0;
    printf("Testing that buyCard fails if estate supply count is set to 0 and we attempt to buy.\n");
    customAssert(buyCard(estate, &G) == -1);

    return 0;
}
