/*********************************************************************
unittest1.c

Author: David Moon
Date: 2-1-2017
Description:
    This unit test will test the buyCard() function in dominion.c.
    The following are key points the test will check:
    - The purchased card is added to the player's discard pile
    - The player has sufficient coins to purchase the card
    - The appropriate amount of coins are removed from the player's coins
    - The card is removed from the appropriate supply pile
    - No other supply piles are affected
    - No state changes should occur for other players
    - Ensure the player has at least 1 buy left
    - Ensure the player cannot buy from an empty pile

Note: Some skeleton code for game setup was taken from cardtest4.c,
    which was posted to the OSU CS-362 course web page.

Include the following lines in your makefile:

unittest1: unittest1.c dominion.o rngs.o
    gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

**********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest1.h"


int main() {
    int testResult = FAIL;
    int observed;
    int expected;
    int seed = 5;
    int numPlayers = 2;
    int currentPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    int cardToBuy;
    int cardCost;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    printf("\n\n############# TESTING buyCard() FUNCTION ###############\n");


    printf("TEST 1: Buy a card with sufficient coins and available supply.\n\n");
    G.numBuys = 3;  //set player's number of buys
    G.coins = 5;    //set player's number of coins

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    cardToBuy = village;
    cardCost = getCost(cardToBuy);

    // Buy the cardToBuy
    buyCard(cardToBuy, &testG);
        
    // Check if the player's number of buys was decreased by 1.
    observed = testG.numBuys;
    expected = G.numBuys - 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Num Buys", observed, expected);

    // Check if the supply count for the purchased card was decreased by 1.
    observed = testG.supplyCount[cardToBuy];
    expected = G.supplyCount[cardToBuy] - 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Supply Count", observed, expected);

    // Check if the discard count for the player was increased by 1.
    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer] + 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Discard Count", observed, expected);

    // Check if the players coins were decreased by the cost of the purchased card.
    observed = testG.coins;
    expected = G.coins - cardCost;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Coins", observed, expected);

    printf("\n\nTEST 2: Buy a card with insufficient coins and available supply.\n\n");
    G.numBuys = 3;  //set player's number of buys
    G.coins = 3;    //set player's number of coins

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    cardToBuy = smithy;
    cardCost = getCost(cardToBuy);

    // Buy the cardToBuy
    buyCard(cardToBuy, &testG);

    // Note: The card should NOT have been purchased.
        
    // Check if the player's number of buys stayed the same.
    observed = testG.numBuys;
    expected = G.numBuys;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Num Buys", observed, expected);

    // Check if the supply count stayed the same.
    observed = testG.supplyCount[cardToBuy];
    expected = G.supplyCount[cardToBuy];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Supply Count", observed, expected);

    // Check if the player's discard count stayed the same.
    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Discard Count", observed, expected);

    // Check if the player's coins stayed the same.
    observed = testG.coins;
    expected = G.coins;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Coins", observed, expected);

    printf("\n\nTEST 3: Buy a card with sufficient coins and unavailable supply.\n\n");
    G.numBuys = 3;  //set player's number of buys
    G.coins = 3;    //set player's number of coins
    G.supplyCount[mine] = 0;    //set supply pile count to 0

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    cardToBuy = mine;
    cardCost = getCost(cardToBuy);

    // Buy the cardToBuy
    buyCard(cardToBuy, &testG);

    // Note: The card should NOT have been purchased.
        
    // Check if the player's number of buys stayed the same.
    observed = testG.numBuys;
    expected = G.numBuys;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Num Buys", observed, expected);

    // Check if the the supply count stayed the same.
    observed = testG.supplyCount[cardToBuy];
    expected = G.supplyCount[cardToBuy];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Supply Count", observed, expected);

    // Check if the player's discard count stayed the same.
    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Discard Count", observed, expected);

    // Check if the player's coins stayed the same.
    observed = testG.coins;
    expected = G.coins;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Coins", observed, expected);

    printf("\n\nEND OF UNIT TEST 1\n\n");

    return 0;
}