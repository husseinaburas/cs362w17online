#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "asserttrue.h" //Custom assert macro


#define DEBUG 0
#define NOISY_TEST 1


int main () {
	printf("Starting unit test 2\n");
	printf("Subject: updateCoins()\n");

	
	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	struct gameState G;

	initializeGame(2, k, 1, &G);
	G.coins = 0;

	/*************************************
	//Test calculation of one card
	*************************************/
	G.hand[0][0] = copper;
	G.hand[0][1] = -1;
	G.hand[0][2] = -1;
	G.hand[0][3] = -1;
	G.hand[0][4] = -1;

	updateCoins(0, &G, 0);
	assertTrue(G.coins == 1, "Copper not calculated correctly");	
	
	G.hand[0][0] = silver;
	G.hand[0][1] = -1;
	G.hand[0][2] = -1;
	G.hand[0][3] = -1;
	G.hand[0][4] = -1;
	updateCoins(0, &G, 0);

	assertTrue(G.coins == 2, "Silver not calculated correctly");	
	

	G.hand[0][0] = gold;
	G.hand[0][1] = -1;
	G.hand[0][2] = -1;
	G.hand[0][3] = -1;
	G.hand[0][4] = -1;

	updateCoins(0, &G, 0);
	assertTrue(G.coins == 3, "Gold not calculated correctly");	
	

	/***********************************
	//Test for multiple treasure cards
	***********************************/
	G.hand[0][0] = copper;
	G.hand[0][1] = copper;
	G.hand[0][2] = copper;
	G.hand[0][3] = copper;
	G.hand[0][4] = copper;

	updateCoins(0, &G, 0);
	assertTrue(G.coins == 5, "Multiple copper not added correctly"); 
	
	
	//Test for multiple varied treasure cards
	G.hand[0][0] = silver;
	G.hand[0][1] = copper;
	G.hand[0][2] = gold;
	G.hand[0][3] = gold;
	G.hand[0][4] = copper;

	updateCoins(0, &G, 0);
	assertTrue(G.coins == 10, "Multiple varied not added correctly"); 
	



	/**********************************
 	//Test for added bonus with no coins
 	**********************************/
	G.hand[0][0] = -1;
	G.hand[0][1] = -1;
	G.hand[0][2] = -1;
	G.hand[0][3] = -1;
	G.hand[0][4] = -1;

	updateCoins(0, &G, 3);
	assertTrue(G.coins == 3, "Bonus not calculated correctly");	

	printf("\n\n");
	
	return 0;
}
