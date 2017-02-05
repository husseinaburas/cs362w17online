/******************************************************************************
* Unittest 1: function isGameOver().
* unittest1.c is a unit testing program for the above function contained within 
* dominion.c, compiled via MakeFile.
* Chris Kearns, kearnsc@oregonstate.edu, CS325-400-W17, Assign_3, 5 Feb 2017
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "dominion.h"

// Prototypes.
void softAssert(_Bool result, int testNum);

int main() {
	int i;
	struct gameState G1;	// Our gameState to be tested.
	struct gameState G2;	// Our gameState used to reset G1.

	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	// Bypasses CLI input with randomseed = 11 (randomly picked by tester...)
	initializeGame(2, k, 11, &G1);

	// Set gameState G2 to the initial settings following initialization of G1.
	memcpy(&G2, &G1, sizeof(struct gameState));

	// Test 1 - is the province supplyCount > 0 AND 1 was returned.
	int result = isGameOver(&G1);
	softAssert((!result && G1.supplyCount[province] > 0), 1);

	// Test 2 - set province supply card count to 0 (game should end).
	G1.supplyCount[province] = 0;
	result = isGameOver(&G1);
	softAssert((result && G1.supplyCount[province] == 0), 2);

	// Reset gameState G1.
	memcpy(&G1, &G2, sizeof(struct gameState));

	/* Test 3 - reproduce the gameState of 3 supply piles at 0. Modulous 12 should
	   give us 3 supply card piles set to 0. Note 0 mod n = 0, so we get i=0. */
	for (i = 0; i < 25; i++) {
		if (i % 12 == 0) {
			G1.supplyCount[i] = 0;
		}
	}
	result = isGameOver(&G1);
	softAssert((result && G1.supplyCount[0] == 0 && G1.supplyCount[12] == 0 && G1.supplyCount[24] == 0 ), 3);

	// Test 4 for the edge case of only 2 supply piles at 0.
	// Reset gameState G1.
	memcpy(&G1, &G2, sizeof(struct gameState));

	/* Reproduce the gameState of 2 supply piles at 0. Modulous 14 should give
	us 2 supply card piles set to 0 and game should not be over. */
	for (i = 0; i < 25; i++) {
		if (i % 14 == 0) {
			G1.supplyCount[i] = 0;
		}
	}
	result = isGameOver(&G1);
	int test4 = 0;
	for (i = 0; i < 25; i++) {
		// We test gameState of all supply card piles for Test4.
		if (G1.supplyCount[i] == 0) {
			test4++;
		}
	}
	// Checked gameState above to increment test4!
	softAssert((!result && test4 < 3), 4);

	return 0;
}

/* "Roll your own" less intrusive assert function. NOTE: When the expectation
is result should be false, call softAssert with "!result" as argument. */
void softAssert(_Bool result, int testNum) {
	printf("Function isGameOver() - ");
	if (result)
		printf("TEST %d SUCCESFULLY COMPLETED\n", testNum);
	else
		printf("TEST %d FAILED - Potential bug!\n", testNum);
}


/* // Function isGameOver() here for reference only.
int isGameOver(struct gameState *state) {
	int i;
	int j;

	// If stack of Province cards is empty, the game ends.
	if (state->supplyCount[province] == 0) {
		return 1;
	}

	// If three supply piles are at 0, the game ends.
	j = 0;
	for (i = 0; i < 25; i++) {
		if (state->supplyCount[i] == 0) {
			j++;
		}
	}

	if (j >= 3) {
		return 1;
	}

	return 0;
}
*/