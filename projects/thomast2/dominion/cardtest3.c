//cardtest3.c
//village

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main () {
		
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};

	int x;
	int y;
	
	struct gameState before;
	struct gameState after;

	initializeGame(2, k, 1, &before);
	memcpy (&before, &after, sizeof(struct gameState));

	after.deckCount[0] = 3;
	before.deckCount[0] = 3;
	after.hand[0][0] = village;
	before.whoseTurn = 0;
		
	//test for numActions
	
	x = before.numActions;
	y = after.numActions;
	
	if((x+2) == y){
		printf("village: Test Passed\n");
	}
	else{
		printf("village: Test Failed\n");
	}

	return 0;
}