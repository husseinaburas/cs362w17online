/* Testing the isGameOver function*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
	
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy, council_room};

	int numPlayers = 2;
	int seed = 10;

	initializeGame(numPlayers, k, seed, &G);
	
	printf("++++++++++++ TESTING isGameOver Function ++++++++++++++++\n");

	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("Starting Test 1: Setting Province count to 0\n");
	testG.supplyCount[3] = 0;

	int over = isGameOver(&testG);
	
	if(over)
	{
		printf("The game is over\n");
	}
	assertTrue(1, over);

	printf("------------------------------------------------------------------\n");

	printf("Starting Test 2: Setting 3 supply card counts to 0\n");

	memcpy(&testG, &G, sizeof(struct gameState));
	
	testG.supplyCount[4] = 0;
	testG.supplyCount[6] = 0;
	testG.supplyCount[0] = 0;
	
	over = isGameOver(&testG);
	
	if(over)
	{
		printf("The game is over\n");
	}
	assertTrue(1, over);

	printf("------------------------------------------------------------------\n");



	printf("Starting Test 3: Didn't touch the supply count of any card.\n");
	
	memcpy(&testG, &G, sizeof(struct gameState));
	
	over = isGameOver(&testG);

	if(over)
	{
		printf("game is over\n");
	}
	else
	{
		printf("game is not over\n");
	}
	assertTrue(0, over);
	
	printf("------------------------------------------------------------------\n");
	
	printf("Starting Test 4: Setting 1 supply card counts to 0 this not Province\n");

	memcpy(&testG, &G, sizeof(struct gameState));
	
	testG.supplyCount[4] = 0;
	
	over = isGameOver(&testG);
	
	if(over)
	{
		printf("The game is over\n");
	}
	else
	{
		printf("The game is not over\n");
	}
	assertTrue(0, over);

	printf("------------------------------------------------------------------\n");
	
	
	printf("Starting Test 5: Setting 2 supply card counts to 0\n");

	memcpy(&testG, &G, sizeof(struct gameState));
	
	testG.supplyCount[4] = 0;
	
	over = isGameOver(&testG);
	
	if(over)
	{
		printf("The game is over\n");
	}
	else
	{
		printf("The game is not over\n");
	}
	assertTrue(0, over);

	printf("------------------------------------------------------------------\n");
	
	
	return 0;
}



