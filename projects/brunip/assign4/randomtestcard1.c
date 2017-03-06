/* Name: Parker Bruni
* CS362 Assignment 4
* Card Test: Village 
*/

#include "dominion.h"
#include <string.h>
#include "rngs.h"
#include "dominion_helpers.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define TESTCARD "Village"
#define NOISY_TEST 0 

void myAssert(int val);

int main(){
	int i, j, numPlayer, choice;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int seed;
    int thisPlayer;
	struct gameState G, testG;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	
	printf("___________Random Test for Village___________\n");
	
	for(i = 0; i < 2000; i++){
		//for new seeds
		srand(time(NULL));
		seed = rand();
		// 4 players max
		numPlayer = rand() % 5;
		// choose a random player for testing, thisPlayer will get a random player from the total number of players;
		thisPlayer = rand() % numPlayer;
		initializeGame(numPlayer, k, seed, &G);
		//save copy of gamestate
		memcpy(&testG, &G, sizeof(struct gameState));

		
		//now that we have generated a randomized gamestate, check card effects
		G.numActions = G.numActions + 2;
		
		cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

		//handcount should be the same, action count should be +2
		printf("action count = %d, expected = %d\n", testG.numActions, G.numActions);
		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);

		assert(testG.numActions == G.numActions);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
		
	}

	return 0;	
}


void myAssert(int num){
	if(num == 1){
		printf("TEST PASSED\n");
	}else{
		printf("ASSERTION FAILURE\n");
	}
}