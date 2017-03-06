/*
  cardtest1.c
  Corey Savage
  Assignment 3
  
  Description: Testing for Adventurer Card
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void assert_true(int);

int main() {
	
	int expected;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	             remodel, smithy, village, baron, great_hall};

	struct gameState G;
	struct gameState G1;

	printf ("Testing Adventurer Card.\n");
	
	//
	// First Tests (No reshuffle needed for card effect)
	//
	initializeGame(2, k, 10, &G);
  
	// Set it to testing player's turn and put the Adventurer Card in the player's hand
	G.whoseTurn = 0;
	G.hand[0][0] = adventurer;
	
	G.deck[0][0] = silver;
	G.deck[0][1] = estate;
	G.deck[0][2] = estate;
	G.deck[0][3] = gold;
	G.deck[0][4] = estate;
	
  
	// play Adventurer Card
	playCard(0, -1, -1, -1, &G);
	
	// Test 1 : handNum + newDraw - discard = newHandNum
	// Expected result : 5 + 2 - 1 = 6
	printf("Test 1: Correct number of cards in hand");
	expected = 6;
	assert_true(G.handCount[0] == expected);
	
	// Test 2 : origPlayedCardCount + 1 = newPlayedCardCount
	// Expected result : 0 + 1 = 1
	printf("Test 2: Correct number of played cards");
	expected = 1;
	assert_true(G.playedCardCount == expected);

	// Test 3 : deckCount - draw = newDeckCount
	// Expected result : 5 - 4 = 1
	printf("Test 3: Correct number of cards in deck");
	expected = 1;
	assert_true(G.deckCount[0] == expected);
	
	// Test 4 : discardCount + newDiscard = newDiscardCount
	// Expected result : 0 + 3 = 3
	printf("Test 4: Correct number of cards in discard pile");
	expected = 3;
	assert_true(G.discardCount[0] == expected);
	
	// Opponent players deck tests
	
	// Test 5 : handNum + newDraw - discard = newHandNum
	// Expected result : 5 + 0 - 0 = 5
	printf("Test 5: Correct number of cards in opponent hand");
	expected = 5;
	assert_true(G.handCount[1] == expected);

	// Test 6 : deckCount - draw = newDeckCount
	// Expected result : 5 - 0 = 5
	printf("Test 6: Correct number of cards in deck");
	expected = 5;
	assert_true(G.deckCount[1] == expected);
	
	// Test 4 : discardCount + newDiscard = newDiscardCount
	// Expected result : 0 + 0 = 0
	printf("Test 7: Correct number of cards in discard pile");
	expected = 0;
	assert_true(G.discardCount[1] == expected);
	
    printf("\nSecond Tests\n");
	//
	//  Second Tests (Reshuffle needed for card effect)
	//
	initializeGame(2, k, 10, &G1);
	
	// Set it to testing player's turn and put the Adventurer Card in the player's hand
	G1.whoseTurn = 0;
	G1.hand[0][0] = adventurer;
	
	G1.deck[0][0] = estate;
	G1.deck[0][1] = estate;
	G1.deck[0][2] = estate;
	G1.deck[0][3] = gold;
	G1.deck[0][4] = estate;

	G1.discard[0][0] = gold;
	
  
	// play Adventurer Card
	playCard(0, -1, -1, -1, &G1);

	// Test 5 : handNum + newDraw - discard = newHandNum
	// Expected result : 5 + 2 - 1 = 6
	printf("Test 1: Correct number of cards in hand");
	expected = 6;
	assert_true(G1.handCount[0] == expected);
	
	// Test 6 : origPlayedCardCount + 1 = newPlayedCardCount
	// Expected result : 0 + 1 = 1
	printf("Test 2: Correct number of played cards");
	expected = 1;
	assert_true(G1.playedCardCount == expected);
	
	// Opponent players deck tests
    printf("\nOpponents deck tests \n");
	
	// Test 7 : handNum + newDraw - discard = newHandNum
	// Expected result : 5 + 0 - 0 = 5
	printf("Test 1: Correct number of cards in opponent hand");
	expected = 5;
	assert_true(G1.handCount[1] == expected);

	// Test 8 : deckCount - draw = newDeckCount
	// Expected result : 5 - 0 = 5
	printf("Test 2: Correct number of cards in deck");
	expected = 5;
	assert_true(G1.deckCount[1] == expected);
	
	// Test 9 : discardCount + newDiscard = newDiscardCount
	// Expected result : 0 + 0 = 0
	printf("Test 3: Correct number of cards in discard pile");
	expected = 0;
	assert_true(G1.discardCount[1] == expected);
}



// Used to print success or failure messages for test. Comparisons will be made within the 
// function parameters to test results. 
void assert_true(int bool) {
  
	if (bool != 0) {
		printf("      -Test Passed");
	}
	else {
		printf("      -Test Failed");
	}
}
