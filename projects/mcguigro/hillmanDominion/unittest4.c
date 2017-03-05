#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	printf("--- TESTING GAINCARD FUNCTION ---\n");

	int testFailed = 0;
	struct gameState oldState;
	struct gameState newState;
	int actionCards[10] = { smithy, adventurer, sea_hag, minion, cutpurse, mine, council_room, tribute, village, embargo };
	int seed = 1776;
	int numPlayers = 3;
	int currentPlayer = 0;

	//Testing gainCard with empty supply
	initializeGame(numPlayers, actionCards, seed, &newState);
	newState.supplyCount[smithy] = 0;
	memcpy(&oldState, &newState, sizeof(struct gameState));
	gainCard(smithy, &newState, 0, currentPlayer);
	if (memcmp(&newState, &oldState, sizeof(struct gameState)) != 0)
	{
		printf("   > EMPTY SUPPLY TEST FAILED: STATE CHANGED\n");
		testFailed = 1;
	}
	else
		printf("   > EMPTY SUPPLY TEST SUCCESSFUL\n");

	//Testing gainCard to discard
	initializeGame(numPlayers, actionCards, seed, &newState);
	memcpy(&oldState, &newState, sizeof(struct gameState));
	gainCard(smithy, &newState, 0, currentPlayer);
	if (newState.discardCount[currentPlayer] - oldState.discardCount[currentPlayer] != 1)
	{
		printf("   > GAIN TO DISCARD TEST FAILED: DISCARD PILE WRONG SIZE\n");
		testFailed = 1;
	}
	else if (newState.discard[currentPlayer][newState.discardCount[currentPlayer] - 1] != smithy)
	{
		printf("   > GAIN TO DISCARD TEST FAILED: WRONG CARD GAINED\n");
		testFailed = 1;
	}
	else if (newState.deckCount[currentPlayer] != oldState.deckCount[currentPlayer])
	{
		printf("   > GAIN TO DISCARD TEST FAILED: DECK SIZE CHANGED\n");
		testFailed = 1;
	}
	else if (newState.handCount[currentPlayer] != oldState.handCount[currentPlayer])
	{
		printf("   > GAIN TO DISCARD TEST FAILED: HAND SIZE CHANGED\n");
		testFailed = 1;
	}
	else
		printf("   > GAIN TO DISCARD TEST SUCCESSFUL\n");

	//Testing gainCard to deck
	initializeGame(numPlayers, actionCards, seed, &newState);
	memcpy(&oldState, &newState, sizeof(struct gameState));
	gainCard(smithy, &newState, 1, currentPlayer);
	if (newState.deckCount[currentPlayer] - oldState.deckCount[currentPlayer] != 1)
	{
		printf("   > GAIN TO DECK TEST FAILED: DECK WRONG SIZE\n");
		testFailed = 1;
	}
	else if (newState.deck[currentPlayer][newState.deckCount[currentPlayer] - 1] != smithy)
	{
		printf("   > GAIN TO DECK TEST FAILED: WRONG CARD GAINED\n");
		testFailed = 1;
	}
	else if (newState.discardCount[currentPlayer] != oldState.discardCount[currentPlayer])
	{
		printf("   > GAIN TO DECK TEST FAILED: DISCARD PILE SIZE CHANGED\n");
		testFailed = 1;
	}
	else if (newState.handCount[currentPlayer] != oldState.handCount[currentPlayer])
	{
		printf("   > GAIN TO DECK TEST FAILED: HAND SIZE CHANGED\n");
		testFailed = 1;
	}
	else
		printf("   > GAIN TO DECK TEST SUCCESSFUL\n");

	//Testing gainCard to hand
	initializeGame(numPlayers, actionCards, seed, &newState);
	memcpy(&oldState, &newState, sizeof(struct gameState));
	gainCard(smithy, &newState, 2, currentPlayer);
	if (newState.handCount[currentPlayer] - oldState.handCount[currentPlayer] != 1)
	{
		printf("   > GAIN TO HAND TEST FAILED: HAND WRONG SIZE\n");
		testFailed = 1;
	}
	else if (newState.hand[currentPlayer][newState.handCount[currentPlayer] - 1] != smithy)
	{
		printf("   > GAIN TO HAND TEST FAILED: WRONG CARD GAINED\n");
		testFailed = 1;
	}
	else if (newState.discardCount[currentPlayer] != oldState.discardCount[currentPlayer])
	{
		printf("   > GAIN TO HAND TEST FAILED: DISCARD PILE SIZE CHANGED\n");
		testFailed = 1;
	}
	else if (newState.deckCount[currentPlayer] != oldState.deckCount[currentPlayer])
	{
		printf("   > GAIN TO HAND TEST FAILED: DECK SIZE CHANGED\n");
		testFailed = 1;
	}
	else
		printf("   > GAIN TO HAND TEST SUCCESSFUL\n");

	if (testFailed)
		printf("TEST FAILED\n");
	else
		printf("TEST SUCCEEDED\n");

	return 0;
}