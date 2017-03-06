#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

int getCardIndex(int card, int actionCards[10]);
void randomizeState(struct gameState* state, int actionCards[10]);
int insertCard(struct gameState* state, int card);
void insertTreasures(struct gameState* state);
void printTestResult(struct gameState* newState, struct gameState* oldState, int testNum, int currentPlayer);

int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));

	struct gameState newState;
	struct gameState oldState;

	int actionCards[10] = { smithy, adventurer, sea_hag, minion, cutpurse, mine, council_room, great_hall, village, embargo };

	printf("--- TESTING ADVENTURER CARD EFFECT ---\n");

	int i;
	for (i = 0; i < 200; i++)
	{
		randomizeState(&newState, actionCards);
		int cardPos = insertCard(&newState, adventurer);
		assert(cardPos != -1);
		insertTreasures(&newState);
		memcpy(&oldState, &newState, sizeof(struct gameState));
		int currentPlayer = newState.whoseTurn;
		playCard(cardPos, 0, 0, 0, &newState);
		printTestResult(&newState, &oldState, i, currentPlayer);
	}

	return 0;
}

int getCardIndex(int card, int actionCards[10])
{
	if (card < 10 && card > -1)
		return actionCards[card];
	else if (card == 10)
		return copper;
	else if (card == 11)
		return silver;
	else if (card == 12)
		return gold;
	else if (card == 13)
		return estate;
	else if (card == 14)
		return duchy;
	else if (card == 15)
		return province;
	else
		return -1;
}

void randomizeState(struct gameState* state, int actionCards[10])
{
	int numPlayers = rand() % 3 + 2;
	initializeGame(numPlayers, actionCards, -1, state);
	int i;

	//Randomize supply counts
	for (i = 0; i < 10; i++)
	{
		state->supplyCount[actionCards[i]] = rand() % 11;
	}

	//Randomize whose turn it is
	int currentPlayer = rand() % numPlayers;
	state->whoseTurn = currentPlayer;

	//Randomize number of actions
	state->numActions = rand() % 4;

	//Randomize number of buys
	state->numBuys = rand() % 4;

	//Randomize hands

	int j;
	for (i = 0; i < numPlayers; i++)
	{
		state->handCount[i] = rand() % 7 + 1;
		fflush(stdout);
		for (j = 0; j < state->handCount[i]; j++)
		{
			int card = rand() % 16;
			state->hand[i][j] = getCardIndex(card, actionCards);
		}
	}

	//Get coins
	updateCoins(state->whoseTurn, state, 0);

	//Set phase to 0
	state->phase = 0;

	//Randomize decks
	for (i = 0; i < numPlayers; i++)
	{
		state->deckCount[i] = rand() % 7 + 1;
		for (j = 0; j < state->deckCount[i]; j++)
		{
			int card = rand() % 16;
			state->deck[i][j] = getCardIndex(card, actionCards);
		}
	}

	//Randomize discard piles
	for (i = 0; i < numPlayers; i++)
	{
		state->discardCount[i] = rand() % 7 + 1;
		for (j = 0; j < state->discardCount[i]; j++)
		{
			int card = rand() % 16;
			state->discard[i][j] = getCardIndex(card, actionCards);
		}
	}
}

int insertCard(struct gameState* state, int card)
{
	int currentPlayer = state->whoseTurn;
	int handSize = state->handCount[currentPlayer];
	if (handSize < 1)
		return -1;
	int cardPos = rand() % handSize;
	state->hand[currentPlayer][cardPos] = card;
	return cardPos;
}

