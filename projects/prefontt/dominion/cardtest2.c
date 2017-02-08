/*
 * This is the unit test for the Adventurer card
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {

	int handpos = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;
	int i;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	int numPlayers = 2;
	int seed = 10;
	int preTreasureCount = 0;
	int postTreasureCount = 0;

	initializeGame(numPlayers, k, seed, &G);
	
	printf("++++++++++++ TESTING Adventurer CARD ++++++++++++++++\n");

	printf("Testing Happy Path\n");

	memcpy(&testG, &G, sizeof(struct gameState));

	for(i = 0; i < testG.handCount[0]; i++)
	{
		if(testG.hand[0][i] == copper || testG.hand[0][i] == silver || testG.hand[0][i] == gold)
		{
			preTreasureCount++;
		}
		
	}

	for(i = 0; i < testG.deckCount[0]; i++)
	{
		testG.deck[0][i] = estate;
	}
	
	printf("The following tests have the remainder of the deck only have estates\n");
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Starting Test 1: player 0 handcount\n");
	printf("hand count = %d, expected = %d\n", testG.handCount[0], G.handCount[0]);
	assertTrue(testG.handCount[0], 5);
	
	printf("-------------------------------------------------------------------------------------\n");
	
	printf("Starting Test 2: player 0 deck count\n");
	printf("Deck count of player = %d, expected = %d\n", testG.deckCount[0], 0);
	assertTrue(testG.deckCount[0], 0);
	
	printf("-------------------------------------------------------------------------------------\n");
	
	printf("Starting Test 3: player discards correct amount\n");
	printf("cards discarded = %d, expected = 5\n", testG.discardCount[0]);
	assertTrue(testG.discardCount[0], 5);
	
	for(i = 0; i < testG.handCount[0]; i++)
	{
		if(testG.hand[0][i] == copper || testG.hand[0][i] == silver || testG.hand[0][i] == gold)
		{
			postTreasureCount++;
		}
	}
	printf("Starting Test 4: player has correct amount of treasure cards\n");
	printf("Treasure count of player = %d, expected = %d\n", postTreasureCount, preTreasureCount);
	assertTrue(postTreasureCount, preTreasureCount);
	
	printf("-------------------------------------------------------------------------------------\n");
	
	
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Testing happy path of Adventurer card\n");
	
	printf("Starting Test 1: player 1 deck count\n");
	printf("Deck count of opponent = %d, expected = %d\n", testG.deckCount[1], G.deckCount[1]);
	assertTrue(testG.deckCount[1], 10);
	
	printf("-------------------------------------------------------------------------------------\n");
	
	printf("Starting Test 2: player gains 2 treasure cards\n");
	for(i = 0; i < testG.handCount[0]; i++)
	{
		if(testG.hand[0][i] == copper || testG.hand[0][i] == silver || testG.hand[0][i] == gold)
		{
			postTreasureCount++;
		}
	}
	printf("Treasure count of player = %d, expected = %d\n", postTreasureCount, preTreasureCount + 2);
	assertTrue(postTreasureCount, preTreasureCount + 2);
	
	printf("-------------------------------------------------------------------------------------\n");
	
	printf("Starting Test 3: player gains no actions\n");
	printf("Actions count of player = %d, expected = %d\n", testG.numActions, 1);
	assertTrue(testG.numActions, G.numActions);
	
	printf("-------------------------------------------------------------------------------------\n");

	printf("Starting Test 4: player discards correct amount\n");
	printf("cards discarded = %d, expected = 2\n", testG.discardCount[0]);
	assertTrue(testG.discardCount[0], 0);

	printf("-------------------------------------------------------------------------------------\n");

	printf("Starting Test 5: player gains no buys\n");
	printf("Number of buys for player = %d, expected = 1\n", testG.numBuys);
	assertTrue(testG.numBuys, 1);
	
	printf("-------------------------------------------------------------------------------------\n");

	printf("Starting Test 6: player gains no coins\n");
	printf("Coin count of player = %d, expected = %d\n", testG.coins, G.coins);
	assertTrue(testG.coins, G.coins);
	
	printf("-------------------------------------------------------------------------------------\n");
	
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
