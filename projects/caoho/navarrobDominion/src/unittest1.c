#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

/**
 * This file is designed to test:
 * int supplyCount(int card, struct gameState *state);
 * */
int main() {

	printf(
			"****** Testing Method <int fullDeckCount(int player, int card, struct gameState *state);>******\n");



	int rSeed = rand();
	int kValues[10] = { adventurer, council_room, feast, gardens, mine, remodel,
			smithy, village, baron, great_hall };
	int numPlayer = 2;
	struct gameState state;
	initializeGame(numPlayer, kValues, rSeed, &state);

	int num_cards = treasure_map;

	int i,j;
	int player = 0;
	for (i = 0; i < num_cards; i++) {
		int count = 0;
		int card = i;
		for (j = 0; j < state.deckCount[player]; j++) {
			if (state.deck[player][j] == i) {
				count++;
			}
		}
		for (j = 0; j < state.handCount[player]; j++) {
			if (state.hand[player][j] == i) {
				count++;
			}
		}
		for (j = 0; j < state.discardCount[player]; j++) {
			if (state.discard[player][j] == i) {
				count++;
			}
		}
		assertMsg("Testing the fullDeckCount function matches the count", fullDeckCount(player, card, &state), count);
		player++;
	}

	printf("****** FInished ******\n");

	return 0;
}
