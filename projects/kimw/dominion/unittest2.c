#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(){
	printf("------  shuffle unit test ------\n");
	
	//initialize game
	int r, wasShuffled;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	struct gameState G;
  	r = initializeGame(2, k, 1, &G);
	
	//Player 1 has no cards, expect shuffle to return -1
	//indicating cards were not shuffled.
	printf("Player 1 has no cards\n");
	G.deckCount[0] = 0;
	wasShuffled = shuffle(0, &G);
	asserttrue(wasShuffled == -1);
	
	//Player 1 has 4 cards, expect shuffle to return 0
	//indicating cards were shuffled.
	printf("Player 1 has cards\n");
	G.deckCount[0] = 4;
	wasShuffled = shuffle(0, &G);
	asserttrue(wasShuffled == 0);
		
	printf("--------------- end --------------\n");
	return 0;
}