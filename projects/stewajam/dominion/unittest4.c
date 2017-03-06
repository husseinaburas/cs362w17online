/***************************************
* Name: James Stewart
* Date: 1/31/2017
* File: cardtest1.c
* Description: Tests the buyCard() Function
***************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "unittest.h"

int main() {
    int testResult = FAIL;
    int observed, expected, cardToBuy, cardCost;
    int seed = 5;
    int numPlayers = 2;
    int currentPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    printf("\n\n----------------- TESTING buyCard() FUNCTION -----------------\n\n");
    printf("TEST 1: Buy a card with sufficient coins and available supply\n\n");
    G.numBuys = 3;
    G.coins = 5;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    cardToBuy = village;
    cardCost = getCost(cardToBuy);
    buyCard(cardToBuy, &testG);
	
    observed = testG.numBuys;
    expected = G.numBuys - 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Buys", observed, expected);

    observed = testG.supplyCount[cardToBuy];
    expected = G.supplyCount[cardToBuy] - 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Supplies", observed, expected);

    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer] + 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Discards", observed, expected);

    observed = testG.coins;
    expected = G.coins - cardCost;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Coins", observed, expected);

    printf("\n\nTEST 2: Buy a card with insufficient coins and available supply\n\n");
    G.numBuys = 3;
    G.coins = 3;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    cardToBuy = smithy;
    cardCost = getCost(cardToBuy);
    buyCard(cardToBuy, &testG);

    observed = testG.numBuys;
    expected = G.numBuys;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Buys", observed, expected);

    observed = testG.supplyCount[cardToBuy];
    expected = G.supplyCount[cardToBuy];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Supplies", observed, expected);

    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Discards", observed, expected);

    observed = testG.coins;
    expected = G.coins;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Coins", observed, expected);

    printf("\n\nTEST 3: Buy a card with sufficient coins and unavailable supply\n\n");
    G.numBuys = 3;
    G.coins = 3;
    G.supplyCount[mine] = 0;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    cardToBuy = mine;
    cardCost = getCost(cardToBuy);
    buyCard(cardToBuy, &testG);

    observed = testG.numBuys;
    expected = G.numBuys;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Buys", observed, expected);

    observed = testG.supplyCount[cardToBuy];
    expected = G.supplyCount[cardToBuy];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Supplies", observed, expected);

    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Discards", observed, expected);

    observed = testG.coins;
    expected = G.coins;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Coins", observed, expected);

    printf(" >>>>> SUCCESS: Testing buyCard() complete <<<<<\n\n");

    return 0;
}