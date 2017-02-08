/*
 * cardtest3.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	
	// ----------- TEST 1: Testing if 3 cards were drawn and one discarded(handcount +2)--------------
	printf("TEST 1: Testing if 3 cards were drawn and one discarded (+2 cards)\n");
	
		// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
		//Setting what the handcount should be
	G.handCount[thisPlayer] = G.handCount[thisPlayer] + 2;
		//Trying the test
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);

	// ----------- TEST 2: Testing if deckcount decreased by 3 --------------
	printf("TEST 2: Testing if deckCount decreased by 3\n");

		// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
		//Setting what the deck count and discard count should be
	G.deckCount[thisPlayer] = G.deckCount[thisPlayer] - 3;
		
		//trying the test
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("deckCount = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);

	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);
	


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


