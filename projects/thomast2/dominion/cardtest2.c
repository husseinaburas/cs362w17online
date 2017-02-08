//cardtest2.c
//smithy

#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {

	struct gameState state;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int x;

	initializeGame(2, k, 2, &state);

	x = numHandCards(&state);
	cardEffect(smithy, choice1, choice2, choice3, &state, NULL);

	if(numHandCards(&state) == x+2){
		printf("smithy: Test Passed\n");  
	}
	else{
		printf("smithy: Test Failed\n");
	}

	return 0;

}