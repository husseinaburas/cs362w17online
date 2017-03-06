#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1
int ERROR = 0;
#undef assert
#define assert(x) if(!(x)){printf("Assertion Error!\n"); ERROR = 1; }

int PLAYER = 0;
int NUM_PLAYERS = 4;
int LAST_ENUM_VALUE = treasure_map;
int MAXHAND = 5;
int MIXED_DECK[] = {copper, council_room, feast, baron, cutpurse};

void reset(struct gameState *state)
{
	int i;
	for(i = 0; i < LAST_ENUM_VALUE; i++){
		state->supplyCount[i] = 10;
	}
}

int main () {
    int returnVal;
	struct gameState *state = malloc(sizeof(struct gameState));

	reset(state);
	
	//Supply piles all at 10, game not over
	returnVal = isGameOver(state);
	assert(returnVal == 0);
	
	state->supplyCount[adventurer] = 0;
	state->supplyCount[village] = 0;
	
	//Supply Count for only two piles is 0, game not over
	returnVal = isGameOver(state);
	assert(returnVal == 0);
	
	reset(state);
	
	state->supplyCount[province] = 0;
	
	//Province supply 0, game over
	returnVal = isGameOver(state);
	assert(returnVal == 1);
	
	reset(state);
	
	state->supplyCount[adventurer] = 0;
	state->supplyCount[village] = 0;
	state->supplyCount[feast] = 0;
	
	//Three decks 0, game over
	returnVal = isGameOver(state);
	assert(returnVal == 1);
	
	state->supplyCount[province] = 0;
	
	//Three decks + province, game still over
	returnVal = isGameOver(state);
	assert(returnVal == 1);
	
	free(state);
	
	if(!ERROR){
		printf("unittest4 finished successfully\n");
	} else{
		printf("unittest4 finished with errors\n");
	}
	
    return 0;
}
