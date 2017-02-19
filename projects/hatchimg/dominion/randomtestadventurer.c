#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "rngs.h"

int checkAdventurer(struct gameState *post){
	
	int x;
	
	x = play_adventurer(post);
	
	assert(x == 0);
	
	return 0;
}

int main(int argc, char *argv[]){
	
	if(argc != 2)
		printf("Must provide one number for random seed. Please run program again.\n");
	
	else{
	int i, j, p;
	
	struct gameState G;
		
	printf("Performing random tests on play_adventurer.\n");
	
	SelectStream(2);
	PutSeed(argv[1]);
	
	for (i = 0; i < 125; i++){
		for (j = 0; j < sizeof(struct gameState); j++){
			((char*)&G)[j] = floor(Random() * 256);
		}
		p = floor(Random() * 2);
		G.whoseTurn = p;
		G.deckCount[p] = floor(Random() * MAX_DECK);
		
		//make sure there are three treasure cards in the deck (should be two, but inserted bug) and in different indices
		int randomIndex1 = (Random() * G.deckCount[p]) - 1;
		G.deck[p][randomIndex1] = copper;
		int randomIndex2;
		do{
			randomIndex2 = (Random() * G.deckCount[p]) - 1;
		}while(randomIndex2 == randomIndex1);
		G.deck[p][randomIndex2] = copper;
		int randomIndex3;
		do{
			randomIndex3 = (Random() * G.deckCount[p]) - 1;
		}while(randomIndex3 == randomIndex1 || randomIndex3 == randomIndex2);
		G.deck[p][randomIndex3] = copper;
		
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		checkAdventurer(&G);
	}
	
	printf("ALL TESTS PASSED\n");
	
	return 0;
	}
}