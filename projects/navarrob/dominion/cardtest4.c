//
// Created by Rob Navarro on 2/1/17.
//

#include "dominion.h"
#include <stdio.h>

int main() {
    printf("\n*** Card Test 4: Council Room ***\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    initializeGame(2, k, 2, &G);

    //Set up hand and deck to check smithy
    printf("Setting game parameters so council room is card played and 4 cards will be drawn for player 1 and"
                   " 1 card for player 2\n");
    G.whoseTurn = 0;
    G.numActions = 1;
    G.numBuys = 1;
    G.handCount[0] = 1;
    G.numActions = 1;
    G.hand[0][0] = council_room;
    G.deckCount[0] = 5;
    G.handCount[1] = 0;
    G.deck[1][0] = gold;
    G.deck[1][1] = silver;
    G.deckCount[1] = 2;
    G.deck[0][0] = gold;
    G.deck[0][1] = silver;
    G.deck[0][2] = copper;
    G.deck[0][3] = smithy;
    G.deck[0][4] = village;
    G.deckCount[0] = 5;

    printf("Confirming that initial handCount is 1 for player 1.\n");
    customAssert(G.handCount[0] == 1);

    printf("Confirming that initial handCount is 0 for player 2.\n");
    customAssert(G.handCount[1] == 0);

    printf("Confirming that player 1 deckCount contains 5 card.\n");
    customAssert(G.deckCount[0] == 5);

    printf("Confirming that player 2 deckCount contains 2 card.\n");
    customAssert(G.deckCount[1] == 2);

    printf("Confirming that initial buys for player 1 is 1.\n");
    customAssert(G.numBuys == 1);

    printf("Confirming that initial actions is 1.\n");
    customAssert(G.numActions == 1);

    printf("***Playing the council_room card.\n");
    playCard(0, 0, 0, 0, &G);

    printf("***Checking player 1 attributes after card was played.\n");
    printf("Test that hand count for player 1 is now 4.\n");
    customAssert(G.handCount[0] == 4);
    printf("Test that deck count for player 1 is now 1.\n");
    customAssert(G.deckCount[0] == 1);
    printf("Test that first card in player 1 hand is gold.\n");
    customAssert(G.hand[0][0] == gold);
    printf("Test that second card in player 1 hand is village.\n");
    customAssert(G.hand[0][1] == village);
    printf("Test that third card in player 1 hand is smithy.\n");
    customAssert(G.hand[0][2] == smithy);
    printf("Test that fourth card in player 1 hand is copper.\n");
    customAssert(G.hand[0][3] == copper);
    printf("Test that actions is now 0.\n");
    customAssert(G.numActions == 0);
    printf("Test that there is one card in played cards pile.\n");
    customAssert(G.playedCardCount == 1);
    printf("Test that the top card in the played cards pile is council_room.\n");
    customAssert(G.playedCards[0] == council_room);

    printf("***Testing player 2 attributes after card was played.");
    printf("Test that hand count for player 2 is now 1.\n");
    customAssert(G.handCount[1] = 1);
    printf("Test that first card in hand for player 2 is silver.\n");
    customAssert(G.hand[1][0] == silver);
    printf("Test that player 2 deck now contains only 1 card.\n");
    customAssert(G.deckCount[1] == 1);

    return 0;
}


