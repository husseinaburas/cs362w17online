#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char ** argv){
	printf("******begin unit test on buyCard()******\n");
	
	//initialize game
	struct gameState G;
	int result, randomVar = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	randomVar = rand() % 10;
	result = initializeGame(2, k, randomVar, &G);
	int i;
	
	printf("testing successful buy\n");
	G.coins = 5;
	G.numBuys = 2;
	result = buyCard(1, &G);
	asserttrue(result == 0);
		
	printf("testing insufficient buys\n");
	G.coins = 5;
	G.numBuys = 0;
	result = buyCard(1, &G);
	asserttrue(result == -1);	
	
	printf("testing insufficient supply\n");
	G.coins = 5;
	G.numBuys = 1;
	for(i = 0; i < 100; i++) G.supplyCount[i] = 0;
	asserttrue(result == -1);	
	
	printf("testing insufficient coins\n");
	G.coins = 0;
	G.numBuys = 1;
	result = buyCard(1, &G);
	asserttrue(result == -1);	
	
	G.coins = 2;
	G.numBuys = 1;
	result = buyCard(3, &G);
	asserttrue(result == -1);	
	
	printf("******begin unit test on buyCard()******\n");
	return 0;
}