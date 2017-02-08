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
	printf("-----unittest1-----\n");
	if(testAll(0, 1111, 2) < 0 && testAll(1, 1111, 1) >= 0 && testAll(2, 1111, 1) >= 0 &&
		testAll(-1, 1111, 1) > 0 &&	testAll(5, 1111, 1) >=0 && testAll(2147483648, 1111, 1) >=0 &&
		testAll(-2147483648, 1111, 1) < 0)
	{
		printf("----------Passed----------\n");
	}
	else
	{
		printf("----------Failed----------\n");
		printf("scoreFor returns %i \n",testAll(0, 1111, 2)); //no players checking player 2
		printf("scoreFor returns %i \n",testAll(1, 1111, 1)); //checking only players score
		printf("scoreFor returns %i \n",testAll(2, 1111, 1)); //checking normal game
		printf("scoreFor returns %i \n",testAll(-1, 1111, 1)); //checking negative number of players
		printf("scoreFor returns %i \n",testAll(5, 1111, 1)); //checking too many players
		printf("scoreFor returns %i \n",testAll(2147483648, 1111, 1)); //checking 4 byte int max
		printf("scoreFor returns %i \n",testAll(-2147483648, 1111, 1)); //checking 4 byte int min
	}
	return 0;
}

int testAll(int numP, int seed, int player)
{
	printf("testing scoreFor with %i players, seed of %i, and current player %i \n", numP, seed, player);
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
	initializeGame(numP, k, seed, &G);
	//memcpy(&G2, &G, sizeof(struct gameState)); 
	return scoreFor(player, &G);

}
