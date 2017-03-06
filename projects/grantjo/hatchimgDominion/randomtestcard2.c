//this is the random test for play_outpost

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "rngs.h"

int checkOutpost(struct gameState *post, int handPos){
	
	int x;
	
	x = play_outpost(post, handPos);
	
	assert(x == 0);
	
	return 0;
}

int main(int argc, char* argv[]){
	
	if(argc != 2)
		printf("Must provide one number for random seed. Please run program again.\n");
	
	else{
	int i, j, p, handPos;
		
	struct gameState G;
	
	printf("Performing random tests on play_outpost.\n");
	
	SelectStream(2);
	PutSeed(argv[1]);
	
	for (i = 0; i < 3000; i++){
		for (j = 0; j < sizeof(struct gameState); j++){
			((char*)&G)[j] = floor(Random() * 256);
		}
		G.playedCardCount = floor(Random() * MAX_DECK);
		p = floor(Random() * 2);
		G.whoseTurn = p;
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		handPos = floor(Random() * (G.handCount[p] - 1));
		checkOutpost(&G, handPos);
	}
	
	printf("ALL TESTS PASSED\n");
	
	return 0;
	}
}