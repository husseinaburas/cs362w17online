/*
  unit test for isGameOver() 
  */ 

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
	
    int seed = 1000;
    int numPlayers = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
			 
			 
	// initialize a game state and player cards
	struct gameState G;
	
	printf("----------------- Testing Unit: isGameOver ----------------\n");
	
    initializeGame(numPlayers, k, seed, &G);
	
	
	// ----------- TEST 1: Testing if game ends with supply count province at 0 --------------
	printf("TEST 1: Testing if game ends with supply count province at 0\n");
	G.supplyCount[province]=0;
	printf("isGameOver() returns %d, expected = 1\n", isGameOver(&G));
	assert(isGameOver(&G) == 1);
	
	// ----------- TEST 2: Testing if game ends with 8 province  --------------
	printf("TEST 2: Testing if game ends with 8 province\n");
	G.supplyCount[province]=8;
	printf("isGameOver() returns %d, expected = 0\n", isGameOver(&G));
	assert(isGameOver(&G) == 0);
	
	// ----------- TEST 3: Testing if game ends when setting more than 3 out of 8 to zero --------------
	printf("TEST 3: Testing if game ends when setting more than 3 out of 8 to zero\n");
	G.supplyCount[province]=8;
	G.supplyCount[1]=0, G.supplyCount[2]=0, G.supplyCount[3]=0, G.supplyCount[4]=0;
	printf("isGameOver() returns %d, expected = 1\n", isGameOver(&G));
	assert(isGameOver(&G) == 1);
	
	printf("\n >>>>> SUCCESS: Testing complete for unittest1 <<<<<\n\n");
	return 0;
}
