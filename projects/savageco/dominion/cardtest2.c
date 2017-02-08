/*
  cardtest2.c
  Corey Savage
  Assignment 3
  
  Description: Testing for Smithy Card
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void assert_true(int);

int main() {
	// Used from BetterTestCardDraw.c
	int expected, n, r, p, deckCount, discardCount, handCount;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	             remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf ("Testing Smithy Card.\n");

	initializeGame(2, k, 10, &G);
  
	// Set it to testing player's turn and put the Smithy Card in the player's hand
	G.whoseTurn = 0;
	G.hand[0][0] = smithy;
  
	// play Smithy Card
	playCard(0, -1, -1, -1, &G);

	// Testing players deck tests
	
	// Test 1 : handNum + newDraw - discard = newHandNum
	// Expected result : 5 + 3 - 1 = 7
	printf("Test 1: Correct number of cards in hand\n");
	expected = 7;
	printf("%d\n", G.handCount[0]);
	assert_true(G.handCount[0] == expected);
	
	// Test 2 : origPlayedCardCount + 1 = newPlayedCardCount
	// Expected result : 0 + 1 = 1
	printf("Test 2: Correct number of played cards\n");
	expected = 1;
	printf("%d\n", G.playedCardCount);
	assert_true(G.playedCardCount == expected);

	// Test 3 : deckCount - draw = newDeckCount
	// Expected result : 5 - 3 = 2
	printf("Test 3: Correct number of cards in deck\n");
	expected = 2;
	printf("%d\n", G.deckCount[0]);
	assert_true(G.deckCount[0] == expected);
	
	// Test 4 : discardCount + newDiscard = newDiscardCount
	// Expected result : 0 + 1 = 1
	printf("Test 4: Correct number of cards in discard pile\n");
	expected = 1;
	assert_true(G.discardCount[0] == expected);
	
	// Opponent players deck tests
	
	// Test 5 : handNum + newDraw - discard = newHandNum
	// Expected result : 5 + 0 - 0 = 5
	printf("Test 5: Correct number of cards in opponent hand\n");
	expected = 5;
	printf("%d\n", G.handCount[1]);
	assert_true(G.handCount[1] == expected);

	// Test 6 : deckCount - draw = newDeckCount
	// Expected result : 5 - 0 = 5
	printf("Test 6: Correct number of cards in deck\n");
	expected = 5;
	printf("%d\n", G.deckCount[1]);
	assert_true(G.deckCount[1] == expected);
	
	// Test 4 : discardCount + newDiscard = newDiscardCount
	// Expected result : 0 + 0 = 0
	printf("Test 4: Correct number of cards in discard pile\n");
	expected = 0;
	assert_true(G.discardCount[1] == expected);
}

// Used to print success or failure messages for test. Comparisons will be made within the 
// function parameters to test results. 
void assert_true(int bool) {
  
	if (bool != 0) {
		printf("      -Test Passed\n");
	}
	else {
		printf("      -Test Failed\n");
	}
}
