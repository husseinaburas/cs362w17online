/* matthew hillman
 * unittest4.c whoseTurn()
 * 
 */

  
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTUNIT "whoseTurn"

void my_assert(int test, char* msg)
{
	if (!test) {
		printf ("ASSERT HAS FAILED: %s\n", msg);
	}
	return;
}

int main() {
	int i, r;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

// initialize a game state 
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Unit: %s ----------------\n", TESTUNIT);
	

// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
//verify that function returns correct results for turns of different values
	int turn = 0;
	for (i = 0; i < 25; i++){
		testG.whoseTurn = turn;
		r = whoseTurn(&testG);
		my_assert(r == turn, "msg1");
		turn++;
	}
	
// reset testG.whoseTurn to zero and verify that other gameState variables have 
// not changed by call
		
		testG.whoseTurn = 0;
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg2");  		
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTUNIT);


	return 0;
}


