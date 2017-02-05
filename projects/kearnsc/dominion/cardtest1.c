/******************************************************************************
* cardtest 1: function runSmithy() tests dominion.c::smithy().
* cardtest1.c is a unit testing program for the above function contained within
* dominion.c, compiled via MakeFile.
* Chris Kearns, kearnsc@oregonstate.edu, CS325-400-W17, Assign_3, 5 Feb 2017
* 1. Current player should receive exactly 3 cards.
* 2. 3 cards should come from his own pile.
* 3. No state change should occur for other players.
* 4. No state change should occur to victory card and kingdom card piles.
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

	// Bypasses CLI input with randomseed = 55 (totally random pick by tester...)
	initializeGame(2, k, 55, &G1);

	// Set gameState G2 to the initial settings following initialization of G1.
	memcpy(&G2, &G1, sizeof(struct gameState));

	// Test 1-4 - Check cardCounts, player[0].
	int T1pre = G1.handCount[0];
	int T2pre = G1.deckCount[0];
	int T3pre = G1.discardCount[0];
	int T4pre = G1.playedCardCount;

	runSmithy(&G1, 0, 1);

	int T1post = G1.handCount[0];
	int T2post = G1.deckCount[0];
	int T3post = G1.discardCount[0];
	int T4post = G1.playedCardCount;

	softAssert((T1pre + 2 == T1post), 1);	//  3 cards drawn, -1 played = +2.
	softAssert((T2pre - 3 == T2post), 2);	//  3 cards drawn from deckCount.
	softAssert((T3pre == T3post), 3);		//  discardCount unaffected.
	softAssert((T4pre == T4post - 1), 4);	//  playedCardCount increments by 1.

	// Reset gameState G1.
	memcpy(&G1, &G2, sizeof(struct gameState));

	// Test 5-8 - Check cardCounts, player[1].
	T1pre = G1.handCount[1];
	T2pre = G1.deckCount[1];
	T3pre = G1.discardCount[1];
	T4pre = G1.playedCardCount;

	// runSmithy on player 0, test for player 1 state change!!
	runSmithy(&G1, 0, 1);

	T1post = G1.handCount[1];
	T2post = G1.deckCount[1];
	T3post = G1.discardCount[1];
	T4post = G1.playedCardCount;

	softAssert((T1pre  == T1post), 5);		//  Should be ==.
	softAssert((T2pre  == T2post), 6);		//  Should be ==.
	softAssert((T3pre == T3post), 7);		//  Should be ==.
	softAssert((T4pre == T4post - 1), 8);	//  playedCardCount should still increment by 1.

	// Reset gameState G1.
	memcpy(&G1, &G2, sizeof(struct gameState));

	// Tests 9 - 36 - no supplyCard piles change.
	int i, pre[27], post[27];
	for (i = 0; i < 27; i++) {
		pre[i] = G1.supplyCount[i];
	}

	// runSmithy on player[0].
	runSmithy(&G1, 0, 1);

	for (i = 0; i < 27; i++) {
		post[i] = G1.supplyCount[i];
	}

	// Test them all - should all pass.
	for (i = 0; i < 27; i++) {
		softAssert((pre[i] == post[i]), i+9);
	}

	// Reset gameState G1.
	memcpy(&G1, &G2, sizeof(struct gameState));

	// Tests 36 - 40.
	// Store player[0] hand data.
	int temp[MAX_HAND];
	for (i = 0; i < G1.handCount[0]; i++) {
		temp[i] = G1.hand[0][i];
	}

	// Run Smithy by player[1].
	runSmithy(&G1, 1, 1);

	// Test for no change to player[0] hand data.
	for (i = 0; i < G1.handCount[0]; i++) {
		softAssert((G1.hand[0][i] == temp[i]), i + 36);
	}

	return 0;
}

/* "Roll your own" less intrusive assert function. NOTE: When the expectation
is result should be false, call softAssert with "!result" as argument. */
void softAssert(_Bool result, int testNum) {
	printf("Card Smithy - ");
	if (result)
		printf("TEST %d SUCCESFULLY COMPLETED\n", testNum);
	else
		printf("TEST %d FAILED - Potential bug!\n", testNum);
}


/* For reference only.
void runSmithy(struct gameState* state, int currentPlayer, int handPos) {
	int i;
	// +3 Cards.
	for (i = 3; i > 0; i--) {
		drawCard(currentPlayer, state);
	}
	// Discard card from hand.
	discardCard(handPos--, currentPlayer, state, 1);
}
*/