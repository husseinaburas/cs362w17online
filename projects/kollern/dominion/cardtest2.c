/*
* Card Test 2 - adventurer
* Parameters: hand position of card to play, 3 optional choice fields, current game state
*/

/*
* Include the following lines in your makefile:
*
* cardtest2: cardtest2.c dominion.o rngs.o
*      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
	int newCards = 0;
	int discarded = 1;
	int xtraCoins = 0;
	int shuffledCards = 0;

	int i, j, m;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int remove1, remove2;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = { adventurer, remodel, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST a: This Player plays adventurer --------------
	printf("Test a: This Player uses adventurer and it moves from hand to Discard\n");

	G.hand[thisPlayer][0] = adventurer;
	G.hand[thisPlayer][1] = copper;
	G.hand[thisPlayer][2] = duchy;
	G.hand[thisPlayer][3] = estate;
	G.hand[thisPlayer][4] = village;

	// copy the game state to a test case - Control
	memcpy(&testG, &G, sizeof(struct gameState));
	playCard(0, -1, -1, -1, &testG);

	newCards = 3;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	printf("Discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	printf("Action Count = %d, expected = %d\n", testG.numActions, G.numActions - 1);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	//assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);
	assert(testG.discardCount[thisPlayer] == (G.discardCount[thisPlayer]));
	assert(testG.numActions == (G.numActions - 1));
	//assert(testG.coins == G.coins + xtraCoins);

	// ----------- TEST b: Other State's Conditions --------------
	printf("Test b: Other State's Conditions\n");

	printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
	printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
	printf("copper count = %d, expected = %d\n", testG.supplyCount[copper], G.supplyCount[copper]);
	printf("silver count = %d, expected = %d\n", testG.supplyCount[silver], G.supplyCount[silver]);
	printf("gold count = %d, expected = %d\n", testG.supplyCount[gold], G.supplyCount[gold]);
	printf("estate count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
	printf("duchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
	printf("adventurer count = %d, expected = %d\n", testG.supplyCount[adventurer], G.supplyCount[adventurer]);
	printf("remodel count = %d, expected = %d\n", testG.supplyCount[remodel], G.supplyCount[remodel]);
	printf("village count = %d, expected = %d\n", testG.supplyCount[village], G.supplyCount[village]);
	printf("minion count = %d, expected = %d\n", testG.supplyCount[minion], G.supplyCount[minion]);
	printf("mine count = %d, expected = %d\n", testG.supplyCount[mine], G.supplyCount[mine]);
	printf("cutpurse count = %d, expected = %d\n", testG.supplyCount[cutpurse], G.supplyCount[cutpurse]);
	printf("sea_hag count = %d, expected = %d\n", testG.supplyCount[sea_hag], G.supplyCount[sea_hag]);
	printf("tribute count = %d, expected = %d\n", testG.supplyCount[tribute], G.supplyCount[tribute]);
	printf("smithy count = %d, expected = %d\n", testG.supplyCount[smithy], G.supplyCount[smithy]);
	printf("council_room count = %d, expected = %d\n", testG.supplyCount[council_room], G.supplyCount[council_room]);

	assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
	assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);
	assert(testG.supplyCount[copper] == G.supplyCount[copper]);
	assert(testG.supplyCount[silver] == G.supplyCount[silver]);
	assert(testG.supplyCount[gold] == G.supplyCount[gold]);
	assert(testG.supplyCount[estate] == G.supplyCount[estate]);
	assert(testG.supplyCount[duchy] == G.supplyCount[duchy]);
	assert(testG.supplyCount[adventurer] == G.supplyCount[adventurer]);
	assert(testG.supplyCount[remodel] == G.supplyCount[remodel]);
	assert(testG.supplyCount[village] == G.supplyCount[village]);
	assert(testG.supplyCount[minion] == G.supplyCount[minion]);
	assert(testG.supplyCount[mine] == G.supplyCount[mine]);
	assert(testG.supplyCount[cutpurse] == G.supplyCount[cutpurse]);
	assert(testG.supplyCount[sea_hag] == G.supplyCount[sea_hag]);
	assert(testG.supplyCount[tribute] == G.supplyCount[tribute]);
	assert(testG.supplyCount[smithy] == (G.supplyCount[smithy]));
	assert(testG.supplyCount[council_room] == G.supplyCount[council_room]);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}