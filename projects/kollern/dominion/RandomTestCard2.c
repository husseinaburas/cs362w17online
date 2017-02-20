/*
* Card Test 3 - village
* Parameters: hand position of card to play, 3 optional choice fields, current game state
*/

/*
* Include the following lines in your makefile:
*
* RandomTestCard2: RandomTestCard2.c dominion.o rngs.o
*      gcc -o RandomTestCard2 -g  RandomTestCard2.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "VILLAGE"

int checkVillage(int p, struct gameState *post){
    int r;
    r = Village(p,post,p);
	if(r == 0){
		printf("VILLAGE SUCCEEDED");
	}else
	{
		printf("VILLAGE FAILED");		
	}
    return 0;
  
}

int main(int argc, char* argv[]){
	
	int i, n, r, p, deckCount, discardCount, handCount;
	int seed = 1000;
	//(int) argv[1]; // passed seed number

	int k[10] = { adventurer, remodel, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };
	
	struct gameState G, testG;
	
	// initializeGame(numPlayers, k, seed, &G);
	SelectStream(2);
	PutSeed(seed);
	// initialize a game state and player cards
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	
	for (n = 0; n < 2000; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		p = floor(Random() * 2);
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		checkVillage(p, &G); 
	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	exit(0);
  	
	return 0;
}