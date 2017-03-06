#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int testAll(int numP, int seed);

int main()
{
	printf("-----unittest3-----\n");	
	
	if (testAll(0, 1111) == 0 && testAll(1, 1111) == 0 && testAll(-1, 1111) > 0 && testAll(5, 1111) > 0 &&
 		testAll(2147483648, 1111) > 0 && testAll(-2147483648, 1111) > 0)
	{
		printf("----------Passed----------\n");
	}	
	else
	{
		printf("----------Failed----------\n");
		printf("whoseTurn returns %i \n",testAll(0, 1111)); //no players 
		printf("whoseTurn returns %i \n",testAll(1, 1111)); //1 player
		printf("whoseTurn returns %i \n",testAll(-1, 1111)); //checking negative number of players
		printf("whoseTurn returns %i \n",testAll(5, 1111)); //checking too many players
		printf("whoseTurn returns %i \n",testAll(2147483648, 1111)); //checking 4 byte int max
		printf("whoseTurn returns %i \n",testAll(-2147483648, 1111)); //checking 4 byte int min

	}

	return 0;
}

int testAll(int numP, int seed)
{
	//printf("testing scoreFor with %i players, seed of %i\n", numP, seed);
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
	initializeGame(numP, k, seed, &G);
	//memcpy(&G2, &G, sizeof(struct gameState)); 
	return whoseTurn(&G);

}
