/* Name: Parker Bruni
* CS362 Assignment 4
* Card Test: Village 
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#define TESTCARD "outpost"
#define NOISY_TEST 0 

void myAssert(int val);

int main() {
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed, i;
    int numPlayer;
    int thisPlayer;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	printf("___________Random Test for Outpost___________\n");

	for(i = 0; i < 2000; i++){
		srand(time(NULL)); //for new seeds
		seed = rand();
		// 4 players max
		numPlayer = rand() % 5;
		// choose a random player for testing, thisPlayer will get a random player from the total number of players;
		thisPlayer = rand() % numPlayer;
		initializeGame(numPlayer, k, seed, &G);
		//save copy of gamestate
		memcpy(&testG, &G, sizeof(struct gameState));
		
		//for the card to have worked appropriately, outpost played should always be 1
		G.outpostPlayed = 1;
		//G.handCount[thisPlayer] = G.handCount[thisPlayer] - 1;
		// this is the only variable we need to change,deck count and hand count will be the same

		cardEffect(outpost, choice1, choice2, choice3, &testG, handpos, &bonus);
		printf("outpostPlayed = %d, expected = %d\n", testG.outpostPlayed, G.outpostPlayed);
		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
		printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);

		assert(testG.outpostPlayed == G.outpostPlayed);
		assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);
		
		G.outpostPlayed = 0; //reset outpost played 
			
	}	
		
 
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
