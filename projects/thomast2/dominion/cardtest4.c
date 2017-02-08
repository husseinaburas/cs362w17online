//cardtest4.c
//council_room

#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main () {
	struct gameState state;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
		sea_hag, tribute, smithy};
	
	initializeGame(2, k, 2, &state);
	
	state.numBuys = 0;
	int x;
	x = state.handCount[0];
	
	int card = council_room;
	state.hand[0][0] = card;
	playCard(0,0,0,0,&state);
	
	if (state.numBuys == 1){
		printf("council_room: Test 1 Passed\n");
	}
	else{
		printf("council_room: Test 1 Failed\n");
	}
	if (state.handCount[0] == 8){
		printf("council_room: Test 2 Passed\n");
	}
	else{
		printf("council_room: Test 2 Failed\n");
	}
	if (state.handCount[1] == 6){
		printf("council_room: Test 3 Passed\n");
	}
	else{
		printf("council_room: Test 3 Failed\n");
	}
	
	
	return 0;
}	