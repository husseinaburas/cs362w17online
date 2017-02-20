#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "rngs.h"
#include "dominion.h"
#include "string.h"

int checkSmithy(int currentPlayer, struct gameState *state) {
	struct gameState * pre = malloc(sizeof(struct gameState));
	memcpy(pre, state, sizeof(struct gameState));

	int hand_pos = floor(Random() * state->handCount[currentPlayer]);

	reSmithy(state, currentPlayer, hand_pos);

	if (state->handCount[currentPlayer] != pre->handCount[currentPlayer] + 3){
		printf("Player has %d cards, expected %d\n", state->handCount[currentPlayer], pre->handCount[currentPlayer] + 3);
		return 1;
	} 
	else{
		return 0;
	}

}


int main() {

	int i, j, x;
	struct gameState state;
	struct gameState pre;
	int smithySuccess = 1;

	for (i = 0; i < 2000; i++){
		for (j = 0; j < sizeof(struct gameState); j++){
			((char *)&state)[j] = floor(Random() * 256);
		}
		memcpy(&pre, &state, sizeof(struct gameState));
		x = floor(Random() * 2);
		//generate random values for the test
		state.deckCount[x] = floor(Random() * MAX_DECK);
		state.discardCount[x] = floor(Random() * MAX_DECK);
		state.handCount[x] = floor(Random() * MAX_HAND);
		state.playedCardCount = floor(Random() * MAX_DECK);
		//gather results of smithy check
		int smithyResult = checkSmithy(x, &state);

		if (smithySuccess){
			if (smithyResult){
				smithySuccess = 0;
			}
		}
	}


	if (!smithySuccess){
		printf("Test failed.\n");
	} 
	else{
		printf("Test passed.\n");
	}


	return 0;
}