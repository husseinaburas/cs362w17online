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
	printf("Starting unit test 3\n");
	printf("Subject: isGameOver()\n");
	int r = 0;
	
	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	struct gameState G;

	initializeGame(2, k, 1, &G);
	/*******************************************
	//Test win condition province being empty
	*******************************************/

	G.supplyCount[province] = 0;
	r = isGameOver(&G);
	assertTrue(r==1, "Province being empty and no win"); 

	initializeGame(2, k, 1, &G);
	/*******************************************
	//Test win condition province being negative
	*******************************************/

	G.supplyCount[province] = -1;
	r = isGameOver(&G);
	assertTrue(r==1, "Province being negative and no win"); 


	initializeGame(2, k, 1, &G);
	/**********************************************
 	//Test win condition 3 supply piles being empty
 	**********************************************/
 	G.supplyCount[curse] = 0;
	G.supplyCount[estate] = 0;
	G.supplyCount[copper] = 0;
	r = isGameOver(&G);
	assertTrue(r==1, "3 supply piles being empty and no win");

	initializeGame(2, k, 1, &G);
	/***********************************************
 	//Test no win condition, no empty piles 
 	************************************************/ 
	r = isGameOver(&G);
	assertTrue(r==0, "False win condition detected. No empty supply piles"); 	
	
	initializeGame(2, k, 1, &G);
	/***********************************************
 	//Test no win condition 2 empty piles 
	***********************************************/
	G.supplyCount[curse] = 0;
	G.supplyCount[gold] = 0;
	r = isGameOver(&G);
	assertTrue(r==0, "False win condition. 2 empty piles");

	printf("\n\n");

	return 0;
}
