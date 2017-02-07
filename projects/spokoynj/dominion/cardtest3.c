// testing village card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define TESTCARD "village"

int assertTest(int actual, int expected, int testNo) {
	if (actual == expected) {
		printf("\tTEST %d SUCCESSFULLY COMPLETED\n",testNo);
		return 1;
	} 
	else {
		printf("\tTEST %d FAILED\n",testNo);
		printf("\tEXPECTED %d ---- ACTUAL %d\n",expected,actual);
		return 0;
	}
}

int main() {
	struct gameState G;
	struct gameState G1;
	struct gameState G2;
	struct gameState G3;
	
	int k[10] = {adventurer, council_room, feast, gardens, mine, 
				 remodel, smithy, village, baron, great_hall};
	
	initializeGame(2, k, 1000, &G);
	initializeGame(2, k, 1000, &G1);
	initializeGame(2, k, 1000, &G2);
	initializeGame(2, k, 1000, &G3);

	int actual, expected;
	int oHandCount, oDeckCount, oDiscardCount;
	int player = 0;
	int opponent = 1;

	// save opponent's hand, deck, discard counts
	oHandCount = G.handCount[1];
	oDeckCount = G.deckCount[1];
	oDiscardCount = G.discardCount[1];

	// set village as first card in player's hand
	G.hand[player][0] = village;
  
	// play village 
	playCard(0, -1, -1, -1, &G);
	
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("\n--Testing with Village as First Card in Player's Hand\n");
	
	// ----   TEST 1 - check numHandCards  
	printf("TEST 1 - cards in hand +0\n");
	// start with 5 cards in hand + 1 - 1 = 5
  	expected = 5;
	actual = numHandCards(&G);
	assertTest(actual, expected, 1);

	// ----   TEST 2 - check numActions 
	printf("TEST 2 - action count +1\n");
	// start with 1 action + 2 - 1 = 2
	expected = 2;
	actual = G.numActions;
	assertTest(actual, expected, 2);

	// ----  TEST 3 - check playedCardCount  
	printf("TEST 3 - played card count +1\n");
	// start with 0 played cards + 1 = 1
	expected = 1;
	actual = G.playedCardCount;
	assertTest(actual, expected, 3);

	// ----   TEST 4 - check playedCards  
	printf("TEST 4 - check village in played cards\n");
	// village card should be in playedCards array
	expected = 1;
	actual = 0;
	int i;
	for (i = 0; i < G.playedCardCount; i++) {
		if (G.playedCards[i] == village) 
			actual = 1;
	}
	assertTest(actual, expected, 4);
	
	// ----   TEST 5 - check deckCount  
	printf("TEST 5 - deck count -1\n");
	// start with 5 cards in deck - 1 = 4
	expected = 4;
	actual = G.deckCount[whoseTurn(&G)];
	assertTest(actual, expected, 5);
	
	printf("\n");

	// ----   TEST 6 - check getCost  
	printf("TEST 6 - village cost (3)\n");
	// cost = 3 coins
	expected = 3;
	actual = getCost(village);
	assertTest(actual, expected, 6);

	// ----   TEST 7 - check numBuys  
	printf("TEST 7 - number of buys +0\n");
	// start with 1 buy = unchanged
	expected = 1;
	actual = G.numBuys;
	assertTest(actual, expected, 7);
	
	printf("\n--Testing Opponent's State\n");

	// ----   TEST 8 - check opponent handCount  
	printf("TEST 8 - opponent hand count +0\n");
	// start with x cards in hand = unchanged
	expected = 0;
	actual = G.handCount[opponent] - oHandCount;
	assertTest(actual, expected, 8);

	// ----   TEST 9 - check opponent deckCount  
	printf("TEST 9 - opponent deck count +0\n");
	// start with x cards in deck = unchanged
	expected = 0;
	actual = G.deckCount[opponent] - oDeckCount;
	assertTest(actual, expected, 9);

	// ----   TEST 10 - check opponent discardCount  
	printf("TEST 10 - opponent discard count +0\n");
	// start with x cards in discard = unchanged
	expected = 0;
	actual = G.discardCount[opponent] - oDiscardCount;
	assertTest(actual, expected, 10);
	
	printf("\n--Testing with Village as Last Card in Player's Hand\n");
	
	// set village as last card in player's hand
	int pos = numHandCards(&G1) - 1;
	G1.hand[player][pos] = village;
	// play village
	playCard(pos, -1, -1, -1, &G1);

	// ----   TEST 11 - check numHandCards 	
	printf("TEST 11 - cards in hand +0\n");
	// start with 5 cards in hand + 1 - 1 = 5
  	expected = 5;
	actual = numHandCards(&G1);
	assertTest(actual, expected, 11);
	
	printf("\n--Testing with Empty Deck & Discard Piles\n");
	
	// set deck and discard pile to empty
	G2.deckCount[player] = 0;
	G2.discardCount[player] = 0;
	// set village as first card in player's hand
	G2.hand[player][0] = village;
	// play village
	playCard(0, -1, -1, -1, &G2);

	// ----   TEST 12 - check numHandCards 	
	printf("TEST 12 - cards in hand -1\n");
	// start with 5 cards in hand + 0 - 1 = 4
  	expected = 4;
	actual = numHandCards(&G2);
	assertTest(actual, expected, 12);
	
	printf("\n--Testing with Village as Only Card in Player's Hand\n");
	
	// set village as the only card in player's hand
	G3.handCount[player] = 1;
	G3.hand[player][0] = village;
	// play village
	playCard(0, -1, -1, -1, &G3);
	
	// ----   TEST 13 - check numHandCards 	
	printf("TEST 13 - cards in hand +0\n");
	// start with 1 card in hand + 1 - 1 = 1
  	expected = 1;
	actual = numHandCards(&G3);
	assertTest(actual, expected, 13);

	printf("\n-------------- Testing Complete: %s ----------------\n\n", TESTCARD);

  return 0;

}