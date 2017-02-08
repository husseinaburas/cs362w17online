// testing isGameOver()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define TESTUNIT "isGameOver()"

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

	printf("\n----------------- Testing Unit: %s ----------------\n", TESTUNIT);
	
	// ----   Test 1 - All Supply Piles Full 
	printf("TEST 1 - all supply piles full\n");
	// game should not be over = 0
	expected = 0;
	actual = isGameOver(&G);
	assertTest(actual, expected, 1);
	
	// ----   Test 2 - Supply of Province Cards Empty 
	printf("TEST 2 - supply of province cards empty\n");
	// game should be over = 1
	expected = 1;
	// set supply of province to 0
	G.supplyCount[province] = 0;
	actual = isGameOver(&G);
	assertTest(actual, expected, 2);

	// ----   Test 3 - 2 Supply Piles Empty 
	printf("TEST 3 - 2 supply piles empty\n");
	// game should not be over = 0
	expected = 0;
	// reset supply of province to 8
	G.supplyCount[province] = 8;
	// set supply of smithy and village to 0
	G.supplyCount[smithy] = 0;
	G.supplyCount[village] = 0;
 	actual = isGameOver(&G);
	assertTest(actual, expected, 3);

	// ----   Test 4 - 3 Supply Piles Empty 
	printf("TEST 4 - 3 supply piles empty\n");
	// game should be over = 1
	expected = 1;
	// set supply of estate to 0
	G.supplyCount[estate] = 0;
	actual = isGameOver(&G);
	assertTest(actual, expected, 4);
	
	// ----   Test 5 - 4 Supply Piles Empty 
	printf("TEST 5 - 4 supply piles empty\n");
	// game should be over = 1
	expected = 1;
	// set supply of council_room to 0
	G.supplyCount[council_room] = 0;
	actual = isGameOver(&G);
	assertTest(actual, expected, 5);

	// ----   Test 6 - All Supply Piles Empty Except Province 
	printf("TEST 6 - all supply piles empty except province\n");
	// game should be over = 1
	expected = 1;
	// empty all supply piles 
	int i;
	for (i = 0; i < 27; i++) 
		G.supplyCount[i] = 0;
	// reset supply of province
	G.supplyCount[province] = 8;
	actual = isGameOver(&G);
	assertTest(actual, expected, 6);
	
	printf("\n-------------- Testing Complete: %s ----------------\n\n", TESTUNIT);

  return 0;
}	