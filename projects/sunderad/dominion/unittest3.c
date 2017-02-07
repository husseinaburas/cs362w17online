#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

//---------------------------------
//Unit Test For Buy Card Function
//---------------------------------
int main(int argc, char const *argv[])
{
	int i, j, k, l;
	int errorFlag[3]={0,0,0};
	int players=2;
	int seed=999;
	struct gameState twoPlayerG, threePlayerG, fourPlayerG, copyG;
	int c[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	initializeGame(players, c, seed, &twoPlayerG);
	initializeGame((players+1), c, seed, &threePlayerG);
	initializeGame((players+2), c, seed, &fourPlayerG);

	printf("-----------------------------------------------------------------------\n");
	printf("Running Unit Test 3: Buy Card Function\n\n");
	printf("Testing buyCard(), Two Player Game\n");
	memcpy(&copyG, &twoPlayerG, sizeof(struct gameState));











	return 0;
}