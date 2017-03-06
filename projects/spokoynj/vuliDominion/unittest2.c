// testing fullDeckCount()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define TESTUNIT "fullDeckCount()"

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
	
	int k[10] = {adventurer, council_room, feast, gardens, mine, 
				 remodel, smithy, village, baron, great_hall};
				 
	initializeGame(2, k, 1000, &G);

	int actual, expected;
	int player = 0;
	
	int i;
	
	// fill player's hand 
	for (i = 0; i < 10; i++) 
		G.hand[player][i] = province;

	G.handCount[player] = 10;
	
	G.hand[player][1] = gold;
	G.hand[player][2] = gold;
	G.hand[player][3] = feast;
	G.hand[player][4] = feast;
	G.hand[player][5] = feast;
	G.hand[player][6] = estate;
	
	// fill player's deck 
	for (i = 0; i < 20; i++) 
		G.deck[player][i] = duchy;

	G.deckCount[player] = 20;
	
	G.deck[player][1] = gold;
	G.deck[player][2] = gold;
	G.deck[player][3] = mine;
	G.deck[player][4] = feast;
	G.deck[player][5] = feast;
	G.deck[player][6] = estate;
	
	// fill player's discard with estate cards
	for (i = 0; i < 20; i++) 
		G.discard[player][i] = estate;

	G.discardCount[player] = 20;
	
	G.discard[player][1] = gold;
	G.discard[player][2] = gold;
	G.discard[player][3] = mine;
	G.discard[player][4] = mine;
	G.discard[player][5] = mine;
	G.discard[player][6] = mine;
	
	printf("\n----------------- Testing Unit: %s ----------------\n", TESTUNIT);

	// ----   Test 1 - Count Silver Cards
	printf("TEST 1 - count silver cards\n");
	expected = 0;
	actual = fullDeckCount(0, silver, &G);
	assertTest(actual, expected, 1);

	// ----   Test 2 - Count Gold Cards 
	printf("TEST 2 - count gold cards\n");
	expected = 6;
	actual = fullDeckCount(0, gold, &G);
	assertTest(actual, expected, 2);

	// ----   Test 3 - Count Feast Cards 
	printf("TEST 3 - count feast cards\n");
	expected = 5;
	actual = fullDeckCount(0, feast, &G);
	assertTest(actual, expected, 3);

	// ----   Test 4 - Count Mine Cards 
	printf("TEST 4 - count mine cards\n");
 	expected = 5;
	actual = fullDeckCount(0, mine, &G);
	assertTest(actual, expected, 4);

	// ----   Test 5 - Count Province Cards 
	printf("TEST 5 - count province cards\n");
	expected = 4;
	actual = fullDeckCount(0, province, &G);
	assertTest(actual, expected, 5);

	// ----   Test 6 - Count Duchy Cards 
	printf("TEST 6 - count duchy cards\n");
	expected = 14;
	actual = fullDeckCount(0, duchy, &G);
	assertTest(actual, expected, 6);

	// ----   Test 7 - Count Estate Cards 
	printf("TEST 7 - count estate cards\n");
	expected = 16;
	actual = fullDeckCount(0, estate, &G);
	assertTest(actual, expected, 7);
	
	// ----   Test 8 - Count Cutpurse Cards 
	printf("TEST 8 - count cutpurse cards\n");
	expected = 0;
	actual = fullDeckCount(0, cutpurse, &G);
	assertTest(actual, expected, 8);

	printf("\n-------------- Testing Complete: %s ----------------\n\n", TESTUNIT);

	return 0;
}
