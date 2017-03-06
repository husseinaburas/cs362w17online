/*
 * cardtest1.c
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

#define TESTCARD "outpost"

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

	
	// ----------- TEST 1: outpost flag set --------------
	printf("TEST 1: outpost flag set\n");
	
		// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
		//Setting what the output should be
	G.outpostPlayed = 1;
		//Trying the test
	cardEffect(outpost, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("outpostPlayed = %d, expected = %d\n", testG.outpostPlayed, G.outpostPlayed);
	assert(testG.outpostPlayed == G.outpostPlayed);

	// ----------- TEST 2: Testing if Discarded --------------
	printf("TEST 2: Testing if Discarded\n");

		// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
		//Setting what the output should be, handcount should be one less after running card effect
	G.handCount[thisPlayer] = G.handCount[thisPlayer] - 1;
		//trying the test
	cardEffect(outpost, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);

	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);



	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


