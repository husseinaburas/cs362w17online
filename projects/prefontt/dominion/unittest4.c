/* This unit test will test the updateCoins function */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
	
	int bonus = 0;
	int i;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy, council_room};

	int numPlayers = 2;
	int thisPlayer = 0;
	int seed = 10;

	initializeGame(numPlayers, k, seed, &G);

	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("++++++++++++ TESTING updateCoins Function ++++++++++++++++\n\n\n");
	
	printf("Happy path test\n");
	testG.coins = 0;
	for(i = 0; i < testG.handCount[0]; i++)
	{
		if(testG.hand[0][i] == copper)
		{
			testG.coins++;
		}
	}
	int coinCount = testG.coins;
	printf("Player 0 started with %d coins\n", testG.coins);
	updateCoins(thisPlayer, &testG, bonus);
	printf("adding %d coins, expected coins = %d\n", bonus, testG.coins);
	assertTrue(testG.coins, (bonus + coinCount));
	printf("Checking opponents deck count doesn't change\n");
	printf("Opponent deck count = %d, expected 10\n", testG.deckCount[1]);
	assertTrue(testG.deckCount[0] + 5, testG.deckCount[1]);
	
	printf("------------------------------------------------------------------\n");
	
	
	printf("Testing with bonus > 0\n");
	testG.coins = 0;
	bonus = 2;
	
	for(i = 0; i < testG.handCount[0]; i++)
	{
		if(testG.hand[0][i] == copper)
		{
			testG.coins++;
		}
	}
	coinCount = testG.coins;
	printf("Player 0 started with %d coins\n", testG.coins);
	updateCoins(thisPlayer, &testG, bonus);
	printf("adding %d, expected coins = %d\n", bonus, testG.coins);
	assertTrue(testG.coins, (coinCount + bonus));
	printf("Checking opponents deck count doesn't change\n");
	printf("Opponent deck count = %d, expected 10\n", testG.deckCount[1]);
	assertTrue(testG.deckCount[0] + 5, testG.deckCount[1]);
	
	printf("------------------------------------------------------------------\n");
	
	
	printf("Testing with no bonus and no treasures in hand\n");
	testG.coins = 0;
	bonus = 0;
	
	for(i = 0; i < testG.handCount[0]; i++)
	{
		testG.hand[0][i] = estate;
	}
	coinCount = testG.coins;
	printf("Player 0 started with %d coins\n", testG.coins);
	updateCoins(thisPlayer, &testG, bonus);
	printf("adding %d, expected coins = %d\n", bonus, testG.coins);
	assertTrue(testG.coins, (coinCount + bonus));
	
	printf("Checking opponents deck count doesn't change\n");
	printf("Opponent deck count = %d, expected 10\n", testG.deckCount[1]);
	assertTrue(testG.deckCount[0] + 5, testG.deckCount[1]);
	
	printf("--------------------------------------------------------------------\n");
	
	printf("Testing for any change in actions of player\n");
	printf("Actions count of player 0 = %d, expected = %d\n", testG.numActions, 1);
	assertTrue(testG.numActions, G.numActions);
	printf("Testing for no change in hand count\n");
	printf("hand count = %d, expected = %d\n", testG.handCount[0], G.handCount[0]);
	assertTrue(testG.handCount[0], 5);
	printf("Testing for state change in deck of player 0\n");
	printf("Deck count of player 0 after card played: %d\n", testG.deckCount[0]);
	assertTrue(testG.deckCount[0], 5);
	
	printf("---------------------------------------------------------------------\n");
	
	printf("Testing for state change in deck of player 1\n");
	printf("Deck count of opponent = %d, expected = %d\n", testG.deckCount[1], G.deckCount[1]);
	assertTrue(testG.deckCount[1], G.deckCount[1]);
	
	bonus = 0;
	printf("Testing with having gold and silver in my hand\n");
	testG.hand[0][1] = silver;
	testG.hand[0][2] = gold;
	updateCoins(thisPlayer, &testG, bonus);
	printf("adding %d coins, expected coins = %d\n", bonus, 5);
	assertTrue(testG.coins, 5);
	
		
	
	
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
