/******************************************************************************
* Unittest 3: function discardCard() tests dominion.c::discardCard().
* unittest3.c is a unit testing program for the above function contained within
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

	// Bypasses CLI input with randomseed = 33 (totally random pick by tester...)
	initializeGame(2, k, 33, &G1);

	// Set gameState G2 to the initial settings following initialization of G1.
	memcpy(&G2, &G1, sizeof(struct gameState));

	// TEST 1: Player 0 discards village card (enum CARD 14), trashflag is 0.
	int result = discardCard(14, 0, &G1, 0);
	softAssert((result == 0 && G1.playedCards[G1.playedCardCount] == 0 && G1.playedCardCount == 1), 1);

	// Reset gameState G1.
	memcpy(&G1, &G2, sizeof(struct gameState));

	// TEST 2: Player 0 discards village card (enum CARD 14), trashflag is 1.  Fails - G1.playedCards[G1.playedCardCount] unitialized.
	result = discardCard(14, 0, &G1, 1);
	softAssert((result == 0 && G1.playedCards[G1.playedCardCount] == 0 && G1.playedCardCount == 0), 2);

	// Reset gameState G1.
	memcpy(&G1, &G2, sizeof(struct gameState));

	int test7 = G1.handCount[0];		// Save that for now...
	int test8 = G1.handCount[1];		// Save that for now...
	int test9 = G1.playedCardCount;	// Save that for now...

	// TEST 3: Player 0 discards the last card in hand (temp-1), trashflag is 0.
	// First, we find the last card in player 0's hand...
	int i, temp = 0;
	for (i = 26; i >= 0; i--) {
		if (G1.hand[0][i] != 0) {
			temp++;
		}
	}
	// ...and discard that card.
	result = discardCard(temp - 1, 0, &G1, 0);
	softAssert((result == 0 && G1.hand[0][temp-1] == -1), 3);

	// Do not reset gameState G1 !

	// TEST 4: A card should have been removed from player[0]'s hand.
	softAssert((temp-1 == G1.handCount[0]), 4);

	// Test 5: Was discarded card replaced with last card in hand.
	softAssert((G1.hand[0][temp-2] == G1.hand[0][(G1.handCount[0] - 1)]), 5);

	// Test 6: Was last card set to -1.
	softAssert((G1.hand[0][temp - 1] == -1), 6);

	// Test 7: Did number of cards in player[0]'s hand decrement.
	softAssert((G1.handCount[0] == test7 - 1), 7);

	// Test 8: Did number of cards in player[1]'s hand decrement.
	softAssert((G1.handCount[1] == test8), 8);

	// Test 9: Does playedCardCount increment?
	softAssert((G1.playedCardCount +1 == test9 ), 9);

	return 0;
}


/* "Roll your own" less intrusive assert function. NOTE: When the expectation
is result should be false, call softAssert with "!result" as argument. */
void softAssert(_Bool result, int testNum) {
	printf("Function discardCard() - ");
	if (result)
		printf("TEST %d SUCCESFULLY COMPLETED\n", testNum);
	else
		printf("TEST %d FAILED - Potential bug!\n", testNum);
}


/* For reference only.
int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag) {
	// If card is not trashed, added to Played pile.
	if (trashFlag < 1) {
		// Add card to played pile.
		state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos];
		state->playedCardCount++;
	}
	// Set played card to -1.
	state->hand[currentPlayer][handPos] = -1;

	// Remove card from player's hand.
	if (handPos == (state->handCount[currentPlayer] - 1)) { // Last card in hand array is played.
												 // Reduce number of cards in hand.
		state->handCount[currentPlayer]--;
	}
	else if (state->handCount[currentPlayer] == 1) { // Only 1 card in hand, reduce number of cards in hand.
		state->handCount[currentPlayer]--;
	}
	else {
		// Replace discarded card with last card in hand.
		state->hand[currentPlayer][handPos] = state->hand[currentPlayer][(state->handCount[currentPlayer] - 1)];
		// Set last card to -1.
		state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
		// Reduce number of cards in hand.
		state->handCount[currentPlayer]--;
	}
	return 0;
}
*/
