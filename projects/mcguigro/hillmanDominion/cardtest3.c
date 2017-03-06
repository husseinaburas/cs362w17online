#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	printf("--- TESTING VILLAGE CARD EFFECT ---\n");

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
	newState.hand[currentPlayer][newState.handCount[currentPlayer] - 1] = village;
	newState.deckCount[currentPlayer] = 4;
	newState.deck[currentPlayer][0] = smithy;
	newState.deck[currentPlayer][1] = copper;
	newState.deck[currentPlayer][2] = silver;
	newState.deck[currentPlayer][3] = province;
	memcpy(&oldState, &newState, sizeof(struct gameState));

	playCard(newState.handCount[currentPlayer] - 1, 0, 0, 0, &newState);
	if (newState.handCount[currentPlayer] != oldState.handCount[currentPlayer])
		printf("TEST FAILED: HAND SIZE INCORRECT\n");
	else if (oldState.deckCount[currentPlayer] - newState.deckCount[currentPlayer] != 1)
		printf("TEST FAILED: DECK SIZE INCORRECT: %d, %d\n", oldState.deckCount[currentPlayer], newState.deckCount[currentPlayer]);
	else if (newState.numActions != 2)
		printf("TEST FAILED: WRONG NUMBER OF ACTIONS: %d\n", newState.numActions);
	else if (oldState.playedCardCount - newState.playedCardCount != 1)
		printf("TEST FAILED: PLAYED CARD PILE SIZE INCORRECT\n");
	else if (newState.playedCards[newState.playedCardCount - 1] != village)
		printf("TEST FAILED: WRONG CARD PUT IN PLAYED CARD PILE\n");
	else if (newState.deck[currentPlayer][newState.deckCount[currentPlayer - 1]] != province) //wrong -1 placement, look at hand
		printf("TEST FAILED: GAINED WRONG CARD\n");
	else
		printf("TEST SUCCESSFUL\n");

	return 0;
}
