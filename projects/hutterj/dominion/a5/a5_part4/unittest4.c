/*
Author: hutterj
Date: 2017.02.07
File: unittest3.c
Purpose: Perform unit tests of function updateCoins in dominion.c

Rules of updateCoins:
	coins reset from previous state
	copper adds 1
	silver adds 2
	gold adds 3
	bonus added
		
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
    int funcStatus;
	int thisPlayer = 0;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	thisPlayer = whoseTurn(&G);
	
	printf("----------------- Testing Function: updateCoins ----------------\n");
	
	printf("TEST 1: reset coins from previous state\n");
	G.coins = 50;
	// discard 5 times
	asserttrue((discardCard(0, thisPlayer, &G, 0)==0), "discard hand index 0");
	asserttrue((discardCard(0, thisPlayer, &G, 0)==0), "discard hand index 0");
	asserttrue((discardCard(0, thisPlayer, &G, 0)==0), "discard hand index 0");
	asserttrue((discardCard(0, thisPlayer, &G, 0)==0), "discard hand index 0");
	asserttrue((discardCard(0, thisPlayer, &G, 0)==0), "discard hand index 0");
	
	
	funcStatus = updateCoins(thisPlayer, &G, 0);
	asserttrue((funcStatus == 0), "update coins with empty hand");
	asserttrue((G.coins == 0), "resulting coin count is 0");
	
	printf("\n\nTEST 2: copper adds 1\n");
	asserttrue(gainCard(copper, &G, 2, thisPlayer)==0, "added copper to hand");
	funcStatus = updateCoins(thisPlayer, &G, 0);
	asserttrue((funcStatus == 0), "update coins with 1 copper hand");
	asserttrue((G.coins == 1), "resulting coin count is 1");
	
	// 2 copper
	asserttrue(gainCard(copper, &G, 2, thisPlayer)==0, "added copper to hand");
	funcStatus = updateCoins(thisPlayer, &G, 0);
	asserttrue((funcStatus == 0), "update coins with 2 copper n hand");
	asserttrue((G.coins == 2), "resulting coin count is 2");
	
	
	
	printf("\n\nTEST 3: silver adds 2\n");
	asserttrue((discardCard(0, thisPlayer, &G, 0)==0), "discard hand index 0");
	asserttrue((discardCard(0, thisPlayer, &G, 0)==0), "discard hand index 0");
	asserttrue(gainCard(silver, &G, 2, thisPlayer)==0, "added silver to hand");
	funcStatus = updateCoins(thisPlayer, &G, 0);
	asserttrue((funcStatus == 0), "update coins with 1 silver hand");
	asserttrue((G.coins == 2), "resulting coin count is 2");
	
	
	printf("\n\nTEST 4: gold adds 3\n");
	asserttrue((discardCard(0, thisPlayer, &G, 0)==0), "discard hand index 0");
	asserttrue(gainCard(gold, &G, 2, thisPlayer)==0, "added gold to hand");
	funcStatus = updateCoins(thisPlayer, &G, 0);
	asserttrue((funcStatus == 0), "update coins with 1 gold hand");
	asserttrue((G.coins == 3), "resulting coin count is 3");
	
	
	printf("\n\nTEST 5: bonus added\n");
	asserttrue((discardCard(0, thisPlayer, &G, 0)==0), "discard hand index 0");
	asserttrue(gainCard(gold, &G, 2, thisPlayer)==0, "added gold to hand");
	asserttrue(gainCard(silver, &G, 2, thisPlayer)==0, "added silver to hand");
	asserttrue(gainCard(silver, &G, 2, thisPlayer)==0, "added silver to hand");
	asserttrue(gainCard(copper, &G, 2, thisPlayer)==0, "added copper to hand");
	// update, with 10 bonus
	funcStatus = updateCoins(thisPlayer, &G, 10);
	asserttrue((funcStatus == 0), "update coins with multiple hand");
	asserttrue((G.coins == 18), "resulting coin count is 18");
	
	
	printf("\n\n\n");
		
	return 0;
	

}


