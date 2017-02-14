/****************************************************************************** 
* randomtestcard1: council_room tests dominion.c::cardEffect::council_room.
* randomtestcard.c is a unit testing program for the above function contained within
* dominion.c, compiled via MakeFile.
* Chris Kearns, kearnsc@oregonstate.edu, CS325-400-W17, Assign_4, 19 Feb 2017
******************************************************************************/
#include "rngs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"

#define SHOW_PASSFAIL 0
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

	int k[11] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };

	// Initialize game with CLI input argv[1] as randomseed (paremeter 3).
	initializeGame(MAX_PLAYERS, k, (long)atoi(argv[1]), &G1);

	// Set gameState G2 to the initial settings following initialization of G1.
	memcpy(&G2, &G1, sizeof(struct gameState));

	int i, T1pre, T1post, T2pre, T2post, T3pre, T3post, T4pre, T4post, T5pre, T5post, T6pre, T6post;

	for (i = 0; i < MAX_PLAYERS; i++) {
		memcpy(&G1, &G2, sizeof(struct gameState));// Reset gameState each pass.
		G1.handCount[i] = floor(Random() * MAX_HAND);
		G1.deckCount[i] = floor(Random() * MAX_DECK);
		G1.discardCount[i] = floor(Random() * MAX_DECK);
		G1.playedCardCount = floor(Random() * MAX_DECK);
		G1.hand[i][8] = floor(Random() * MAX_DECK);

		int T1pre = G1.handCount[i];
		int T2pre = G1.deckCount[i];
		int T3pre = G1.discardCount[i];
		int T4pre = G1.playedCardCount;
		int T5pre = G1.hand[i][8];
		int T6pre = G1.numBuys;

		cardEffect(council_room, 0, 0, 0, &G1, 0, 0);

		int T1post = G1.handCount[i];
		int T2post = G1.deckCount[i];
		int T3post = G1.discardCount[i];
		int T4post = G1.playedCardCount;
		int T5post = G1.hand[i][8];
		int T6post = G1.numBuys;

		// Test 0 - Make sure it's player i's turn. Not really a test, but impt. for these tests to be valid.
		softAssert((whoseTurn(&G1) == i), 0);

		// Test 1: Does handCount for player[1-4] increase by 3 (4 drawn - 1 played).
		softAssert((T1pre + 3 == T1post), 1);

		// Test 2: Does deckCount for player[1-4] decrease by 4 (4 drawn).
		softAssert((T2pre - 4 == T2post), 2);

		// Test 3: Does discardCount[1-4] increment when card is discarded. Fails! **** POTENTIAL BUG ****
		softAssert((T3pre < T3post), 3);

		// Test 4: Does playedCardCount increment when council_room card is played.
		softAssert((T4pre + 1 == T4post), 4);

		// Test 5: Does hand[1-4][8] change to -1 when council_room card is played.
		softAssert((T5pre != -1 && T5post == -1), 5);

		// Test 6: Did numbuys get incremented by 1 when council_room card was played.
		softAssert((T6pre + 1 == T6post), 6);
	}

	// Reset gameState G1.
	memcpy(&G1, &G2, sizeof(struct gameState));

	for (i = 0; i < MAX_PLAYERS; i++) {
		G1.handCount[i] = floor(Random() * MAX_HAND);
		G1.deckCount[i] = floor(Random() * MAX_DECK);
		G1.discardCount[i] = floor(Random() * MAX_DECK);
		G1.playedCardCount = floor(Random() * MAX_DECK);

		// Redo but with check player[1] after running council_room card by player 0. No changes should be seen with player[1,2, and 3].
		T1pre = G1.handCount[i];
		T2pre = G1.deckCount[i];
		T3pre = G1.discardCount[i];
		T4pre = G1.playedCardCount;
		T5pre = G1.hand[i][8];
		T6pre = G1.numBuys;

		//We only want player 0 to run cardEffect(council_room) and test all other players gameState
		if(i == 0)
			cardEffect(council_room, 0, 0, 0, &G1, 0, 0);

		T1post = G1.handCount[i];
		T2post = G1.deckCount[i];
		T3post = G1.discardCount[i];
		T4post = G1.playedCardCount;
		T5post = G1.hand[i][8];
		T6post = G1.numBuys;

		// Test 7 - Make sure its player i's turn. Not really a test, but impt. for these tests to be valid.
		softAssert((whoseTurn(&G1) == 0), 7);

		// Test 8: Does handCount for player[1,23] increase by 1 (per council_room card action!).
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
