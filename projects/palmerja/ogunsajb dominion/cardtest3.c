#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//village card test
int main()
{
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {copper, minion, mine, silver, gold, cutpurse,
		sea_hag, tribute, smithy, council_room};

	//printf("first test:%d, testG.handCount[testG.whoseTurn])
	printf("** Card Test 3: Village **\n");
	
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	villageCard(&testG, 0);
	printf("Expected value: %d, Result: %d\n", G.handCount[G.whoseTurn] + 1, testG.handCount[testG.whoseTurn]);

	memcpy(&testG, &G, sizeof(struct gameState));
	villageCard(&testG, 0);
    
	//printf("final test:%d, testG.handCount[testG.whoseTurn])
	printf("Final Expected action count: %d, Result: %d\n", G.numActions + 2, testG.numActions);
	
	printf("** End Card Test 3: Village **\n");
	return 0;
}