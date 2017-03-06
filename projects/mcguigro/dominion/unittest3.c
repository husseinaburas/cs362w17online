#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	printf("--- TESTING DRAWCARD FUNCTION ---\n");

	int testFailed = 0;
	struct gameState oldState;
	struct gameState newState;
	int actionCards[10] = { smithy, adventurer, sea_hag, minion, cutpurse, mine, council_room, tribute, village, embargo };
	int seed = 1492;
	int numPlayers = 3;
	int currentPlayer = 0;
	
	//Testing drawCard without shuffle
	initializeGame(numPlayers, actionCards, seed, &newState);
	newState.deckCount[currentPlayer] = 5;
	int i = 0;
	for (i = 0; i < 4; i++)
	{
		newState.deck[currentPlayer][i] = smithy;
	}
	newState.deck[currentPlayer][4] = adventurer;
	memcpy(&oldState, &newState, sizeof(struct gameState));
	drawCard(currentPlayer, &newState);
	if (newState.deckCount[currentPlayer] != 4)
	{
		printf("   > NO SHUFFLE TEST FAILED: WRONG DECK SIZE\n");
		testFailed = 1;
	}
	else if (newState.handCount[currentPlayer] - oldState.handCount[currentPlayer] != 1)
	{
		printf("   > NO SHUFFLE TEST FAILED: WRONG HAND SIZE\n");
		testFailed = 1;
	}
	else if (newState.hand[currentPlayer][newState.handCount[currentPlayer] - 1] != adventurer)
	{
		printf("   > NO SHUFFLE TEST FAILED: WRONG CARD DRAWN\n");
		testFailed = 1;
	}
	else
		printf("   > NO SHUFFLE TEST SUCCESSFUL\n");

	//Testing drawCard with shuffle
	initializeGame(numPlayers, actionCards, seed, &newState);
	newState.deckCount[currentPlayer] = 0;
	newState.discardCount[currentPlayer] = 5;
	for (i = 0; i < 4; i++)
	{
		newState.discard[currentPlayer][i] = smithy;
	}
	newState.discard[currentPlayer][4] = adventurer;
	memcpy(&oldState, &newState, sizeof(struct gameState));
	drawCard(currentPlayer, &newState);
	if (newState.deckCount[currentPlayer] != 4)
	{
		printf("   > WITH SHUFFLE TEST FAILED: WRONG DECK SIZE\n");
		testFailed = 1;
	}
	else if (newState.discardCount[currentPlayer] != 0)
	{
		printf("   > WITH SHUFFLE TEST FAILED: DISCARD PILE NOT EMPTY\n");
		testFailed = 1;
	}
	else if (newState.handCount[currentPlayer] - oldState.handCount[currentPlayer] != 1)
	{
		printf("   > WITH SHUFFLE TEST FAILED: WRONG HAND SIZE\n");
		testFailed = 1;
	}
	else if (newState.hand[currentPlayer][newState.handCount[currentPlayer] - 1] != smithy &&
		newState.hand[currentPlayer][newState.handCount[currentPlayer] - 1] != adventurer)
	{
		printf("   > WITH SHUFFLE TEST FAILED: WRONG CARD DRAWN\n");
		testFailed = 1;
	}
	else
		printf("   > WITH SHUFFLE TEST SUCCESSFUL\n");

	if (testFailed)
		printf("TEST FAILED\n");
	else
		printf("TEST SUCCEEDED\n");

	return 0;
}