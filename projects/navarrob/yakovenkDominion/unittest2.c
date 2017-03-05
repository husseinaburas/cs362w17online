//
// Created by Rob Navarro on 2/1/17.
//

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

//Testing int numHandCards(struct gameState *state);
int main() {
    struct gameState G;
    int i;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    initializeGame(2, k, 2, &G);

    printf("\n*** Unit test 2: Testing numHandCards ***\n");
    printf("Testing with player 1 as the player\n");

    printf("Confirm that initial cards in hand is 5.\n");
    customAssert(numHandCards(&G) == 5);

    printf("Adding five cards to hand and confirm value is 10\n");
    for (i = 0; i < 5; i++) {
        drawCard(0, &G);
    }
    customAssert(numHandCards(&G) == 10);

    printf("Confirm that the number of cards in hand doesn't increase if deck is empty\n");
    drawCard(0, &G);
    customAssert(numHandCards(&G) == 10);

    printf("Remove all cards from hand and confirm value is 0\n");
    for (i = 0; i < 10; i++) {
        discardCard(i, 0, &G, 0);
    }
    customAssert(numHandCards(&G) == 0);

    printf("Confirm that the number of cards doesn't go negative if the hand is empty\n");
    discardCard(0, 0, &G, 0);
    customAssert(numHandCards(&G) == 0);

    return 0;
}
