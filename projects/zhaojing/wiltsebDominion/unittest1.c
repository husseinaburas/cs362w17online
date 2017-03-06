#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char ** argv){
	printf("******begin unit test on shuffle()******\n");
	
	//initialize game
	struct gameState G;
	int result, randomVar = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	randomVar = rand() % 10;
	result = initializeGame(2, k, randomVar, &G);
	
	//test deck count < 1 condition
	printf("testing shuffle() with deck count < 1 \n");
	G.deckCount[1] = -10;
	result = shuffle(1, &G);
	asserttrue(result == -1);
	
	G.deckCount[1] = 0;
	result = shuffle(1, &G);
	asserttrue(result == -1);
	
	//test deck count > 0 condition
	printf("testing shuffle() with deck count > 0 \n");
	G.deckCount[1] = 1;
	result = shuffle(1, &G);
	asserttrue(result == 0);
	
	G.deckCount[1] = 3;
	result = shuffle(1, &G);
	asserttrue (result == 0);
		
	printf("******end unit test on shuffle()******\n");
	return 0;
}
	