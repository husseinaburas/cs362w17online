#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void asserttrue(int num){
    if(num) printf("TEST PASSED. \n");
    else printf("TEST FAILED.\n");
    return;
}


int main(int argc, char ** argv){
	printf("\n--- TESTING shuffle() ---\n");
	
	//initialize game
	struct gameState G;
	int result, random = 0;
	int k[10] = {adventurer, smithy, council_room, feast, mine, gardens, remodel, village, great_hall, baron};
	random = rand() % 10;
	result = initializeGame(2, k, random, &G);
	
	//test deck count when < 1 
	printf("testing shuffle() with deck count < 1 \n");
	G.deckCount[1] = -10;
	result = shuffle(1, &G);
	asserttrue(result == -1);
	
	G.deckCount[1] = 0;
	result = shuffle(1, &G);
	asserttrue(result == -1);
	
	//test deck count when > 0 
	printf("testing shuffle() with deck count > 0 \n");
	G.deckCount[1] = 1;
	result = shuffle(1, &G);
	asserttrue(result == 0);
	
	G.deckCount[1] = 3;
	result = shuffle(1, &G);
	asserttrue (result == 0);
		
	printf("-------------END UNIT TEST ON shuffle()------------\n");
	return 0;
}
	