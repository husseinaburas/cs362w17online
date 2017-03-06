#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	printf("--- TESTING GREAT HALL CARD EFFECT ---\n");

	int testFailed = 0;
	struct gameState oldState;
	struct gameState newState;
	int actionCards[10] = { smithy, adventurer, sea_hag, minion, cutpurse, mine, council_room, great_hall, village, embargo };
	int seed = 1666;
	int numPlayers = 3;
	int currentPlayer = 0;

	initializeGame(numPlayers, actionCards, seed, &newState);
	newState.phase = 0;
	newState.numActions = 1;
	newState.whoseTurn = currentPlayer;
	newState.hand[currentPlayer][newState.handCount[currentPlayer] - 1] = great_hall;
	newState.deckCount[currentPlayer] = 4;
	newState.deck[currentPlayer][0] = smithy;
	newState.deck[currentPlayer][1] = copper;
	newState.deck[currentPlayer][2] = silver;
	newState.deck[currentPlayer][3] = province;
	memcpy(&oldState, &newState, sizeof(struct gameState));

	playCard(newState.handCount[currentPlayer] - 1, 0, 0, 0, &newState);
	if (newState.handCount[currentPlayer] != oldState.handCount[currentPlayer])
	{
		printf("   > EFFECT TEST FAILED: HAND SIZE INCORRECT\n");
		testFailed = 1;
	}
	else if (oldState.deckCount[currentPlayer] - newState.deckCount[currentPlayer] != 1)
	{
		printf("   > EFFECT TEST FAILED: DECK SIZE INCORRECT\n");
		testFailed = 1;
	}
	else if (oldState.playedCardCount - newState.playedCardCount != 1)
	{
		printf("   > EFFECT TEST FAILED: PLAYED CARD PILE SIZE INCORRECT: %d, %d\n", oldState.playedCardCount, newState.playedCardCount);
		testFailed = 1;
	}
	else if (newState.playedCards[newState.playedCardCount - 1] != village)
	{
		printf("   > EFFECT TEST FAILED: WRONG CARD PUT IN PLAYED CARD PILE\n");
		testFailed = 1;
	}
	else if (newState.numActions != 1)
	{
		printf("   > EFFECT TEST FAILED: WRONG NUMBER OF ACTIONS\n");
		testFailed = 1;
	}
	else if (newState.deck[currentPlayer][newState.deckCount[currentPlayer - 1]] != province)
	{
		printf("   > EFFECT TEST FAILED: GAINED WRONG CARD\n");
		testFailed = 1;
	}
	else
		printf("   > EFFECT TEST SUCCESSFUL\n");

	int oldScore = scoreFor(currentPlayer, &oldState);
	oldState.deck[currentPlayer][0] = great_hall;
	if (scoreFor(currentPlayer, &oldState) - oldScore != 1)
	{
		printf("   > SCORE TEST FAILED: CARD NOT WORTH +1 VICTORY POINTS\n");
		testFailed = 1;
	}
	else
		printf("   > SCORE TEST SUCCESSFUL\n");

	if (testFailed)
		printf("TEST FAILED\n");
	else
		printf("TEST SUCCEEDED\n");


	return 0;
}