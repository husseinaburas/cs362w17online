/*********************************************************************
cardtest4.c

Author: David Moon
Date: 2-3-2017
Description:
    This test will test the feast card in dominion.c.
    The following are key points the test will check:
    - The player's hand count remains the same (trash this card and
      gain a new card)
    - The cost of the card gained is 5 or less
    - The player's actions are decreased by 1
    - The supply count of the card taken is decreased by 1
    - The player's discard count is increased by 1 (choice1)
    - The player's played card count stays the same

Note: Some skeleton code for game setup was taken from cardtest4.c,
    which was posted to the OSU CS-362 course web page.

Include the following lines in your makefile:

cardtest4: cardtest4.c dominion.o rngs.o
    gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

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
    int testCard = feast;
    char *testCardName = "feast";
    int card1, card2, card3, card4, card5;
    int i = 0;

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("\n\n############# TESTING %s CARD ###############\n", testCardName);

    printf("TEST 1: Play %s card.\n\n", testCardName);
    // Setup
    currentPlayer = 0;
    choice1 = mine;

    card1 = testCard; // index 0 in player's hand
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

    printf("SETUP\n");
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

    // Print player's hand after the card is played
    printf("Player's hand after test card is played\n");
    printPlayerHand(&testG);
    printf("\n");

    // Check if the player's deck count stayed the same.
    observed = testG.deckCount[currentPlayer];
    expected = G.deckCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Deck Count", observed, expected);

    // Check if the player's hand count stayed the same (-1 to play the test
    // card and +1 for the card gained)
    observed = testG.handCount[currentPlayer];
    expected = G.handCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Hand Count", observed, expected);

    // Check if the player's discard count is increased by 1.
    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer] + 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Discard Count", observed, expected);

    // Check that the played card count stayes the same.
    observed = testG.playedCardCount;
    expected = G.playedCardCount;
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

    // Check that the other player's hand count stayed the same.
    observed = testG.handCount[currentPlayer + 1];
    expected = G.handCount[currentPlayer + 1];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Other Player's Hand Count", observed, expected);

    // Check that the player's number of buys stayed the same.
    observed = testG.numBuys;
    expected = G.numBuys;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Number of Buys", observed, expected);

    // Check that the supply pile of the taken card decreased by 1
    observed = testG.supplyCount[choice1];
    expected = G.supplyCount[choice1] - 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Supply Count of Choice", observed, expected);

    // Check that the cost of choice1 is less than 5
    observed = getCost(choice1);
    expected = 5;
    if(observed <= expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Cost of Choice (observed <= expected)", observed, expected);

    printf("\n\nEND OF %s CARD TEST\n\n", testCardName);

    return 0;
}