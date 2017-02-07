//
// Created by Rob Navarro on 2/1/17.
//

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("\n*** Card Test 2: Adventurer ***\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    initializeGame(2, k, 2, &G);

    //Set up hand and deck to check smithy
    G.whoseTurn = 0;
    G.numActions = 1;
    G.handCount[0] = 1;
    G.hand[0][0] = adventurer;
    G.deck[0][4] = mine;
    G.deck[0][3] = silver;
    G.deck[0][2] = tribute;
    G.deck[0][1] = embargo;
    G.deck[0][0] = gold;

    printf("Confirming that initial handCount is 1.\n");
    customAssert(G.handCount[0] == 1);

    printf("Confirming that deck initially contains 5 cards.\n");
    customAssert(G.deckCount[0] == 5);

    printf("Confirming that initial number of actions is 1\n");
    customAssert(G.numActions == 1);

    printf("*** Playing adventurer card\n");
    playCard(0, 0, 0, 0, &G);

    printf("Test that hand count is now 3\n");
    customAssert(G.handCount[0] == 3);
    printf("Test that deck count is now 0\n");
    customAssert(G.deckCount[0] == 0);
    printf("Test that second card in hand is silver\n");
    customAssert(G.hand[0][1] == silver);
    printf("Test that third card in hand is gold\n");
    customAssert(G.hand[0][2] == gold);
    printf("Test that there is one card in played cards pile\n");
    customAssert(G.discardCount[0]== 3);
    printf("Test that the top card in the discard pile is embargo\n");
    customAssert(G.discard[0][0] == embargo);
    printf("Confirm that number of actions is now 0.\n");
    customAssert(G.numActions == 0);

    return 0;
}
