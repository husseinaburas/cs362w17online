/*
 * unittest4.c (supplyCount)
 * 
 */

  
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTUNIT "supplyCount"

void my_assert(int test, char* msg)
{
	if (!test) {
		printf ("ASSERT HAS FAILED: %s\n", msg);
	}
	return;
}

int main() {
	int r;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

// initialize a game state 
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Unit: %s ----------------\n", TESTUNIT);
	
//test each card for supply count and no change to gameState after call to gameState
	
//adventurer
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//verify supply count is correct
		r = supplyCount(adventurer, &G);
		printf ("supplyCount(adventurer, &G) = %d\n", r);
		my_assert(r == 10, "msg1");
	
	//verify that gameState has not changed by call
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg2");  
	
	
//embargo
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//verify supply count is correct
		r = supplyCount(embargo, &G);
		printf ("supplyCount(embargo, &G) = %d\n", r);
		my_assert(r == 10, "msg1");
	
	//verify that gameState has not changed by call
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg2");  
		 	
	
//village
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//verify supply count is correct
		r = supplyCount(village, &G);
		printf ("supplyCount(village, &G) = %d\n", r);
		my_assert(r == 10, "msg1");
	
	//verify that gameState has not changed by call
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg2");  
	
	
//minion
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//verify supply count is correct
		r = supplyCount(minion, &G);
		printf ("supplyCount(minion, &G) = %d\n", r);
		my_assert(r == 10, "msg1");
	
	//verify that gameState has not changed by call
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg2");  
		
//mine
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//verify supply count is correct
		r = supplyCount(mine, &G);
		printf ("supplyCount(mine, &G) = %d\n", r);
		my_assert(r == 10, "msg1");
	
	//verify that gameState has not changed by call
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg2"); 

//cutpurse
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//verify supply count is correct
		r = supplyCount(cutpurse, &G);
		printf ("supplyCount(cutpurse, &G) = %d\n", r);
		my_assert(r == 10, "msg1");
	
	//verify that gameState has not changed by call
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg2");  	

//sea_hag
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//verify supply count is correct
		r = supplyCount(sea_hag, &G);
		printf ("supplyCount(sea_hag, &G) = %d\n", r);
		my_assert(r == 10, "msg1");
	
	//verify that gameState has not changed by call
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg2");  

//tribute
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//verify supply count is correct
		r = supplyCount(tribute, &G);
		printf ("supplyCount(tribute, &G) = %d\n", r);
		my_assert(r == 10, "msg1");
	
	//verify that gameState has not changed by call
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg2");  

//smithy
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//verify supply count is correct
		r = supplyCount(smithy, &G);
		printf ("supplyCount(smithy, &G) = %d\n", r);
		my_assert(r == 10, "msg1");
	
	//verify that gameState has not changed by call
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg2");  

//council_room
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//verify supply count is correct
		r = supplyCount(council_room, &G);
		printf ("supplyCount(council_room, &G) = %d\n", r);
		my_assert(r == 10, "msg1");
	
	//verify that gameState has not changed by call
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg2");  		
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTUNIT);


	return 0;
}


