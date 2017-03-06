/***************************************
* Name: James Stewart
* Date: 1/31/2017
* File: cardtest1.c
* Description: Tests the discardCard() Function
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
    int observed, expected, i;
    int seed = 5;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int currentPlayer = 1;

	void process(int trashed, int discardPos){
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		printf("Player %d Deck Count: %d\n\n", currentPlayer, G.deckCount[currentPlayer]);
		discardCard(discardPos, currentPlayer, &testG, trashed);
			
		observed = testG.handCount[currentPlayer];
		expected = G.handCount[currentPlayer] - 1;
		if(observed == expected){testResult = PASS;}
		else{testResult = FAIL;}
		assertTrue(testResult, "Hand Count", observed, expected);

		observed = testG.playedCardCount;
		expected = G.playedCardCount;
		if(observed == expected){testResult = PASS;}
		else{testResult = FAIL;}
		assertTrue(testResult, "Played Cards", observed, expected);

		observed = testG.discardCount[currentPlayer];
		expected = G.discardCount[currentPlayer] + 1;
		if(observed == expected){testResult = PASS;}
		else{testResult = FAIL;}
		assertTrue(testResult, "Discards", observed, expected);

		observed = testG.deckCount[currentPlayer];
		expected = G.deckCount[currentPlayer];
		if(observed == expected){testResult = PASS;}
		else{testResult = FAIL;}
		assertTrue(testResult, "Deck Count", observed, expected);
	}
	
	initializeGame(numPlayers, k, seed, &G);
	printf("\n\n----------------- TESTING discardCard() FUNCTION -----------------\n\n");
    printf("TEST 1: Discard a card (not trashed)\n");
	process(0,2);

    printf("\nTEST 2: Discard a card (trashed)\n");
	process(1,2);

    printf("\nTEST 3: Try discard from empty hand\n");
    for(i = 0; i < G.handCount[currentPlayer]; i++){
        G.hand[currentPlayer][i] = -1;
    }
    G.handCount[currentPlayer] = 0;
	process(0,2);

    printf(" >>>>> SUCCESS: Testing discardCard() complete <<<<<\n\n");

    return 0;
}