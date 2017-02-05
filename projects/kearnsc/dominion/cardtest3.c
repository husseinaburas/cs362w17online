/******************************************************************************
* cardtest 1: council_room tests dominion.c::cardEffect::council_room.
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

	// Bypasses CLI input with randomseed = 77 (totally random pick by tester...)
	initializeGame(2, k, 77, &G1);

	// Set gameState G2 to the initial settings following initialization of G1.
	memcpy(&G2, &G1, sizeof(struct gameState));

	int T1pre = G1.handCount[0];
	int T2pre = G1.deckCount[0];
	int T3pre = G1.discardCount[0];
	int T4pre = G1.playedCardCount;
	int T5pre = G1.hand[0][8];
	int T6pre = G1.numBuys;

	cardEffect(council_room, 0, 0, 0, &G1, 0, 0);

	int T1post = G1.handCount[0];
	int T2post = G1.deckCount[0];
	int T3post = G1.discardCount[0];
	int T4post = G1.playedCardCount;
	int T5post = G1.hand[0][8];
	int T6post = G1.numBuys;

	// Test 0 - Make sure its player 0's turn. Not really a test, but impt. for these tests to be valid.
	softAssert((whoseTurn(&G1) == 0), 0);

	// Test 1: Does handCount for player[0] increase by 3 (4 drawn - 1 played).
	softAssert((T1pre + 3 == T1post), 1);

	// Test 2: Does deckCount for player[0] decrease by 4 (4 drawn).
	softAssert((T2pre - 4 == T2post), 2);

	// Test 3: Does discardCount[0] increment when card is discarded. Fails! **** POTENTIAL BUG ****
	softAssert((T3pre < T3post), 3);

	// Test 4: Does playedCardCount increment when council_room card is played.
	softAssert((T4pre + 1 == T4post), 4);

	// Test 5: Does hand[0][8] change to -1 when council_room card is played.
	softAssert((-1 == T5post), 5);

	// Test 6: Did numbuys get incremented by 1 when council_room card was played.
	softAssert((T6pre + 1 == T6post), 6);

	// Reset gameState G1.
	memcpy(&G1, &G2, sizeof(struct gameState));

	// Redo but with check player[1] after running council_room card.  No changes should be seen with player[1].
	T1pre = G1.handCount[1];
	T2pre = G1.deckCount[1];
	T3pre = G1.discardCount[1];
	T4pre = G1.playedCardCount;
	T5pre = G1.hand[1][8];
	T6pre = G1.numBuys;

	cardEffect(council_room, 0, 0, 0, &G1, 0, 0);

	T1post = G1.handCount[1];
	T2post = G1.deckCount[1];
	T3post = G1.discardCount[1];
	T4post = G1.playedCardCount;
	T5post = G1.hand[1][8];
	T6post = G1.numBuys;

	// Test 7 - Make sure its player 0's turn. Not really a test, but impt. for these tests to be valid.
	softAssert((whoseTurn(&G1) == 0), 7);

	// Test 8: Does handCount for player[1] increase by 1 (per council_room card action!).
	softAssert((T1pre + 1 == T1post), 8);

	// Test 9: Does deckCount for player[1] decrease by 1 (1 drawn).
	softAssert((T2pre - 1 == T2post), 9);

	// Test 10: Does discardCount[1] not increment when card is discarded.
	softAssert((T3pre == T3post), 10);

	// Test 11: Does playedCardCount increment when council_room card is played.
	softAssert((T4pre + 1 == T4post), 11);

	// Test 12: Does hand[1][8] not change by -1 when council_room card is played.
	softAssert((T5pre == T5post), 12);

	// Test 13: Did numbuys get incremented by 1 when council_room card was played.
	softAssert((T6pre + 1 == T6post), 13);

	return 0;
}

/* "Roll your own" less intrusive assert function. NOTE: When the expectation
is result should be false, call softAssert with "!result" as argument. */
void softAssert(_Bool result, int testNum) {
	printf("Card Council_room - ");
	if (result)
		printf("TEST %d SUCCESFULLY COMPLETED\n", testNum);
	else
		printf("TEST %d FAILED - Potential bug!\n", testNum);
}

/* For reference only.
case council_room:
	// +4 Cards.
	for (i = 0; i < 4; i++) {
		drawCard(currentPlayer, state);
	}
	// +1 Buy.
	state->numBuys++;
	// Each other player draws a card.
	for (i = 0; i < state->numPlayers; i++) {
		if (i != currentPlayer) {
			drawCard(i, state);
		}
	}
	// Put played card in played card pile.
	discardCard(handPos, currentPlayer, state, 0);
	return 0;
*/
