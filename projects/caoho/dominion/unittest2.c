#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]) {
	printf(
			"****** Testing Method <int updateCoins(int player, struct gameState *state, int bonus);>******\n");

	int rSeed = rand();
	int kValues[10] = { adventurer, council_room, feast, gardens, mine, remodel,
			smithy, village, baron, great_hall };
	int numPlayer = 2;
	struct gameState state;
	initializeGame(numPlayer, kValues, rSeed, &state);

	int i;
	int copperCounter = 0;
	int silverCounter = 0;
	int goldCounter = 0;
	int cardsCouner = state.handCount[0];

	int bonusCounter = floor( Random() * 10);

	for (i = 0; i < cardsCouner; i++) {
		if (state.hand[0][i] == copper) {
			copperCounter++;
		} else if (state.hand[0][i] == silver) {
			silverCounter++;
		} else if (state.hand[0][i] == silver) {
			goldCounter++;
		}
	}

	int total_coins = copperCounter*1 + silverCounter*2 + goldCounter*3 + bonusCounter;
	updateCoins(0, &state, bonusCounter);
	assertMsg("Testing update coins ", total_coins, state.coins);

	printf("****** FInished ******\n");

	return 0;
}

