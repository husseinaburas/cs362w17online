#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

// unit 3 tests if the player is finished with their turn
int main(int argc, char** argv)
{
	struct gameState state;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
	int a = initializeGame(2, k, 3, &state);
	
	printf("\n** Unit Test 3: Turn Over? **\n");

	int j = isGameOver(&state);
	assert(j == 0);
	printf("\nTest Passed\n");

	printf("\n** End of Unit Test 3: Turn over? **\n"); 
	
	assert(a == 0);
	return 0;
} 