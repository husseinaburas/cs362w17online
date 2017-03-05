//
// Created by Rob Navarro on 2/1/17.
//

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("\n*** Card Test 3: Village ***\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    initializeGame(2, k, 2, &G);

    //Set up hand and deck to check smithy
    printf("Setting game parameters so village is card played and gold will be the card drawn\n");
    G.whoseTurn = 0;
    G.numActions = 1;
    G.handCount[0] = 1;
    G.numActions = 1;
    G.hand[0][0] = village;
    G.deckCount[0] = 1;
    G.deck[0][0] = gold;

    printf("Confirming that initial handCount is 1.\n");
    customAssert(G.handCount[0] == 1);

    printf("Confirming that deckCount contains 1 card.\n");
    customAssert(G.deckCount[0] == 1);

    printf("Confirming that initial actions is 1\n");
    customAssert(G.numActions == 1);

    printf("*** Playing the village card.\n");
    playCard(0, 0, 0, 0, &G);

    printf("Test that hand count is now 2\n");
    customAssert(G.handCount[0] == 1);
    printf("Test that deck count is now 0\n");
    customAssert(G.deckCount[0] == 0);
    printf("Test that first card in hand is gold\n");
    customAssert(G.hand[0][0] == gold);
    printf("Test that actions is now 2\n");
    customAssert(G.numActions == 2);
    printf("Test that there is one card in played cards pile\n");
    customAssert(G.playedCardCount == 1);
    printf("Test that the top card in the played cards pile is village\n");
    customAssert(G.playedCards[0] == village);

    return 0;
}
