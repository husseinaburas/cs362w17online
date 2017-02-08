/*********************************************************************
unittest3.c

Author: David Moon
Date: 2-1-2017
Description:
    This unit test will test the updateCoins() function in dominion.c.
    The following are key points the test will check:
    - Ensure that the player's coins are counted correctly
    - Ensure that bonuses are added to the player's coin total correctly
    - Ensure the player's hand count is not affected
    - Ensure the player's deck count is not affected
    - Ensure the player's discard count is not affected
    - Ensure the played card count is not affected

Note: Some skeleton code for game setup was taken from cardtest4.c,
    which was posted to the OSU CS-362 course web page.

Include the following lines in your makefile:

unittest3: unittest3.c dominion.o rngs.o
    gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

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
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    int currentPlayer = whoseTurn(&G);
    int i;
    int bonus;
    int card1, card2, card3, card4, card5;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    printf("\n\n############# TESTING updateCoins() FUNCTION ###############\n");


    printf("TEST 1: Hand with 1 copper, 1 silver, 1 gold (no bonus).\n\n");

    card1 = copper;
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
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    bonus = 0;

    // confirm that the player's hand is populated properly
    printf("Player hand: \t");
    for(i = 0; i < G.handCount[currentPlayer]; i++){
        printf("%d ", G.hand[currentPlayer][i]);
    }
    printf("\nExpected hand: \t%d %d %d %d %d\n", card1, card2, card3, card4, card5);

    // Update the player's coins total
    updateCoins(currentPlayer, &testG, bonus);
        
    // Check that the player's coin total equals the expected value.
    observed = testG.coins;
    expected = 6;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Coins", observed, expected);

    // Check that the played card count stayed the same.
    observed = testG.playedCardCount;
    expected = G.playedCardCount;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Played Card Count", observed, expected);

    // Check that the discard stayed the same.
    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Discard Count", observed, expected);

    // Check that the player's deck count stayed the same.
    observed = testG.deckCount[currentPlayer];
    expected = G.deckCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Player Deck Count", observed, expected);

    // Check if the player's hand count stayed the same.
    observed = testG.handCount[currentPlayer];
    expected = G.handCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Hand Count", observed, expected);


    printf("\n\nTEST 2: Hand with 3 coppers and a bonus of 2.\n\n");

    card1 = copper;
    card2 = smithy;
    card3 = copper;
    card4 = estate;
    card5 = copper;

    // construct the hand
    G.hand[currentPlayer][0] = card1;
    G.hand[currentPlayer][1] = card2;
    G.hand[currentPlayer][2] = card3;
    G.hand[currentPlayer][3] = card4;
    G.hand[currentPlayer][4] = card5;

    G.handCount[currentPlayer] = 5;

    bonus = 2;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // confirm that the player's hand is populated properly
    printf("Player hand: \t");
    for(i = 0; i < G.handCount[currentPlayer]; i++){
        printf("%d ", G.hand[currentPlayer][i]);
    }
    printf("\nExpected hand: \t%d %d %d %d %d\n", card1, card2, card3, card4, card5);

    // Update the player's coins total
    updateCoins(currentPlayer, &testG, bonus);
        
    // Check that the player's coin total equals the expected value.
    observed = testG.coins;
    expected = 5;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Coins", observed, expected);
    
    // Check that the played card count stayed the same.
    observed = testG.playedCardCount;
    expected = G.playedCardCount;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Played Card Count", observed, expected);

    // Check that the discard stayed the same.
    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Discard Count", observed, expected);

    // Check that the player's deck count stayed the same.
    observed = testG.deckCount[currentPlayer];
    expected = G.deckCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Player Deck Count", observed, expected);

    // Check if the player's hand count stayed the same.
    observed = testG.handCount[currentPlayer];
    expected = G.handCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Hand Count", observed, expected);


    printf("\n\nTEST 3: Hand with no treasures and bonus of 5.\n\n");
    
    card1 = province;
    card2 = smithy;
    card3 = feast;
    card4 = estate;
    card5 = tribute;

    // construct the hand
    G.hand[currentPlayer][0] = card1;
    G.hand[currentPlayer][1] = card2;
    G.hand[currentPlayer][2] = card3;
    G.hand[currentPlayer][3] = card4;
    G.hand[currentPlayer][4] = card5;

    G.handCount[currentPlayer] = 5;

    bonus = 5;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // confirm that the player's hand is populated properly
    printf("Player hand: \t");
    for(i = 0; i < G.handCount[currentPlayer]; i++){
        printf("%d ", G.hand[currentPlayer][i]);
    }
    printf("\nExpected hand: \t%d %d %d %d %d\n", card1, card2, card3, card4, card5);

    // Update the player's coins total
    updateCoins(currentPlayer, &testG, bonus);

    // Check that the player's coin total equals the expected value.
    observed = testG.coins;
    expected = 5;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Coins", observed, expected);
    
    // Check that the played card count stayed the same.
    observed = testG.playedCardCount;
    expected = G.playedCardCount;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Played Card Count", observed, expected);

    // Check that the discard stayed the same.
    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Discard Count", observed, expected);

    // Check that the player's deck count stayed the same.
    observed = testG.deckCount[currentPlayer];
    expected = G.deckCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Player Deck Count", observed, expected);

    // Check if the player's hand count stayed the same.
    observed = testG.handCount[currentPlayer];
    expected = G.handCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Hand Count", observed, expected);

    printf("\n\nEND OF UNIT TEST 3\n\n");

    return 0;
}