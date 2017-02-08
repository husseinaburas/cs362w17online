#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//great hall test
int main()
{
	
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {copper, minion, mine, silver, gold, cutpurse,
		sea_hag, tribute, smithy, council_room};
	
	//printf("first test:%d, testG.handCount[testG.whoseTurn])
	printf("** Card Test 4: Great Hall **\n");
	
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	greatHallCard(&testG, 0);
	printf("Expected: %d, Result: %d\n", G.handCount[G.whoseTurn] + 1, testG.handCount[testG.whoseTurn]);
	
	//printf("second test:%d, testG.handCount[testG.whoseTurn])
	memcpy(&testG, &G, sizeof(struct gameState));
	greatHallCard(&testG, 0);
     
	
	printf("Final expected action count: %d, Result: %d\n", G.numActions + 1, testG.numActions);
	
	printf("** End Card Test 4: Great Hall **\n");
	
	return 0;
}
