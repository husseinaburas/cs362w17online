/****************************************************************************** 
* cardtest 4: mine() tests dominion.c::cardEffect::mine.
* cardtest4.c is a unit testing program for the above function contained within
* dominion.c, compiled via MakeFile.
* Chris Kearns, kearnsc@oregonstate.edu, CS325-400-W17, Assign_3, 5 Feb 2017
* You may trash a Treasure from your hand.
* Gain a Treasure to your hand costing up to 3 more than it.
******************************************************************************/
#include "rngs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"

#define SHOW_PASSFAIL 1
static int failCount = 0;

// Prototypes.
void softAssert(_Bool result, int testNum);

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Input error: usage: rt1 {int1}\n"
			"  if int1 < 0 then the game state seed is obtained from the system clock.\n"
			"  if int1 == 0 then the game state is to be supplied interactively.\n"
			"  if int1 > 0 then int1 will be used as the seed value\n"
			"  and user must vary int1 input to see different random int results!\n"
		);
		exit(1);
	}

	struct gameState G1;	// Our gameState to be tested.
	struct gameState G2;	// Our gameState used to reset G1.

	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	// Bypasses CLI input with randomseed = 88 (totally random pick by tester...)
	initializeGame(MAX_PLAYERS, k, (long)atoi(argv[1]), &G1);

	// Set gameState G2 to the initial settings following initialization of G1.
	memcpy(&G2, &G1, sizeof(struct gameState));

	int i;
	for (i = 0; i < MAX_PLAYERS; i++) {
		G1.handCount[i] = floor(Random() * MAX_HAND);
		G1.deckCount[i] = floor(Random() * MAX_DECK);
		G1.discardCount[i] = floor(Random() * MAX_DECK);
		G1.playedCardCount = floor(Random() * MAX_DECK);

		int T1pre = G1.hand[i][0];
		int T2pre = G1.handCount[i];
		int T3pre = G1.hand[i][0];

		//We only want player 0 to run cardEffect(council_room) and test all other players gameState
		if (i == 0)
			cardEffect(mine, copper, gold, 0, &G1, 0, 0);

		int T1post = G1.hand[i][0];
		int T2post = G1.handCount[i];
		int T3post = G1.hand[i][0];

		// Test 1: Is card at G1.hand[0][0] now a Gold(6)? 
		softAssert((T1pre != 6 && T1post == 6), 1);

		// Test 2: Does player[0] have the same amount of cards? Gain one, discard one.
		softAssert((T2pre == T2post), 2);

		// Test 3: Is card at G1.hand[1][0] unchanged since this is player[1]? 
		softAssert((T3pre == T3post), 3);

		// We already know discardCard() has some issues, see unittest3.c for those details.

	}

	printf("Failed test count = %d\n", failCount);

	if (failCount > 0)
		printf("Consider running this test with SHOW_PASSFAIL set to 1\n");

	return 0;
}

/* "Roll your own" less intrusive assert function. NOTE: When the expectation
is result should be false, call softAssert with "!result" as argument. */
void softAssert(_Bool result, int testNum) {
	if (SHOW_PASSFAIL == 1) {
		printf("Card Adventurer - ");
		if (result)
			printf("TEST %d SUCCESFULLY COMPLETED\n", testNum);
		else
			printf("TEST %d FAILED - Potential bug!\n", testNum);
	}
	if (result == 0)
		failCount++;
}

/*
case mine:
	j = state->hand[currentPlayer][choice1];  // Store card we will trash.
	if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold) {
		return -1;
	}
	if (choice2 > treasure_map || choice2 < curse) {
		return -1;
	}
	if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) ) {
		return -1;
	}
	gainCard(choice2, state, 2, currentPlayer);

	// Discard card from hand.
	discardCard(handPos, currentPlayer, state, 0);
	// Discard trashed card.
	for (i = 0; i < state->handCount[currentPlayer]; i++) {
		if (state->hand[currentPlayer][i] == j) {
			discardCard(i, currentPlayer, state, 0);
			break;
		}
	}
	return 0;
*/