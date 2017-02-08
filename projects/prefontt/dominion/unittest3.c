/* This unit test will test the buyCard function */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
	
	int i;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy, council_room};

	int numPlayers = 2;
	int seed = 10;

	initializeGame(numPlayers, k, seed, &G);

	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("++++++++++++ TESTING buyCard Function ++++++++++++++++\n\n\n");

	printf("Happy path of buyCard\n");
	int originalCoin = testG.coins;
	int originalBuys = testG.numBuys;
	int result = buyCard(5, &testG);
	printf("result = %d, expected = %d\n", result, 0);
	assertTrue(result, 0);
	
	printf("------------------------------------------------------------------\n");
	
	testG.numBuys = 1;
	printf("trying to buy a card without enough coins\n");
	result = buyCard(5, &testG);
	printf("result = %d, expected = %d\n", result, -1);
	assertTrue(result, -1);

	
	printf("------------------------------------------------------------------\n");
	
	// no buys
	testG.numBuys = 0;
	printf("trying to buy a card without enough buys\n");
	result = buyCard(5, &testG);
	printf("result = %d, expected = %d\n", result, -1);
	assertTrue(result, -1);

	printf("------------------------------------------------------------------\n");
	
	// buy twice enough
	testG.numBuys = 2;
	testG.coins = 12;
	printf("trying to buy a buy the first time with enough buys\n");
	result = buyCard(5, &testG);
	printf("result = %d, expected = %d\n", result, 0);
	assertTrue(result, 0);
	result = buyCard(5, &testG);
	printf("trying to buy a second time with enough buys\n");
	printf("result = %d, expected = %d\n", result, 0);
	assertTrue(result, 0);
	
	printf("------------------------------------------------------------------\n");
	
	// buy twice not enough
	testG.numBuys = 1;
	testG.coins = 12;
	printf("trying to buy a card the first time with enough buys\n");
	result = buyCard(5, &testG);
	printf("result = %d, expected %d\n", result, 0);
	assertTrue(result, 0);
	result = buyCard(5, &testG);
	printf("trying to but a second time without enough buys\n");
	printf("result = %d, expected = %d\n", result, -1);
	assertTrue(result, -1);
	
	printf("------------------------------------------------------------------\n");
	
	// no supply
	testG.numBuys = 1;
	testG.coins = 12;
	testG.supplyCount[5] = 0;
	printf("trying to buy a card without enough supply\n");
	result = buyCard(5, &testG);
	printf("result = %d, expected = %d\n", result, -1);
	assertTrue(result, -1);

	printf("------------------------------------------------------------------\n");
	
	// happy path
	testG.numBuys = 1;
	testG.supplyCount[5] = 10;
	printf("Happy path of buyCard with multiple tests of game state\n");
	testG.coins = 6;
	originalCoin = testG.coins;
	originalBuys = testG.numBuys;
	result = buyCard(5, &testG);
	printf("result = %d, expected = %d\n", result, 0);
	assertTrue(result, 0);
	printf("phase = %d, expected = %d\n", testG.phase, 1);
	int cost = getCost(5);
	printf("coins before buying = %d, cost of card = %d, expected coins after buy = %d\n", originalCoin, cost, (originalCoin - cost));
	assertTrue(testG.coins, (originalCoin - cost));
	printf("number of buys before buying card = %d, number of buys after = %d\n", originalBuys, testG.numBuys);
	assertTrue(testG.numBuys, 0);
	int discarded = testG.discardCount[0];
	printf("card discarded = %d, expected = %d\n", discarded, 5);
	assertTrue(discarded, 5);
	
	
	printf("Testing supply count\n");
	
	int unchanged = 1;
	for(i = 0; i < 17; i++)
	{
		if(G.supplyCount[i] != testG.supplyCount[i])
		{
			printf("supply of card at index %d has changed\n", i);
			unchanged = 0;
		}
		
	}
	if(unchanged)
	{
		printf("Supply piles have not changed\n");
	}
	
	return 0;
}
