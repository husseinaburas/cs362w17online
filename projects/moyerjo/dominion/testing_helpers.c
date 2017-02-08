#include "testing_helpers.h"

#define SUPPLYTOTAL 27

int compareGameState(int player, struct gameState *state1, struct gameState *state2) {

	int i = 0;
	if (state1->handCount[player] != state2->handCount[player]) {
		return 0;
	}
	for (i = state1->handCount[player]; i < state1->handCount[player]; i++) {
		if (state1->hand[player][i] != state2->hand[player][i]) {
			return 0;
		}
	}

	if (state1->deckCount[player] != state2->deckCount[player]) {
		return 0;
	}

	for (i = state1->deckCount[player]; i < state1->deckCount[player]; i++) {
		if (state1->deck[player][i] != state2->deck[player][i]) {
			return 0;
		}
	}

	if (state1->discardCount[player] != state2->discardCount[player]) {
		return 0;
	}
	for (i = state1->discardCount[player]; i < state1->discardCount[player]; i++) {
		if (state1->discard[player][i] != state2->discard[player][i]) {
			return 0;
		}
	}
	return 1; //all compared values are equal
}

int cardNumbersConstant(int player, struct gameState *state1, struct gameState *state2) {
	int state1Cards = 0, state2Cards = 0;

	state1Cards = state1->handCount[player] + state1->deckCount[player] + state1->playedCardCount + state1->discardCount[player];
	
	state2Cards = state2->handCount[player] + state2->deckCount[player] + state2->playedCardCount + state2->discardCount[player];

	if (state1Cards == state2Cards) {
		return 1;
	}
	else {
		return 0;
	}

	return 0;
}

int supplyUnchanged(struct gameState *state1, struct gameState *state2) {
	int i;
	for (i = 0; i < SUPPLYTOTAL; i++) {
		if (state1->supplyCount[i] != state2->supplyCount[i]) {
			return 0;
		}
	}
	return 1;
}

int treasureMapSupplyUnchanged(struct gameState *state1, struct gameState *state2) {
	int i;
	for (i = 0; i < SUPPLYTOTAL; i++) {
		if (state1->supplyCount[i] != state2->supplyCount[i] && i != 6) {
			return 0;
		}
	}
	return 1;
}

int scoreForRefactor(int player, struct gameState *state) {

	int i;
	int score = 0;
	//score from hand

	for (i = 0; i < state->handCount[player]; i++)
	{
		if (state->hand[player][i] == curse) {
			score = score - 1;
		}
		else if (state->hand[player][i] == estate) {
			score = score + 1;
		}
		else if (state->hand[player][i] == duchy) {
			score = score + 3;
		}
		else if (state->hand[player][i] == province) {
			score = score + 6;
		}
		else if (state->hand[player][i] == great_hall) {
			score = score + 1;
		}
		else if (state->hand[player][i] == gardens) {
			score = score + ((state->handCount[player] + state->deckCount[player] + state->discardCount[player]) / 10);
		}
	}

	//score from discard
	for (i = 0; i < state->discardCount[player]; i++)
	{
		if (state->discard[player][i] == curse) {
			score = score - 1;
		}
		else if (state->discard[player][i] == estate) {
			score = score + 1;
		}
		else if (state->discard[player][i] == duchy) {
			score = score + 3;
		}
		else if (state->discard[player][i] == province) {
			score = score + 6;
		}
		else if (state->discard[player][i] == great_hall) {
			score = score + 1;
		}
		else if (state->discard[player][i] == gardens) {
			score = score + ((state->handCount[player] + state->deckCount[player] + state->discardCount[player]) / 10);
		}
	}

	//score from deck
	for (i = 0; i < state->deckCount[player]; i++)
	{
		if (state->deck[player][i] == curse) {
			score = score - 1;
		}
		else if (state->deck[player][i] == estate) {
			score = score + 1;
		}
		else if (state->deck[player][i] == duchy) {
			score = score + 3;
		}
		else if (state->deck[player][i] == province) {
			score = score + 6;
		}
		else if (state->deck[player][i] == great_hall) {
			score = score + 1;
		}
		else if (state->deck[player][i] == gardens) {
			score = score + ((state->handCount[player] + state->deckCount[player] + state->discardCount[player]) / 10);
		}
	}

	return score;
}