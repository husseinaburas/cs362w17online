#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(){
	printf("------  village unit test ------\n");
	
	//initialize game
	int r;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	struct gameState G, oG;
	r = initializeGame(2, k, 1, &G);

	G.hand[0][0] = k[7];
	G.handCount[0] = 1;

	// save initial state
	memcpy(&oG, &G, sizeof(struct gameState));

	printf("Player 1 plays village card\n");
	villageCard(0, 0, &G);

	printf("Player 1 drew a card\n");
	asserttrue(G.handCount[0] == 1);

	printf("Player 1 number of actions increased by 2\n");
	asserttrue(( G.numActions - oG.numActions ) == 2);

	printf("Check if village card was removed from Player 1 hand\n");
	asserttrue(G.hand[0][0] != k[7]);

	printf("--------------- end --------------\n");
	return 0;
}