#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(){
	printf("------  updateCoins test ------\n");
	
	//initialize game
	int r;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	struct gameState G;
	r = initializeGame(2, k, 1, &G);

	printf("Player 1 has no cards, expect no coins\n");
	G.handCount[0] = 0;
	updateCoins(0, &G, 0);
	asserttrue(G.coins == 0);

	printf("Player 1 has a copper card\n");
	G.handCount[0] = 1;
	G.hand[0][0] = copper;
	updateCoins(0, &G, 0);
	asserttrue(G.coins == 1);

	printf("Player 1 has a silver card\n");
	G.handCount[0] = 1;
	G.hand[0][0] = silver;
	updateCoins(0, &G, 0);
	asserttrue(G.coins == 2);

	printf("Player 1 has a gold card\n");
	G.handCount[0] = 1;
	G.hand[0][0] = gold;
	updateCoins(0, &G, 0);
	asserttrue(G.coins == 3);

	printf("Player 1 has no card but has bonus\n");
	G.handCount[0] = 0;
	updateCoins(0, &G, 3);
	asserttrue(G.coins == 3);

	printf("Player 1 has a copper, silver, gold, and bonus \n");
	G.handCount[0] = 3;
	G.hand[0][0] = copper;
	G.hand[0][1] = silver;
	G.hand[0][2] = gold;
	updateCoins(0, &G, 3);
	asserttrue(G.coins == 9);
	

		
	printf("--------------- end --------------\n");
	return 0;
}