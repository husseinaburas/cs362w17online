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
	
	int expected, n, r, p, deckCount, discardCount, handCount;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	             remodel, smithy, village, baron, great_hall};

	struct gameState G;
	struct gameState G1;

	printf ("Testing Adventurer Card.\n");

	// First Tests (
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
	
	initializeGame(2, k, 10, &G1);
	
	// Set it to testing player's turn and put the Adventurer Card in the player's hand
	G1.whoseTurn = 0;
	G1.hand[0][0] = adventurer;
	
	G1.deck[0][0] = estate;
	G1.deck[0][1] = estate;
	G1.deck[0][2] = estate;
	G1.deck[0][3] = gold;
	G1.deck[0][4] = estate;
	
  
	// play Adventurer Card
	playCard(0, -1, -1, -1, &G1);

	// Testing players deck tests



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
