#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

/**
 * This class is designed to test:
 * int shuffle(int player, struct gameState *state);
 * */
int main(int argc, char ** argv){
	printf("****** Testing Method <int shuffle(int player, struct gameState *state);>******\n");
	struct gameState state;
	struct gameState stateCopy;
	memcpy (&stateCopy, &state, sizeof(struct gameState));

	int kValues[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int rSeed = rand();
	int result = initializeGame(2, kValues, rSeed, &state);

	printf("****** Testing state->deckCount[player] < 1 \n");
	int tmpVar = state.deckCount[1];
	state.deckCount[1] = 0;
	result = shuffle(1, &state);
	assertMsg ("Testing the condition (state->deckCount[player] < 1)", -1, result);

	printf("****** Testing state->deckCount[player] >= 1 \n");
	state.deckCount[1] = tmpVar;
	result = shuffle(1, &state);
	assertMsg ("Testing the condition (state->deckCount[player] >= 1)", 0, result);
	assertMsg ("Testing shuffled result", -1, memcmp(&state, &stateCopy, sizeof(struct gameState)));

	printf("****** FInished ******\n");
	return 0;
}
