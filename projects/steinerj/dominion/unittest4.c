#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int testAll(int numP, int seed, int player);

int main()
{
	printf("-----unittest4-----\n");
	if(testAll(2, 1111, 0) == 0 && testAll(2, 1111, 1) == 2 && testAll(2, 1111, -1) == -1 &&
		testAll(2, 1111, 27) == -1 && testAll(2, 1111, 2147483647) == -1 && 
		testAll(2, 1111, -2147483648) == -1 && testAll(2, 1111, 26) == 4)
	{
		printf("----------Passed----------\n");
	}
	else
	{
		printf("----------Failed----------\n");
	}

	return 0;
}

int testAll(int numP, int seed, int cardNum)
{
	printf("----------testing getCost with card number %i \n", cardNum);
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
	initializeGame(numP, k, seed, &G);
	//memcpy(&G2, &G, sizeof(struct gameState)); 
	return getCost(cardNum);

}
