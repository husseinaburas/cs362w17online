/******************************************************************************
* cardtest 1: mine() tests dominion.c::cardEffect::mine.
* cardtest1.c is a unit testing program for the above function contained within
* dominion.c, compiled via MakeFile.
* Chris Kearns, kearnsc@oregonstate.edu, CS325-400-W17, Assign_3, 5 Feb 2017
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "dominion.h"

// Prototypes.
void softAssert(_Bool result, int testNum);

int main() {
	struct gameState G1;	// Our gameState to be tested.
	struct gameState G2;	// Our gameState used to reset G1.

	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	// Bypasses CLI input with randomseed = 88 (totally random pick by tester...)
	initializeGame(2, k, 88, &G1);

	// Set gameState G2 to the initial settings following initialization of G1.
	memcpy(&G2, &G1, sizeof(struct gameState));

	// You may trash a Treasure from your hand.
	// Gain a Treasure to your hand costing up to 3 more than it.

/*	// Inspect hand[0] before call to cardEffect().
	int i;
	for (i = 0; i < G1.handCount[0]; i++) {
		printf("Card %d = %d\n", i, G1.hand[0][i]);
	}
*/

	int T1pre = G1.hand[0][0];
	int T2pre = G1.handCount[0];
	int T3pre = G1.hand[1][0];
	int T4pre = G1.handCount[1];

	cardEffect(mine, copper, gold, 0, &G1, 0, 0);

	int T1post = G1.hand[0][0];
	int T2post = G1.handCount[0];
	int T3post = G1.hand[1][0];
	int T4post = G1.handCount[1];

/*	// Inspect hand[0] after call to cardEffect().
	for (i = 0; i < G1.handCount[0]; i++) {
		printf("Card %d = %d\n", i, G1.hand[0][i]);
	}
*/

	// Test 1: Is card at G1.hand[0][0] now a Gold(6)? 
	softAssert((T1pre != 6 && T1post == 6), 1);

	// Test 2: Does player[0] have the same amount of cards? Gain one, discard one. Fail! **** Potential Bug ****
	softAssert((T2pre == T2post), 2);

	// Test 3: Is card at G1.hand[1][0] unchanged since this is player[1]? 
	softAssert((T3pre == T3post), 3);

	// Test 4: Does player[1] have the same amount of cards?
	softAssert((T4pre == T4post), 4);

	// We alredy know discardCard() has some issues, see unittest3.c for those details.

	return 0;
}

/* "Roll your own" less intrusive assert function. NOTE: When the expectation
is result should be false, call softAssert with "!result" as argument. */
void softAssert(_Bool result, int testNum) {
	printf("Card Mine - ");
	if (result)
		printf("TEST %d SUCCESFULLY COMPLETED\n", testNum);
	else
		printf("TEST %d FAILED - Potential bug!\n", testNum);
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