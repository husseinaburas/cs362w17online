#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int compare2(const void* a, const void* b) {
	if (*(int*)a > *(int*)b)
		return 1;
	if (*(int*)a < *(int*)b)
		return -1;
	return 0;
}

int testFailed()
{
	printf("TEST FAILED\n");
	return 0;
}

int main()
{
	printf("--- TESTING SHUFFLE FUNCTION ---\n");
	struct gameState oldState;
	struct gameState newState;
	int actionCards[10] = { smithy, adventurer, sea_hag, minion, cutpurse, mine, council_room, tribute, village, embargo };
	int seed = 1234;
	int numPlayers = 3;
	int currentPlayer = 0;
	initializeGame(numPlayers, actionCards, seed, &newState);
	memcpy(&oldState, &newState, sizeof(struct gameState));

	shuffle(currentPlayer, &newState);

	//Test if number of cards in current player's deck is same
	if (newState.deckCount[currentPlayer] != oldState.deckCount[currentPlayer])
		return testFailed();

	//Test if remaining game state unchanged
	qsort((void*)(newState.deck[currentPlayer]), newState.deckCount[currentPlayer], sizeof(int), compare2);
	qsort((void*)(oldState.deck[currentPlayer]), oldState.deckCount[currentPlayer], sizeof(int), compare2);

	if (memcmp(&newState, &oldState, sizeof(struct gameState)) != 0)
		return testFailed();

	//All tests passed
	printf("TEST SUCCESSFUL\n");
	return 0;
}