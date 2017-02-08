/*int Dovillage(int currentPlayer, struct gameState *state, int handPos){
      //+1 Card
      drawCard(currentPlayer, state);

      //
      state->numActions = state->numActions + 1;

      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
}
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() {
    int i, j, m;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int handPos = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	memcpy(&testG, &G, sizeof(struct gameState));
	printf("Testing add 1 Card \n", TESTCARD);
	Dovillage(0,&testG, handPos);
	printf("Expected: %d, Result: %d\n", G.handCount[0] + 1, testG.handCount[0]);

	printf("Testing add 2 actions \n", TESTCARD);
	memcpy(&testG, &G, sizeof(struct gameState));
	Dovillage(0,&testG, handPos);

	printf("Expected action count: %d, Result: %d\n", G.numActions + 2, testG.numActions);
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


