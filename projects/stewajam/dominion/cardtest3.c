/***************************************
* Name: James Stewart
* Date: 1/31/2017
* File: cardtest1.c
* Description: Tests the Feast card
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
    int observed;
    int expected;
    int seed = 5;
    int numPlayers = 2;
    int currentPlayer = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};
    int testCard = feast;
    char *testCardName = "Feast";
    int card1, card2, card3, card4, card5;
    int i = 0;

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("\n\n----------------- TESTING %s CARD -----------------\n\n", testCardName);

    printf("TEST 1: Play %s card.\n\n", testCardName);
    currentPlayer = 0;
    choice1 = mine;
    card1 = testCard;
    card2 = silver;
    card3 = gold;
    card4 = adventurer;
    card5 = council_room;
    G.hand[currentPlayer][0] = card1;
    G.hand[currentPlayer][1] = card2;
    G.hand[currentPlayer][2] = card3;
    G.hand[currentPlayer][3] = card4;
    G.hand[currentPlayer][4] = card5;
    G.handCount[currentPlayer] = 5;

    G.deckCount[currentPlayer] = 10;
    for(i = 0; i < G.deckCount[currentPlayer]; i++){
        G.deck[currentPlayer][i] = adventurer;
    }

    printf("SETUP\n");
    printf("Current player deck count: %d\n", G.deckCount[currentPlayer]);
    printDeck(&G);

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    printHand(&G);
    printExpHand(card1, card2, card3, card4, card5);
    printf("\n");
    playCard(0, choice1, choice2, choice3, &testG);
    printf("Player's hand after test card is played\n");
    printHand(&testG);
    printf("\n");
    observed = testG.deckCount[currentPlayer];
    expected = G.deckCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Deck Count", observed, expected);

    observed = testG.handCount[currentPlayer];
    expected = G.handCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Hand Count", observed, expected);

    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer] + 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Discard Count", observed, expected);

    observed = testG.playedCardCount;
    expected = G.playedCardCount;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Played Card Count", observed, expected);

    observed = testG.coins;
    expected = G.coins;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Coins", observed, expected);

    observed = testG.deckCount[currentPlayer + 1];
    expected = G.deckCount[currentPlayer + 1];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Other Player's Deck Count", observed, expected);

    observed = testG.handCount[currentPlayer + 1];
    expected = G.handCount[currentPlayer + 1];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Other Player's Hand Count", observed, expected);

    observed = testG.numBuys;
    expected = G.numBuys;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Number of Buys", observed, expected);

    observed = testG.supplyCount[choice1];
    expected = G.supplyCount[choice1] - 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Supply Count of Choice", observed, expected);

    observed = getCost(choice1);
    expected = 5;
    if(observed <= expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Cost of Choice (observed <= expected)", observed, expected);

    printf("\n\nEND OF %s CARD TEST\n\n", testCardName);

    return 0;
}