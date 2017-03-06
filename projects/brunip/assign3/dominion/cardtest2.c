/*
 * cardtest2.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

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

	
	// ----------- TEST 1: Testing if a card was drawn  and then a card was discarded, hand should be same amount as when village was played--------------
	printf("TEST 1: Testing if a card was drawn\n");
	
		// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
		//Setting what the handcount; the same lol
	G.handCount[thisPlayer] = G.handCount[thisPlayer];
		//Trying the test
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);

	// ----------- TEST 2: Testing if +2 actions --------------
	printf("TEST 2: Testing if +2 actions\n");

		// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
		//Setting what the num actions should be
	G.numActions = G.numActions + 2;
		//trying the test
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("numActions = %d, expected = %d\n", testG.numActions, G.numActions);

	assert(testG.numActions == G.numActions);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


