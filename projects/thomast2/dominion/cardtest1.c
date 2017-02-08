//cardtest.c
//adventurer

#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


int main (int argc, char** argv) {

	struct gameState state;
	int choice1 = 0, choice2 = 0, choice3 = 0;

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};

	initializeGame(2, k, 4, &state);

	if(cardEffect(adventurer, choice1, choice2, choice3, &state, 0, NULL) == 0){
		printf("adventurer: Test Passed\n");
	}
	else{
		printf("adventurer: Test Failed\n");
	}
	return 0;
}