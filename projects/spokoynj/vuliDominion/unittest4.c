// testing buyCard()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define TESTUNIT "buyCard()"

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

	// ----   Test 1 - numBuys 0
	printf("TEST 1 - player has no buys\n");
	// number of buys insufficient = -1
	expected = -1;
	// set numBuys to 0
	G.numBuys = 0;
	// set coins to 15
	G.coins = 15;
	// try to buy something costing 1+ (council_room)
	actual = buyCard(8, &G);
	assertTest(actual, expected, 1);

	// ----   Test 2 - check supplyCount 
	printf("TEST 2 - supply count is unaffected by failed buy\n");
	// supply of council_rooms was 10 before buyCard was called = unchanged
	expected = 10;
	actual = G.supplyCount[8];
	assertTest(actual, expected, 2);

	// ----   Test 3 - coins 0
	printf("TEST 3 - player has no coins\n");
	// number of coins insufficient = -1
	expected = -1;
	// reset numBuys to 1
	G.numBuys = 1;
	// set coins to 0
	G.coins = 0;
	// try to buy something costing 1+ (council_room)
	actual = buyCard(8, &G);
	assertTest(actual, expected, 3);

	// ----   Test 4 - check supplyCount 
	printf("TEST 4 - supply count is unaffected by failed buy\n");
	// supply of council_rooms was 10 before buyCard was called = unchanged
	expected = 10;
	actual = G.supplyCount[8];
	assertTest(actual, expected, 4);

	// ----   Test 5 - supplyCount 0 
	printf("TEST 5 - the card to be bought has no supply\n");
	// supply insufficient = -1
	expected = -1;
	// reset numBuys to 1
	G.numBuys = 1;
	// set coins to 15
	G.coins = 15;
	// set supply count to 0 (council_rooms)
	G.supplyCount[8] = 0;
	// try to buy (council_room)
	actual = buyCard(8, &G);
	assertTest(actual, expected, 5);

	// ----   Test 6 - check supplyCount 
	printf("TEST 6 - supply count is unaffected by failed buy\n");
	// supply of council_rooms was 0 before buyCard was called = unchanged
	expected = 0;
	actual = G.supplyCount[8];
	assertTest(actual, expected, 6);

	// ----   Test 7 - sufficient buys, coins, supply 
	printf("TEST 7 - player has buys, coins, card has supply\n");
	// buys, coins, supply sufficient = 0
	expected = 0;
	// reset numBuys to 1
	G.numBuys = 1;
	// reset coins to 15
	G.coins = 15;
	// reset supply count to 10 (council_rooms)
	G.supplyCount[8] = 10;
	// try to buy (council_room)
	actual = buyCard(8, &G);
	assertTest(actual, expected, 7);

	// ----   Test 8 - check supplyCount 
	printf("TEST 8 - supply count -1\n");
	// start with 10 cards in supply - 1 = 9
	expected = 9;
	actual = G.supplyCount[8];
	assertTest(actual, expected, 8);

	// ----   Test 9 - check numBuys 
	printf("TEST 9 - number of buys -1\n");
	// start with 1 buy - 1 = 0
	expected = 0;
	actual = G.numBuys;
	assertTest(actual, expected, 9);

	// ----   Test 10 - check coins 
	printf("TEST 10 - coins -cost\n");
	// start with 15 coins - 5 = 10
	expected = 10;
	actual = G.coins;
	assertTest(actual, expected, 10);

	printf("\n-------------- Testing Complete: %s ----------------\n\n", TESTUNIT);

	return 0;
}