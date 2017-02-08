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

#define TESTUNIT "isGameOver"

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

	printf("----------------- Testing Unit: %s ----------------\n", TESTUNIT);


	// ----------- TEST 1: province empty --------------
	printf("TEST 1: province empty\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.supplyCount[province] = 0;
	
	printf("province count = %d, expected = %d\n", testG.supplyCount[province], 0);
	assert(isGameOver(&G) == 1);

	
	// ----------- TEST 2: 2 supply empty --------------
	printf("TEST 2: 2 supply empty\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.supplyCount[0] = 0;
	G.supplyCount[1] = 0;
	
	printf("supply count[0] = %d, expected = %d\n", testG.supplyCount[0], 0);
	printf("supply count[1] = %d, expected = %d\n", testG.supplyCount[0], 0);
	// assert(isGameOver(&G) == 0);


	// ----------- TEST 3: 3 supply empty --------------
	printf("TEST 3: 3 supply empty\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.supplyCount[0] = 0;
	G.supplyCount[1] = 0;
	G.supplyCount[2] = 0;

	printf("supply count[0] = %d, expected = %d\n", testG.supplyCount[0], 0);
	printf("supply count[1] = %d, expected = %d\n", testG.supplyCount[0], 0);
	printf("supply count[2] = %d, expected = %d\n", testG.supplyCount[0], 0);
	assert(isGameOver(&G) == 1);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTUNIT);


	return 0;
}


