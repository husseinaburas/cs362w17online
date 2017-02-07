//
// Created by Rob Navarro on 2/1/17.
//

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("\n*** Card Test 1: Smithy ***\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    initializeGame(2, k, 2, &G);

    //Set up hand and deck to check smithy
    G.whoseTurn = 0;
    G.numActions = 1;
    G.handCount[0] = 1;
    G.hand[0][0] = smithy;
    G.deck[0][4] = gold;
    G.deck[0][3] = silver;
    G.deck[0][2] = copper;
    // Leave 2 extra cards in deck in case of overdraw.

    printf("Confirming that initial handCount is 1.\n");
    customAssert(G.handCount[0] == 1);

    printf("Confirming that deck initially contains 5 cards.\n");
    customAssert(G.deckCount[0] == 5);

    printf("Confirming that number of actions is 1\n");
    customAssert(G.numActions == 1);

    printf("*** Playing the smithy card\n");
    playCard(0, 0, 0, 0, &G);

    printf("Test that hand count is now 3\n");
    customAssert(G.handCount[0] == 3);
    printf("Test that deck count is now 2\n");
    customAssert(G.deckCount[0] == 2);
    printf("Test that first card in hand is gold\n");
    customAssert(G.hand[0][1] == gold);
    printf("Test that second card in hand is silver\n");
    customAssert(G.hand[0][2] == silver);
    printf("Test that third card in hand is copper\n");
    customAssert(G.hand[0][3] == copper);
    printf("Test that there is one card in played cards pile\n");
    customAssert(G.playedCardCount == 1);
    printf("Test that card in played cards pile is smithy\n");
    customAssert(G.playedCards[0] == smithy);
    printf("Test that the number of actions is now 0\n");
    customAssert(G.numActions == 0);

    return 0;
}



