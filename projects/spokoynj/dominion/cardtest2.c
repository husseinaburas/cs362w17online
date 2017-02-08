// testing adventurer card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define TESTCARD "adventurer"

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
	struct gameState G4;
	struct gameState G5;
	
	int k[10] = {adventurer, council_room, feast, gardens, mine, 
				 remodel, smithy, village, baron, great_hall};
				 
	initializeGame(2, k, 1000, &G);
	initializeGame(2, k, 1000, &G1);
	initializeGame(2, k, 1000, &G2);
	initializeGame(2, k, 1000, &G3);
	initializeGame(2, k, 1000, &G4);
	initializeGame(2, k, 1000, &G5);

	int actual, expected;
	int oHandCount, oDeckCount, oDiscardCount;
	int player = 0;
	int opponent = 1;
	int i;
	
	// save opponent's hand, deck, discard counts
	oHandCount = G.handCount[1];
	oDeckCount = G.deckCount[1];
	oDiscardCount = G.discardCount[1];

	// set adventurer as first card in player's hand
	G.hand[player][0] = adventurer;
	G1.hand[player][0] = adventurer;
	G2.hand[player][0] = adventurer;

	// set all cards in deck (G)
	for (i = 0; i < 10; i++) 
		G.deck[player][i] = gold;

	G.deckCount[player] = 10;

	G.deck[player][1] = estate;
	G.deck[player][3] = estate;
	G.deck[player][5] = estate;
	G.deck[player][7] = estate;
	G.deck[player][8] = estate;
	G.deck[player][9] = estate;

	// play adventurer (G)
    playCard(0, -1, -1, -1, &G);

	// set all cards in deck (G1)
	for (i = 0; i < 10; i++) 
		G1.deck[player][i] = estate;

	G1.deckCount[player] = 10;

	// play adventurer (G1)
	playCard(0, -1, -1, -1, &G1);
	
	// set all cards in deck (G2)
	for (i = 0; i < 10; i++) 
		G2.deck[player][i] = estate;

	G2.deckCount[player] = 10;
	
	G2.deck[player][7] = copper;

	// play adventurer (G2)
	playCard(0, -1, -1, -1, &G2);

	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("--Testing with >2 Treasure Cards in Deck\n");

	// ----   TEST 1 - check numHandCards  
	printf("TEST 1 - cards in hand +1\n");
	// start with 5 cards in hand + 2 - 1 = 6
  	expected = 6;
	actual = numHandCards(&G);
	assertTest(actual, expected, 1);

	// ----   TEST 2 - check numActions 
	printf("TEST 2 - action count -1\n");
	// start with 1 action - 1 = 0
	expected = 0;
	actual = G.numActions;
	assertTest(actual, expected, 2);

	// ----  TEST 3 - check playedCardCount  
	printf("TEST 3 - played card count +1\n");
	// start with 0 played cards + 1 = 1
	expected = 1;
	actual = G.playedCardCount;
	assertTest(actual, expected, 3);

	// ----   TEST 4 - check playedCards  
	printf("TEST 4 - check adventurer in played cards\n");
	// adventurer card should be in playedCards array
	expected = 1;
	actual = 0;
	for (i = 0; i < G.playedCardCount; i++) {
		if (G.playedCards[i] == adventurer) 
			actual = 1;
	}
	assertTest(actual, expected, 4);

	// ----   TEST 5 - check discardCount  
	printf("TEST 5 - discard count +5\n");
	// start with 0 cards in discard + 4(non-treasure) + 1 = 5
    expected = 5;
	actual = G.discardCount[whoseTurn(&G)];
	assertTest(actual, expected, 5);

	printf("\n--Testing with 0 Treasure Cards in Deck\n");

	// ----   Test 6 - check numHandCards  
	printf("TEST 6 - cards in hand -1\n");
	// start with 5 cards in hand - 1 = 4
	expected = 4;
	actual = numHandCards(&G1);
	assertTest(actual, expected, 6);
	
	// ----   TEST 7 - check numActions 
	printf("TEST 7 - action count -1\n");
	// start with 1 action - 1 = 0
	expected = 0;
	actual = G1.numActions;
	assertTest(actual, expected, 7);

	// ----  TEST 8 - check playedCardCount  
	printf("TEST 8 - played card count +1\n");
	// start with 0 played cards + 1 = 1
	expected = 1;
	actual = G1.playedCardCount;
	assertTest(actual, expected, 8);
  
	// ----   TEST 9 - check playedCards  
	printf("TEST 9 - check adventurer in played cards\n");
	// adventurer card should be in playedCards array
	expected = 1;
	actual = 0;
	for (i = 0; i < G1.playedCardCount; i++) {
		if (G1.playedCards[i] == adventurer) 
			actual = 1;
	}
	assertTest(actual, expected, 9);

	// ----   TEST 10 - check discardCount  
	printf("TEST 10 - discard count +11\n");
	// start with 0 cards in discard + 10(non-treasure) + 1 = 11
    expected = 11;
	actual = G1.discardCount[whoseTurn(&G1)];
	assertTest(actual, expected, 10);
	
	printf("\n--Testing with 1 Treasure Card in Deck\n");

	// ----   Test 11 - check numHandCards  
	printf("TEST 11 - cards in hand +0\n");
	// start with 5 cards in hand + 1 - 1 = 5
	expected = 5;
	actual = numHandCards(&G2);
	assertTest(actual, expected, 11);
	
	// ----   TEST 12 - check numActions 
	printf("TEST 12 - action count -1\n");
	// start with 1 action - 1 = 0
	expected = 0;
	actual = G2.numActions;
	assertTest(actual, expected, 12);

	// ----  TEST 13 - check playedCardCount  
	printf("TEST 13 - played card count +1\n");
	// start with 0 played cards + 1 = 1
	expected = 1;
	actual = G2.playedCardCount;
	assertTest(actual, expected, 13);
  
	// ----   TEST 14 - check playedCards  
	printf("TEST 14 - check adventurer in played cards\n");
	// adventurer card should be in playedCards array
	expected = 1;
	actual = 0;
	for (i = 0; i < G2.playedCardCount; i++) {
		if (G2.playedCards[i] == adventurer) 
			actual = 1;
	}
	assertTest(actual, expected, 14);

	// ----   TEST 15 - check discardCount  
	printf("TEST 15 - discard count +10\n");
	// start with 0 cards in discard + 9(non-treasure) + 1 = 10
    expected = 10;
	actual = G2.discardCount[whoseTurn(&G2)];
	assertTest(actual, expected, 15);
	
	printf("\n");

	// ----   TEST 16 - check getCost  
	printf("TEST 16 - adventurer cost (6)\n");
	// cost = 6 coins
	expected = 6;
	actual = getCost(adventurer);
	assertTest(actual, expected, 16);

	// ----   TEST 17 - check numBuys  
	printf("TEST 17 - number of buys +0\n");
	// start with 1 buy = unchanged
	expected = 1;
	actual = G.numBuys;
	assertTest(actual, expected, 17);
	
	printf("\n--Testing Opponent's State\n");

	// ----   TEST 18 - check opponent handCount  
	printf("TEST 18 - opponent hand count +0\n");
	// start with x cards in hand = unchanged
	expected = 0;
	actual = G.handCount[opponent] - oHandCount;
	assertTest(actual, expected, 18);

	// ----   TEST 19 - check opponent deckCount  
	printf("TEST 19 - opponent deck count +0\n");
	// start with x cards in deck = unchanged
	expected = 0;
	actual = G.deckCount[opponent] - oDeckCount;
	assertTest(actual, expected, 19);

	// ----   TEST 20 - check opponent discardCount  
	printf("TEST 20 - opponent discard count +0\n");
	// start with x cards in discard = unchanged
	expected = 0;
	actual = G.discardCount[opponent] - oDiscardCount;
	assertTest(actual, expected, 20);
	
	printf("\n--Testing with Adventurer as Last Card in Player's Hand\n");
	
	// set all cards in deck (G3)
	for (i = 0; i < 10; i++) 
		G3.deck[player][i] = silver;

	G3.deckCount[player] = 10;

	G3.deck[player][7] = estate;
	G3.deck[player][9] = estate;
	
	// set adventurer as last card in player's hand
	int pos = numHandCards(&G1) - 1;
	G3.hand[player][pos] = adventurer;
	// play adventurer
	playCard(pos, -1, -1, -1, &G3);

	// ----   TEST 21 - check numHandCards 	
	printf("TEST 21 - cards in hand +1\n");
	// start with 5 cards in hand + 2 - 1 = 6
  	expected = 6;
	actual = numHandCards(&G3);
	assertTest(actual, expected, 21);
	
	printf("\n--Testing with Empty Deck & Discard Piles\n");
	
	// set deck and discard pile to empty
	G4.deckCount[player] = 0;
	G4.discardCount[player] = 0;
	// set adventurer as first card in player's hand
	G4.hand[player][0] = adventurer;
	// play adventurer
	playCard(0, -1, -1, -1, &G4);

	// ----   TEST 22 - check numHandCards 	
	printf("TEST 22 - cards in hand -1\n");
	// start with 5 cards in hand + 0 - 1 = 4
  	expected = 4;
	actual = numHandCards(&G4);
	assertTest(actual, expected, 22);
	
	printf("\n--Testing with Adventurer as Only Card in Player's Hand\n");
	
	// set adventurer as the only card in player's hand
	G5.handCount[player] = 1;
	G5.hand[player][0] = adventurer;
	// play adventurer
	playCard(0, -1, -1, -1, &G5);
	
	// ----   TEST 23 - check numHandCards 	
	printf("TEST 23 - cards in hand +1\n");
	// start with 1 card in hand + 2 - 1 = 2
  	expected = 2;
	actual = numHandCards(&G5);
	assertTest(actual, expected, 23);

	printf("\n-------------- Testing Complete: %s ----------------\n\n", TESTCARD);

	return 0;
}
