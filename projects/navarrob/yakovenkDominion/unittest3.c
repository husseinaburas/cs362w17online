//
// Created by Rob Navarro on 2/1/17.
//

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

void setHand(int player, struct gameState *state, int type) {
    //Helper function to quickly set a hand of 5 to all of one type of card.
    int i;

    for(i = 0; i < 5; i++) {
        state->hand[player][i] = type;
    }
}

//Testing int updateCoins(int player, struct gameState *state, int bonus)
int main() {
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    initializeGame(2, k, 2, &G);
    G.whoseTurn = 0;
    printf("\n*** Unit Test 3: Testing updateCoins ***\n");

    //Set player 0 hand to be all copper
    setHand(G.whoseTurn, &G, copper);
    printf("Testing that a hand off all copper returns a coin value of 5.\n");
    updateCoins(0, &G, 0);
    customAssert(G.coins == 5);

    //Set player 0 hand to be all silver
    setHand(G.whoseTurn, &G, silver);
    printf("Testing that a hand off all silver returns a coin value of 10.\n");
    updateCoins(0, &G, 0);
    customAssert(G.coins == 10);

    //Set player 0 hand to be all gold
    setHand(G.whoseTurn, &G, gold);
    printf("Testing that a hand off all silver returns a coin value of 15.\n");
    updateCoins(0, &G, 0);
    customAssert(G.coins == 15);

    //Set player 0 hand to contain no treasure
    setHand(G.whoseTurn, &G, estate);
    printf("Testing that a hand with no treasure has a coin value of 0.\n");
    updateCoins(0, &G, 0);
    customAssert(G.coins == 0);

    //Setting hand to contain 1 copper, silver and gold.
    G.hand[0][0] = copper;
    G.hand[0][1] = silver;
    G.hand[0][2] = gold;
    printf("Testing that hand with 1 copper, silver and gold has a value of 6\n");
    updateCoins(0, &G, 0);
    customAssert(G.coins == 6);

    return 0;
}