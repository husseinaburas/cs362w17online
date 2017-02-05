/*********************************************************************
unittest2.c

Author: David Moon
Date: 2-1-2017
Description:
    This unit test will test the discardCard() function in dominion.c.
    The following are key points the test will check:
    - The player's hand count is decremented by 1 after discard
    - The player's discard count is incremented by 1 after discard
    - The number of cards in a player's hand does not exceed the max allowed
    - The number of cards in a player's hand is never less than 0
    - No state changes should occur for other players
    - The deck count does not change
    - Played card pile should increase by 1 after a trashed card

Note: Some skeleton code for game setup was taken from cardtest4.c,
    which was posted to the OSU CS-362 course web page.

Include the following lines in your makefile:

unittest2: unittest2.c dominion.o rngs.o
    gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

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

    int discardHandPos = 0;
    int currentPlayer = 1;
    int trashFlag;
    int i;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    printf("\n\n############# TESTING discardCard() FUNCTION ###############\n");


    printf("TEST 1: Discard a card (not trashed).\n\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    trashFlag = 0;  //not trashed
    discardHandPos = 2;
    // currentPlayer = 1;
    printf("player %d deck count: %d\n", currentPlayer, G.deckCount[currentPlayer]);

    // Discard the cardToDiscard
    discardCard(discardHandPos, currentPlayer, &testG, trashFlag);
        
    // Check if the player's hand count was decreased by 1.
    observed = testG.handCount[currentPlayer];
    expected = G.handCount[currentPlayer] - 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Hand Count", observed, expected);

    // Check that the played card count stayed the same.
    observed = testG.playedCardCount;
    expected = G.playedCardCount;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Played Card Count", observed, expected);

    // Check that the discard count was increased by 1.
    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer] + 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Discard Count", observed, expected);

    // Check that the player's deck count stayed the same.
    observed = testG.deckCount[currentPlayer];
    expected = G.deckCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Player Deck Count", observed, expected);


    printf("\n\nTEST 2: Discard a card and trash it.\n\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    trashFlag = 1;  //trashed
    discardHandPos = 2;

    // Discard the cardToDiscard
    discardCard(discardHandPos, currentPlayer, &testG, trashFlag);
        
    // Check if the player's hand count was decreased by 1.
    observed = testG.handCount[currentPlayer];
    expected = G.handCount[currentPlayer] - 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Hand Count", observed, expected);

    // Check that the played card count increased by 1.
    observed = testG.playedCardCount;
    expected = G.playedCardCount + 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Played Card Count", observed, expected);

    // Check that the discard count stayed the same.
    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Discard Count", observed, expected);

    // Check that the player's deck count decreased by 1.
    observed = testG.deckCount[currentPlayer];
    expected = G.deckCount[currentPlayer] - 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Player Deck Count", observed, expected);


    printf("\n\nTEST 3: Attempt to discard with an empty hand.\n\n");
    
    // Empty current player's hand
    for(i = 0; i < G.handCount[currentPlayer]; i++){
        G.hand[currentPlayer][i] = -1;
    }

    // Set current player's hand count to 0
    G.handCount[currentPlayer] = 0;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    trashFlag = 0;  //not trashed
    discardHandPos = 2;

    // Discard the cardToDiscard
    discardCard(discardHandPos, currentPlayer, &testG, trashFlag);
        
    // Check if the player's hand count stayed the same.
    observed = testG.handCount[currentPlayer];
    expected = G.handCount[currentPlayer];
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Hand Count", observed, expected);

    // Check that the played card count stayed the same.
    observed = testG.playedCardCount;
    expected = G.playedCardCount;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Played Card Count", observed, expected);

    // Check that the discard count stayed the same.
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

    printf("\n\nEND OF UNIT TEST 2\n\n");

    return 0;
}