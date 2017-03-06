#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int testAll(int numP, int seed, int player, int card);

int main()
{
	printf("-----unittest2-----\n");
	if(testAll(2, 1111, 2, 0) >= 0)//&& testAll(2, 1111, 2, -1) < 0 && testAll(2, 1111, 2, 1) > 0 &&
		//testAll(2, 1111, 2, 4) > 0 && testAll(3, 1111, 2, 0) >= 0 && testAll(3, 1111, 2, 1) >= 0 &&
		//testAll(3, 1111, 2, 41) < 0)

	{
		printf("----------Passed----------\n");
	}
	else
	{
		printf("----------Failed----------\n");
	}
	printf("fullDeckCount returns %i \n",testAll(2, 1111, 2, 0)); //curse should be 0
	//printf("fullDeckCount returns %i \n",testAll(2, 1111, 2, -1)); //invalid should be error
	printf("fullDeckCount returns %i \n",testAll(2, 1111, 2, 1));
	printf("fullDeckCount returns %i \n",testAll(2, 1111, 2, 4));
	printf("fullDeckCount returns %i \n",testAll(3, 1111, 2, 0));
	printf("fullDeckCount returns %i \n",testAll(3, 1111, 2, 1));
	printf("fullDeckCount returns %i \n",testAll(3, 1111, 2, 41));

	return 0;
}

int testAll(int numP, int seed, int player, int card)
{
	//printf("testing fullDeckCount with %i players,current player %i, and card %i \n", numP, player, card);
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
	initializeGame(numP, k, seed, &G);
	//memcpy(&G2, &G, sizeof(struct gameState)); 
	return fullDeckCount(player, card, &G);

}
