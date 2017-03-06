/*This is the unit test for the Great Hall card
i */
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
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy, council_room};

	int numPlayers = 2;
	int seed = 10;

	initializeGame(numPlayers, k, seed, &G);
	
	printf("++++++++++++ TESTING Great Hall CARD ++++++++++++++++\n");

	memcpy(&testG, &G, sizeof(struct gameState));

	//cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);
	playGreatHall(0, handpos, &testG);
	
	
	printf("Starting Test 1: player 0 handcount\n");
	printf("hand count = %d, expected = %d\n", testG.handCount[0], G.handCount[0]);
	assertTrue(testG.handCount[0], G.handCount[0]);
	
	printf("-------------------------------------------------------------------------------------\n");
	
	printf("Starting Test 2: player 0 deck count\n");
	printf("Deck count of player after card played: %d, expected = %d\n", testG.deckCount[0], G.deckCount[0] - 1);
	assertTrue(testG.deckCount[0], G.deckCount[0] - 1);
	
	printf("-------------------------------------------------------------------------------------\n");
	
	printf("Starting Test 3: player 1 deck count\n");
	printf("Deck count of opponent = %d, expected = %d\n", testG.deckCount[1], G.deckCount[1]);
	assertTrue(testG.deckCount[1], 10);
	
	printf("-------------------------------------------------------------------------------------\n");
	
	printf("Starting Test 4: player 0 gains no coins\n");
	printf("Coin count of player 0 = %d, expected = %d\n", testG.coins, G.coins);
	assertTrue(testG.coins, G.coins);
	
	printf("-------------------------------------------------------------------------------------\n");
	
	printf("Starting Test 5: player 0 gains no actions\n");
	printf("Actions count of player 0 = %d, expected = %d\n", testG.numActions, G.numActions + 2);
	assertTrue(testG.numActions, G.numActions + 2);
	
	printf("-------------------------------------------------------------------------------------\n");
	
	printf("Starting Test 6: player 0 gains no buys\n");
	printf("Buy count of player 0 = %d, expected = %d\n", testG.numBuys, 1);
	assertTrue(testG.numBuys, G.numBuys);
	
	printf("-------------------------------------------------------------------------------------\n");
	
	printf("Starting Test 5: player discards correct amount\n");
	printf("cards discarded = %d, expected = 0\n", testG.discardCount[0]);
	assertTrue(testG.discardCount[0], 0);

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
	
	printf("\n");
	return 0;
}


