#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(){
	printf("------  smithy unit test ------\n");
	
	//initialize game
	int r;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	struct gameState G;
	r = initializeGame(2, k, 1, &G);

	G.hand[0][0] = k[6];
	G.handCount[0] = 1;

	printf("Player 1 plays smithy card\n");
	smithyCard(0, 0, &G);

	printf("Player 1 now has three cards\n");
	asserttrue(G.handCount[0] == 3);

	printf("Check if smithy card was removed from Player 1 hand\n");
	asserttrue(G.hand[0][0] != k[6]);

	printf("--------------- end --------------\n");
	return 0;
}