/*********************************************
*   Format used from cardtest4.c example
*
*********************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTUNIT "buyCard"

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 6;
	printf("----------------- Testing Unit: %s ----------------\n", TESTUNIT);

	// ----------- TEST 1: numBuys < 1 --------------
	printf("TEST 1: numBuys < 1\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.numBuys = 0;

	printf("Buy num = %d, expected = %d\n", testG.numBuys, G.numBuys);
	// assert(buyCard(1, &G) == -1);
	

	// ----------- TEST 2: supplyCount < 1 --------------
	printf("TEST 2: supplyCount < 1\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.supplyCount[adventurer] = 0;

	printf("supplyCount = %d, expected = %d\n", testG.supplyCount[adventurer], G.supplyCount[adventurer] );
	// assert(buyCard(0, &G) == -1);

	// ----------- TEST 3: coin < cost --------------
	printf("TEST 3: coin < cost\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.coins = 0;

	printf("coins = %d, expected = %d\n", testG.coins, getCost(1));
	// assert(buyCard(0, &G) == -1);


	// ----------- TEST 4: cost < coin --------------
	printf("TEST 4: cost < coin\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("coins = %d, expected = %d\n", testG.coins, getCost(adventurer));
	buyCard(adventurer, &G);
	// assert(buyCard(adventurer, &G) != -1);
	// assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	printf("coins = %d, expected = %d\n", testG.coins - getCost(adventurer), testG.coins - 6);
	printf("Buy num = %d, expected = %d\n", testG.numBuys, G.numBuys);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTUNIT);


	return 0;
}


