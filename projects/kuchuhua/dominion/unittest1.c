/*
 *
 * unittest1.c supplyCount()
 * 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "supplyCount"
	
	//Custom assert function
void cus_assert(int test)
{
	if (test == 0) {
		printf ("Test Failed");
	}
	return;
}
int main() {
	int card;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards 
	initializeGame(numPlayers, k, seed, &G);

	printf("------------------------- Testing Unit: %s -----------------------\n", TESTCARD);
	
...	//test each card for supply count and no change to gameState after call to gameState
	
	//adventurer card
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//make sure supply count is correct
		card = supplyCount(adventurer, &G);
		cus_assert(card == 10);
		
		//setting a custom card sum
		G.supplyCount[adventurer] = 6; 
		cus_assert(supplyCount(adventurer, &G) == 6);
		
    //---------------------------------------------------------------------------------------------	
			
	//smithy card
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

		//make sure supply count is correct
		card = supplyCount(smithy, &G);
		cus_assert(card == 10);
	
		//setting a custom card sum
		G.supplyCount[smithy] = 6;
		cus_assert(supplyCount(smithy, &G) == 6);
	
	//---------------------------------------------------------------------------------------------
	
	//mine card 
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//make sure the supply count is correct
		card = supplyCount(mine, &G);
		cus_assert(card == 10);
	
	//setting a custom card sum
		G.supplyCount[mine] = 6;
		cus_assert(supplyCount(mine, &G) == 6); 
	//-----------------------------------------------------------------------------------------------
	
	
	//village card 
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//make sure the supply count is correct
		card = supplyCount(village, &G);
		cus_assert(card == 10);
	
	//setting a custom card sum
		G.supplyCount[village] = 6;
		cus_assert(supplyCount(village, &G) == 6); 
	//-----------------------------------------------------------------------------------------------
	
	
	//minion card 
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//make sure the supply count is correct
		card = supplyCount(minion, &G);
		cus_assert(card == 10);
	
	//setting a custom card sum
		G.supplyCount[minion] = 6;
		cus_assert(supplyCount(minion, &G) == 6); 
	//-----------------------------------------------------------------------------------------------
	
	//cutpurse card 
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//make sure the supply count is correct
		card = supplyCount(cutpurse, &G);
		cus_assert(card == 10);
	
	//setting a custom card sum
		G.supplyCount[cutpurse] = 6;
		cus_assert(supplyCount(cutpurse, &G) == 6); 
	//-----------------------------------------------------------------------------------------------	
 		
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
	
	/*
	
	int supplyCount(int card, struct gameState *state) {
		return state->supplyCount[card];
		}

	*/
}
