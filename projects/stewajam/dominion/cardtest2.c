/***************************************
* Name: James Stewart
* Date: 1/31/2017
* File: cardtest1.c
* Description: Tests the Adventurer card
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
    int observed, expected;
    int seed = 5;
    int numPlayers = 2;
    int currentPlayer = 0;
    int handPos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};
    int testCard = adventurer;
    char *testCardName = "Adventurer";
    int i = 0;
    int totalDeck = 0;
    int numActionCards = 0;

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("\n\n----------------- TESTING %s CARD -----------------\n\n", testCardName);
    printf("TEST 1: Play %s card\n\n", testCardName);
    printf("Top 2 cards in deck are treasure cards\n\n");
    currentPlayer = whoseTurn(&G);

    // Populate the current player's deck with 10 cards
    G.deckCount[currentPlayer] = 10;
    totalDeck = G.deckCount[currentPlayer];
    numActionCards = 8;

    for(i = 0; i < numActionCards; i++){
        G.deck[currentPlayer][i] = mine;
    }

    for(i = numActionCards; i < totalDeck; i++){
        G.deck[currentPlayer][i] = copper;
    }
    G.hand[currentPlayer][0] = testCard;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    observed = testG.hand[currentPlayer][0];
    expected = testCard;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Test Card At Index 0", observed, expected);

    printf("Player hand before playing test card.\n");
    printHand(&testG);
    printf("\n");

    printf("Player deck before playing test card.\n");
    printDeck(&testG);
    printf("\n");

    playCard(0, choice1, choice2, choice3, &testG);

    printf("Player hand after playing test card.\n");
    printHand(&testG);
    printf("\n");

    printf("Player deck after playing test card.\n");
    printDeck(&testG);
    printf("\n");

    observed = testG.deckCount[currentPlayer];
    expected = G.deckCount[currentPlayer] - 2;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Deck Count", observed, expected);

    observed = testG.handCount[currentPlayer];
    expected = G.handCount[currentPlayer] + 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Hand Count", observed, expected);
    printHand(&testG);

    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Discard Count", observed, expected);

    observed = testG.playedCardCount;
    expected = G.playedCardCount + 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Played Card Count", observed, expected);

    observed = testG.coins;
    expected = G.coins + 2;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Coins", observed, expected);

    observed = testG.deckCount[currentPlayer + 1];
    expected = G.deckCount[currentPlayer + 1];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Other Player's Deck Count", observed, expected);

    observed = testG.numActions;
    expected = G.numActions - 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Number of Actions", observed, expected);

    printf("\n\nTEST 2: Play %s card.\n", testCardName);
    printf("Top 2 cards in deck action cards, next 2 treasures (1 gold, 1 silver).\n\n");
    currentPlayer = whoseTurn(&G);

    G.deckCount[currentPlayer] = 10;
    totalDeck = G.deckCount[currentPlayer];
    numActionCards = 8;

    for(i = 0; i < totalDeck; i++){
        G.deck[currentPlayer][i] = mine;
    }
    G.deck[currentPlayer][6] = gold;
    G.deck[currentPlayer][7] = silver;
    G.hand[currentPlayer][0] = testCard;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // Check if the test card is at index 0 in the player's hand.
    observed = testG.hand[currentPlayer][0];
    expected = testCard;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Test Card At Index 0", observed, expected);

    printf("Player hand before playing test card.\n");
    printHand(&testG);
    printf("\n");

    printf("Player deck before playing test card.\n");
    printDeck(&testG);
    printf("\n");

    // Play the test card
    cardEffect(testCard, choice1, choice2, choice3, &testG, handPos, &bonus);

    printf("Player hand after playing test card.\n");
    printHand(&testG);
    printf("\n");

    printf("Player deck after playing test card.\n");
    printDeck(&testG);
    printf("\n");

    // Check if the player's deck count decreased by 4.
    observed = testG.deckCount[currentPlayer];
    expected = G.deckCount[currentPlayer] - 4;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Deck Count", observed, expected);

    // Check if the player's hand count increased by 3 (play 1 card, draw 4).
    observed = testG.handCount[currentPlayer];
    expected = G.handCount[currentPlayer] + 3;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Hand Count", observed, expected);
    printHand(&testG);

    // Check if the player's discard count increased by 2.
    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer] + 2;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Discard Count", observed, expected);

    // Check that the played card count increased by 1.
    observed = testG.playedCardCount;
    expected = G.playedCardCount + 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Played Card Count", observed, expected);

    // Check that the players coins increased by 5.
    observed = testG.coins;
    expected = G.coins + 5;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Coins", observed, expected);

    // Check that the other player's deck count stayed the same.
    observed = testG.deckCount[currentPlayer + 1];
    expected = G.deckCount[currentPlayer + 1];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Other Player's Deck Count", observed, expected);

    // Check that the players number of actions decreased by 1.
    observed = testG.numActions;
    expected = G.numActions - 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Number of Actions", observed, expected);



    printf("\n\nTEST 3: Play %s card.\n", testCardName);
    printf("No treasures in deck (10 cards in deck).\n\n");
    // Setup
    currentPlayer = whoseTurn(&G);

    // Populate the current player's deck with 10 cards
    // The first 8 are actions, the last 2 are treasures
    G.deckCount[currentPlayer] = 10;
    totalDeck = G.deckCount[currentPlayer];
    numActionCards = 8;

    // Set all 10 cards in deck to action cards
    for(i = 0; i < totalDeck; i++){
        G.deck[currentPlayer][i] = mine;
    }

    // Put the test card in the player's hand
    G.hand[currentPlayer][0] = testCard;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // Check if the test card is at index 0 in the player's hand.
    observed = testG.hand[currentPlayer][0];
    expected = testCard;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Test Card At Index 0", observed, expected);

    printf("Player hand before playing test card.\n");
    printHand(&testG);
    printf("\n");

    printf("Player deck before playing test card.\n");
    printDeck(&testG);
    printf("\n");

    // Play the test card
    cardEffect(testCard, choice1, choice2, choice3, &testG, handPos, &bonus);

    printf("Player hand after playing test card.\n");
    printHand(&testG);
    printf("\n");

    printf("Player deck after playing test card.\n");
    printDeck(&testG);
    printf("\n");

    // Check if the player's deck count decreased by 10.
    observed = testG.deckCount[currentPlayer];
    expected = G.deckCount[currentPlayer] - 10;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Deck Count", observed, expected);

    // Check if the player's hand count stays the same
    observed = testG.handCount[currentPlayer];
    expected = G.handCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Hand Count", observed, expected);
    printHand(&testG);

    // Check if the player's discard count increased by 10.
    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer] + 2;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Discard Count", observed, expected);

    // Check that the played card count increased by 1.
    observed = testG.playedCardCount;
    expected = G.playedCardCount + 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Played Card Count", observed, expected);

    // Check that the players coins stayed the same.
    observed = testG.coins;
    expected = G.coins;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Coins", observed, expected);

    // Check that the other player's deck count stayed the same.
    observed = testG.deckCount[currentPlayer + 1];
    expected = G.deckCount[currentPlayer + 1];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Other Player's Deck Count", observed, expected);

    // Check that the players number of actions decreased by 1.
    observed = testG.numActions;
    expected = G.numActions - 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    assertTrue(testResult, "Number of Actions", observed, expected);

    printf("\n\nEND OF %s CARD TEST\n\n", testCardName);

    return 0;
}