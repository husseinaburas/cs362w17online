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
	printf("Starting unit test 4\n");
	printf("Subject: buyCard()\n");
		
	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	int r;
	
	
	struct gameState post;

	initializeGame(2, k, 1, &post);

	
	
	 

	/**********************************************************
	//Test to see when number of buys is 0
	**********************************************************/
	post.numBuys = 0;
	r = buyCard(estate, &post);
	assertTrue(r==-1, "Number of buys is 0 but no error on buy");


	/**********************************************************
	//Test if there are no cards in supply of that type 	
	**********************************************************/
	post.numBuys = 1;
	post.supplyCount[estate] = 0;
	r = buyCard(estate, &post);
	assertTrue(r==-1, "No cards left, but no error");

	/***********************************************************
	//Test if there are not sufficient coins
	**********************************************************/
	post.numBuys = 1;
	post.supplyCount[estate] = 1;
	post.coins = 0;
	r = buyCard(estate, &post);
	assertTrue(r==-1, "Insufficient funds, but no error");

	/******************************************************
	//Check numBuys decrements
	******************************************************/
	post.numBuys = 2;
	post.coins = 10;
	post.supplyCount[estate] = 1;

	r = buyCard(estate, &post);

	assertTrue(post.numBuys==1, "Number of buys didn't decrement");
	assertTrue(post.coins==8, "Number of coins didn't decrease");


	return 0;
}
