/*********************************************************************
cardtest1.c

Author: David Moon
Date: 2-3-2017
Description:
    This test will test the smithy card in dominion.c.
    The following are key points the test will check:
    - The current player's actions decrease by 1
    - The current player's hand count increases by 2 (+3 for the card,
      and -1 to play the test card)
    - The current player's deck count decreases by 3
    - The current player's palyed card count increases by 1

Note: Some skeleton code for game setup was taken from cardtest4.c,
    which was posted to the OSU CS-362 course web page.

Include the following lines in your makefile:

cardtest1: cardtest1.c dominion.o rngs.o
    gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

**********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest1.h"  // custom assert function


int main() {
    int testResult = FAIL;
    int observed;
    int expected;
    int seed = 5;
    int numPlayers = 2;
    int currentPlayer = 0;
    int handPos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int testCard = smithy;
    char *testCardName = "smithy";
    int card1, card2, card3, card4, card5;
    int i = 0;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    printf("\n\n############# TESTING %s CARD ###############\n", testCardName);

    printf("TEST 1: Play %s card.\n\n", testCardName);
    // Setup
    currentPlayer = 0;

    card1 = testCard;
    card2 = silver;
    card3 = gold;
    card4 = adventurer;
    card5 = council_room;

    // construct the hand
    G.hand[currentPlayer][0] = card1;
    G.hand[currentPlayer][1] = card2;
    G.hand[currentPlayer][2] = card3;
    G.hand[currentPlayer][3] = card4;
    G.hand[currentPlayer][4] = card5;

    G.handCount[currentPlayer] = 5;

    // Populate the current player's deck with 10 cards
    G.deckCount[currentPlayer] = 10;
    for(i = 0; i < G.deckCount[currentPlayer]; i++){
        G.deck[currentPlayer][i] = adventurer;
    }

    printf("Current player deck count: %d\n", G.deckCount[currentPlayer]);
    printPlayerDeck(&G);

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // Ensure the player's hand is populated correctly
    printPlayerHand(&G);
    printExpectedHand(card1, card2, card3, card4, card5);
    printf("\n");

    // Play the test card
    cardEffect(testCard, choice1, choice2, choice3, &testG, handPos, &bonus);

    // Check if the player's deck count decreased by 3.
    observed = testG.deckCount[currentPlayer];
    expected = G.deckCount[currentPlayer] - 3;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Deck Count", observed, expected);

    // Check if the player's hand count was increased by 2 (play testCard and draw 3).
    observed = testG.handCount[currentPlayer];
    expected = G.handCount[currentPlayer] + 2;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Hand Count", observed, expected);
    printPlayerHand(&testG);

    // Check if the player's discard count stayed the same.
    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Discard Count", observed, expected);

    // Check that the played card count increased by 1.
    observed = testG.playedCardCount;
    expected = G.playedCardCount + 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Played Card Count", observed, expected);

    // Check that the players coins stayed the same.
    observed = testG.coins;
    expected = G.coins;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Coins", observed, expected);

    // Check that the other player's deck count stayed the same.
    observed = testG.deckCount[currentPlayer + 1];
    expected = G.deckCount[currentPlayer + 1];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Other Player's Deck Count", observed, expected);

    // Check that the players number of actions decreased by 1.
    observed = testG.numActions;
    expected = G.numActions - 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Number of Actions", observed, expected);

    printf("\n\nEND OF SMITHY CARD TEST\n\n");

    return 0;
}