void insertTreasures(struct gameState* state)
{
	int currentPlayer = state->whoseTurn;
	int s = rand() % 3;
	if (s == 0)
	{
		if (state->deckCount[currentPlayer] < 2)
		{
			state->deckCount[currentPlayer] = 2;
			state->deck[currentPlayer][0] = copper + (rand() % 3);
			state->deck[currentPlayer][1] = copper + (rand() % 3);
		}
		else
		{
			int firstIndex = rand() % state->deckCount[currentPlayer];
			state->deck[currentPlayer][firstIndex] = copper + (rand() % 3);
			int secondIndex;
			do
			{
				secondIndex = rand() % state->deckCount[currentPlayer];
			} while (secondIndex != firstIndex);
			state->deck[currentPlayer][secondIndex] = copper + (rand() % 3);
		}
	}
	else if (s == 1)
	{
		if (state->deckCount[currentPlayer] < 1)
		{
			state->deckCount[currentPlayer] = 1;
			state->deck[currentPlayer][0] = copper + (rand() % 3);
		}
		else
		{
			int firstIndex = rand() % state->deckCount[currentPlayer];
			state->deck[currentPlayer][firstIndex] = copper + (rand() % 3);
		}
		if (state->discardCount[currentPlayer] < 1)
		{
			state->discardCount[currentPlayer] = 1;
			state->discard[currentPlayer][0] = copper + (rand() % 3);
		}
		else
		{
			int secondIndex = rand() % state->discardCount[currentPlayer];
			state->discard[currentPlayer][secondIndex] = copper + (rand() % 3);
		}
	}
	else
	{
		if (state->discardCount[currentPlayer] < 2)
		{
			state->discardCount[currentPlayer] = 2;
			state->discard[currentPlayer][0] = copper + (rand() % 3);
			state->discard[currentPlayer][1] = copper + (rand() % 3);
		}
		else
		{
			int firstIndex = rand() % state->discardCount[currentPlayer];
			state->discard[currentPlayer][firstIndex] = copper + (rand() % 3);
			int secondIndex;
			do
			{
				secondIndex = rand() % state->discardCount[currentPlayer];
			} while (secondIndex != firstIndex);
			state->discard[currentPlayer][secondIndex] = copper + (rand() % 3);
		}
	}
}

void printTestResult(struct gameState* newState, struct gameState* oldState, int testNum, int currentPlayer)
{
	if (oldState->numActions < 1)
	{
		if (memcmp(newState, oldState, sizeof(struct gameState)) != 0)
			printf("TEST %i FAILED: STATE CHANGED WHEN PLAYER HAD 0 ACTIONS\n", testNum);
		else
			printf("TEST %i SUCCESSFUL\n", testNum);
	}
	else if (oldState->deckCount[currentPlayer] + oldState->handCount[currentPlayer] + oldState->discardCount[currentPlayer] !=
		newState->deckCount[currentPlayer] + newState->handCount[currentPlayer] + newState->discardCount[currentPlayer] + newState->playedCardCount)
		printf("TEST %i FAILED: TOTAL NUMBER OF PLAYER'S CARDS CHANGED\n", testNum);
	else if (newState->handCount[currentPlayer] - oldState->handCount[currentPlayer] != 1)
		printf("TEST %i FAILED: HAND SIZE INCORRECT\n", testNum);
	else if (newState->playedCardCount != 1)
		printf("TEST %i FAILED: PLAYED CARD PILE SIZE INCORRECT: %i\n", testNum, newState->playedCardCount);
	else if (newState->playedCards[0] != adventurer)
		printf("TEST %i FAILED: WRONG CARD IN PLAYED CARD PILE\n", testNum);
	else if (oldState->numActions - newState->numActions != 1)
		printf("TEST %i FAILED: WRONG NUMBER OF ACTIONS\n", testNum);
	else if ((newState->hand[currentPlayer][newState->handCount[currentPlayer] - 2] != copper &&
		newState->hand[currentPlayer][newState->handCount[currentPlayer] - 2] != silver &&
		newState->hand[currentPlayer][newState->handCount[currentPlayer] - 2] != gold) ||
		(newState->hand[currentPlayer][newState->handCount[currentPlayer] - 1] != copper &&
			newState->hand[currentPlayer][newState->handCount[currentPlayer] - 1] != silver &&
			newState->hand[currentPlayer][newState->handCount[currentPlayer] - 1] != gold))
		printf("TEST %i FAILED: CARDS GAINED WERE NOT TREASURES", testNum);
	else
		printf("TEST %i SUCCESSFUL\n", testNum);

}