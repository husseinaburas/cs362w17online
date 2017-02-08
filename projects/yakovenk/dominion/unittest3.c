
//Konstantin Yakovenko
//2k17/02/07
//Unit Test for isGameOver()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
//setup the environment
//initialize the game state to where we could test the function under different game states
	int failFlag = 0; 

	//input: (int player, struct gameState *state, int bonus)
	int numPlayers = 2;
	int thisPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
				sea_hag, tribute, smithy, council_room};
	int seed = 1000;

	struct gameState G;	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	//run unit tests
	//things we can test: province cards > 0, == 0 
	//1 supply pile at 0, 2... 3.. 4...
	printf("\n----------------- Test Function: isGameOver() ----------------\n");

	// ----------- TEST 1  --------------
	printf("TEST 1: Province Cards > 0\n");

	//setup the testing situation
	G.supplyCount[province] = 1;

	//check.
	printf("Provinces, should be 1 and Game Not Over: %d -- ", G.supplyCount[province]);  

	//output results
	failFlag += assertTrue(isGameOver(&G) == 0);


	// ----------- TEST 2  --------------
	printf("\nTEST 2: Province Cards == 0\n");

	//setup the testing situation
	G.supplyCount[province] = 0;

	//check.
	printf("Provinces, should be 0 and Game Over: %d -- ", G.supplyCount[province]);  

	//output results
	failFlag += assertTrue(isGameOver(&G) == 1);


	// ----------- TEST 3  --------------
	G.supplyCount[province] = 8; // just return the provinces back to a reasonable count.

	int i;
	for(i = 1; i <= 4; i++){
		printf("\nTEST 3.%d: Various number of supply piles going to 0: \n", i);

		//setup the testing situation
		G.supplyCount[i] = 0;

		//check.
		printf("Number of supply cards at 0: %d, is game over: %d -- ", i, isGameOver(&G));  

		//if 3 piles are empty we should get a GameOver.
		if(i >= 3){
			failFlag += assertTrue(isGameOver(&G) == 1);
		}else{
			failFlag += assertTrue(isGameOver(&G) == 0);
		}
	}



	printf("\n UNIT TESTS for updateCoins(): ");
	assertTrue(failFlag == 0);
	printf("\n");
	

	return 0;
}

