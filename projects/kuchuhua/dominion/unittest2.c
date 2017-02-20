/* 
 *
 * unittest2.c whoseTurn()
 * 
 */

  
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "whoseTurn"

void cus_assert(int test)
{
	if (test == 0) {
		printf ("Test Failed");
	}
	return;
}

int main() {
	int num;
	int state;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int turn = 0;

// initialize a game state 
	initializeGame(numPlayers, k, seed, &G);
	

	printf("------------------------- Testing Unit: %s -----------------------\n", TESTCARD);
	

// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
		
		testG.whoseTurn = 0;
		cus_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0);  

//Test to make sure the turns progress
	for (num = 0; num = 30; num = num + 1) {
		G.whosTurn = num;
		cus_assert(G.whosTurn == whoseTutn(&G))
		}

	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);



	return 0;
	
	/*
	
	int whoseTurn(struct gameState *state) {
		return state->whoseTurn;
		}
	
	*/
}

