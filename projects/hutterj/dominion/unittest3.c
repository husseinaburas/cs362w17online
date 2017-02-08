/*
Author: hutterj
Date: 2017.02.07
File: unittest3.c
Purpose: Perform unit tests of function isGameOver in dominion.c

Rules of isGameOver:
	no province cards left = over
	3 or more supplyCount piles empty = over
	game state should remain the same after isGameOver check
	
		
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


/*
Name: asserttrue
Purpose:  use something like assert to check conditions
but still be able to collect coverage
*/
void asserttrue(int condition, char* condName){
	if (condition){
		printf("Test: %-33s success.\n", condName);
	}
	else {
		printf("Test: %-33s FAIL.\n", condName);
	}
	return;
}

int main(void){
    int seed = 1000;
    int numPlayers = 2;
	int funcStatus, i;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing Function: isGameOver ----------------\n");
	printf("TEST 1: province pile\n");
	asserttrue((G.supplyCount[province] == 8), " 8 in province pile");
	funcStatus = isGameOver(&G);
	asserttrue((funcStatus == 0), "game not over");
	
	// -1 provinces (weird but let's account for it because edge cases)
	G.supplyCount[province] = -1;
	asserttrue((G.supplyCount[province] == -1), "-1 in province pile");
	funcStatus = isGameOver(&G);
	asserttrue((funcStatus == 1), "game over");
	
	// 0 provinces 
	G.supplyCount[province] = 0;
	asserttrue((G.supplyCount[province] == 0), " 0 in province pile");
	funcStatus = isGameOver(&G);
	asserttrue((funcStatus == 1), "game over");
	
	printf("\n\nTEST 2: 3 or more empty piles\n");
	//piles empty with 0
	initializeGame(numPlayers, k, seed, &G);
	for (i = 0; i < 5; i++){
		G.supplyCount[i] = 0;
		asserttrue((G.supplyCount[i] == 0), "pile emptied 0");
	}
	funcStatus = isGameOver(&G);
	asserttrue((funcStatus == 1), "game over");
	
	// piles empty with -1
	initializeGame(numPlayers, k, seed, &G);
	for (i = 0; i < 5; i++){
		G.supplyCount[i] = -1;
		asserttrue((G.supplyCount[i] <= 0), "pile emptied -1");
	}
	funcStatus = isGameOver(&G);
	asserttrue((funcStatus == 1), "game over");
	
	// just 2 piles empty
	initializeGame(numPlayers, k, seed, &G);
	for (i = 0; i < 2; i++){
		G.supplyCount[i] = 0;
		asserttrue((G.supplyCount[i] <= 0), "pile emptied  0");
	}
	funcStatus = isGameOver(&G);
	asserttrue((funcStatus == 0), "game not over");
	
	printf("\n\n\n");
		
	return 0;
	

}


