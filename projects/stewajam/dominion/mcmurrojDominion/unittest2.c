/***************************************
* Name: James Stewart
* Date: 1/31/2017
* File: cardtest1.c
* Description: Tests the updateCoins() Function
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
    int observed, i, bonus, card1, card2, card3, card4, card5;
    int seed = 5;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int currentPlayer = whoseTurn(&G);
	
	void newHand(){
		// copy the game state to a test case
		G.hand[currentPlayer][0] = card1;
		G.hand[currentPlayer][1] = card2;
		G.hand[currentPlayer][2] = card3;
		G.hand[currentPlayer][3] = card4;
		G.hand[currentPlayer][4] = card5;
		G.handCount[currentPlayer] = 5;
		memcpy(&testG, &G, sizeof(struct gameState));
		printf("\nPlayer hand: \t");
		for(i = 0; i < G.handCount[currentPlayer]; i++){
			printf("%d ", G.hand[currentPlayer][i]);
		}
		printf("\nExpected hand: \t%d %d %d %d %d\n\n", card1, card2, card3, card4, card5);
		updateCoins(currentPlayer, &testG, bonus);
	}
	
	void process(int expected){
		observed = testG.coins;
		if(observed == expected){testResult = PASS;}
		else{testResult = FAIL;}
		assertTrue(testResult, "Coins", observed, expected);

		observed = testG.playedCardCount;
		expected = G.playedCardCount;
		if(observed == expected){testResult = PASS;}
		else{testResult = FAIL;}
		assertTrue(testResult, "Played Cards", observed, expected);

		observed = testG.discardCount[currentPlayer];
		expected = G.discardCount[currentPlayer];
		if(observed == expected){testResult = PASS;}
		else{testResult = FAIL;}
		assertTrue(testResult, "Discards", observed, expected);

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
	}
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    printf("\n\n----------------- TESTING updateCoins() FUNCTION -----------------\n\n");
    printf("TEST 1: 1 copper, 1 silver, 1 gold, 0 bonus\n");
    card1 = copper;
    card2 = silver;
    card3 = gold;
    card4 = adventurer;
    card5 = council_room;
	bonus = 0;
	newHand();
	process(6);

    printf("\nTEST 2: 3 copper, bonus 2\n");
    card1 = copper;
    card2 = smithy;
    card3 = copper;
    card4 = estate;
    card5 = copper;
	bonus = 2;
	newHand();
	process(5);

    printf("\nTEST 3: 0 treasure, bonus 5\n");
    card1 = province;
    card2 = smithy;
    card3 = feast;
    card4 = estate;
    card5 = tribute;
	bonus = 5;
	newHand();
	process(5);

	printf(" >>>>> SUCCESS: Testing updateCoins() complete <<<<<\n\n");

    return 0;
}