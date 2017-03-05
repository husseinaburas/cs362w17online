#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>



int main()
{
	printf("--- TESTING BUYCARD FUNCTION ---\n");
	
	int testFailed = 0;
	struct gameState oldState;
	struct gameState newState;
	int actionCards[10] = { smithy, adventurer, sea_hag, minion, cutpurse, mine, council_room, tribute, village, embargo };
	int seed = 1193;
	int numPlayers = 3;
	int currentPlayer = 0;
	initializeGame(numPlayers, actionCards, seed, &newState);
	memcpy(&oldState, &newState, sizeof(struct gameState));

	//Test buy with no buys left, should have no effect on game state
	newState.whoseTurn = currentPlayer;
	newState.numBuys = 0;
	oldState.numBuys = 0;
	newState.coins = 5;
	oldState.coins = 5;
	buyCard(smithy, &newState);
	if (memcmp(&newState, &oldState, sizeof(struct gameState)) != 0)
	{
		printf("   > NO BUYS LEFT TEST FAILED\n");
		testFailed = 1;
	}
	else
		printf("   > NO BUYS LEFT TEST SUCCESSFUL\n");

	//Test buy with insufficient coins, should have no effect on game state
	initializeGame(numPlayers, actionCards, seed, &newState);
	newState.whoseTurn = currentPlayer;
	newState.numBuys = 1;
	newState.coins = 3;
	memcpy(&oldState, &newState, sizeof(struct gameState));
	buyCard(smithy, &newState);
	if (memcmp(&newState, &oldState, sizeof(struct gameState)) != 0)
	{
		printf("   > INSUFFICIENT COINS TEST FAILED\n");
		testFailed = 1;
	}
	else
		printf("   > INSUFFICIENT COINS TEST SUCCESSFUL\n");

	//Test buy with none of desired card left, should have no effect on game state
	initializeGame(numPlayers, actionCards, seed, &newState);
	newState.whoseTurn = currentPlayer;
	newState.supplyCount[smithy] = 0;
	newState.numBuys = 1;
	newState.coins = 5;
	memcpy(&oldState, &newState, sizeof(struct gameState));
	buyCard(smithy, &newState);
	if (memcmp(&newState, &oldState, sizeof(struct gameState)) != 0)
	{
		printf("   > NONE IN SUPPLY TEST FAILED\n");
		testFailed = 1;
	}
	else
		printf("   > NONE IN SUPPLY TEST SUCCESSFUL\n");

	//Test good buy, should move the card from supply into discard pile
	initializeGame(numPlayers, actionCards, seed, &newState);
	newState.whoseTurn = currentPlayer;
	newState.numBuys = 1;
	newState.coins = 5;
	memcpy(&oldState, &newState, sizeof(struct gameState));
	buyCard(smithy, &newState);
	if (oldState.supplyCount[smithy] - newState.supplyCount[smithy] != 1)
	{
		printf("   > GOOD BUY TEST FAILED: Supply Count Wrong\n");
		testFailed = 1;
	}
	else if (newState.discardCount[currentPlayer] - oldState.discardCount[currentPlayer] != 1)
	{
		printf("   > GOOD BUY TEST FAILED: Discard Count Wrong\n");
		testFailed = 1;
	}
	else if (newState.discard[currentPlayer][newState.discardCount[currentPlayer] - 1] != smithy)
	{
		printf("   > GOOD BUY TEST FAILED: Top Discard Card Not What Was Bought\n");
		testFailed = 1;
	}

	if (testFailed)
		printf("TEST FAILED\n");
	else
		printf("TEST SUCCEEDED\n");

	return 0;
}