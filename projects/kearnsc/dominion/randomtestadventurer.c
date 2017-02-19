/****************************************************************************** 
* randomtestadventurer: tests dominion.c::cardEffect::adventurer and is a 
* random testing program for the above function contained within
* dominion.c, compiled via MakeFile.
* Chris Kearns, kearnsc@oregonstate.edu, CS325-400-W17, Assign_4, 19 Feb 2017
* Reveal cards from your deck until 2 Treasure cards are revealed.
* Add those cards to your hand.
* Discard the other revealed cards.
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
		printf("Input error: usage: rta {int1}\n"
			"  if int1 < 0 then the game state seed is obtained from the system clock.\n"
			"  if int1 == 0 then the game state is to be supplied interactively.\n"
			"  if int1 > 0 then int1 will be used as the seed value\n"
			"  and user must vary int1 input to see different random int results!\n"
		);
		exit(1);
	}

	int temphand[MAX_HAND];
	struct gameState G1;	// Our gameState to be tested.
	struct gameState G2;	// Our gameState used to reset G1.

	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	// Initialize game with CLI input argv[1] as randomseed (paremeter 3).
	initializeGame(MAX_PLAYERS, k, (long)atoi(argv[1]), &G1);

	// Set gameState G2 to the initial settings following initialization of G1.
	memcpy(&G2, &G1, sizeof(struct gameState));

	int i, T1pre, T1post, T2pre, T2post, T3pre, T3post, T4pre, T4post;

	for (i = 0; i < MAX_PLAYERS; i++) {
		memcpy(&G1, &G2, sizeof(struct gameState));// Reset game state.
		G1.handCount[i] = floor(Random() * MAX_HAND);
		G1.deckCount[i] = floor(Random() * MAX_DECK);
		G1.discardCount[i] = floor(Random() * MAX_DECK);
		G1.playedCardCount = floor(Random() * MAX_DECK);

		T1pre = G1.handCount[i];
		T2pre = G1.deckCount[i];
		T3pre = G1.discardCount[i];
		T4pre = G1.playedCardCount;

		runAdventurer(&G1, i, temphand); // Note second arg == i for player i.

		T1post = G1.handCount[i];
		T2post = G1.deckCount[i];
		T3post = G1.discardCount[i];
		T4post = G1.playedCardCount;

		// Test 1: Does handCount for player[i] increase by 2 (2 Treasure cards less discarded).
		softAssert((T1pre + 2 == T1post), 1);

		// Test 2: Does deckCount for player[i] decrease by 2 (-2 Treasure cards + discarded).
		softAssert((T2pre - 2 == T2post), 2);

		// Test 3: Does discardCount[i] increment when cards are discarded.
		softAssert((T3pre < T3post), 3);

		// Test 4: Does playedCardCount increment when Adventurer card is played.
		softAssert((T4pre + 1 == T4post), 4);
	}

	memcpy(&G1, &G2, sizeof(struct gameState));// Reset game state.

	// Only testing effect on other players of player[0] playing Adventurer card.
	for (i = 1; i < MAX_PLAYERS; i++) {
		// No gameState reset on each pass!
		G1.handCount[i] = floor(Random() * MAX_HAND);
		G1.deckCount[i] = floor(Random() * MAX_DECK);
		G1.discardCount[i] = floor(Random() * MAX_DECK);
		G1.playedCardCount = floor(Random() * MAX_DECK);

		// Run tests but with player[0] only running Adventurer card.  No changes should be seen with player[2, 3, and 4].
		T1pre = G1.handCount[i];
		T2pre = G1.deckCount[i];
		T3pre = G1.discardCount[i];
		T4pre = G1.playedCardCount;

		runAdventurer(&G1, 0, temphand); // Note second arg == 0 for player 0.

		T1post = G1.handCount[i];
		T2post = G1.deckCount[i];
		T3post = G1.discardCount[i];
		T4post = G1.playedCardCount;

		// Test 5: Does handCount for player[2, 3, and 4] not change by 2 (2 Treasure cards less discarded but for player[0])?
		softAssert((T1pre == T1post), 5);

		// Test 6: Does deckCount for player[2, 3, and 4] not change by 2 (-2 Treasure cards + discarded but for player[0])?
		softAssert((T2pre == T2post), 6);

		// Test 7: Does discardCount[2, 3, and 4] increment when cards are discarded by player[0]?
		softAssert((T3pre == T3post), 7);

		// Test 8: Does playedCardCount not increment when Adventurer card is played by player[0]?
		softAssert((T4pre == T4post), 8);
	}

	printf("Card Adventurer failed test count = %d\n", failCount);

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
	if(result == 0)
		failCount++;
}


/* // For reference only.
void runAdventurer(struct gameState *state, int currentPlayer, int *temphand) {
	int drawntreasure = 0;
	int z = 0;
	int cardDrawn;

	while (drawntreasure < 2) {
		if (state->deckCount[currentPlayer] < 1) { // If the deck is empty we need to shuffle discard and add to deck.
			shuffle(currentPlayer, state);
		}
		drawCard(currentPlayer, state);
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1]; // Top card of hand is most recently drawn card.
		cardDrawn++;
		if (cardDrawn == copper - 1 || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		else {
			if (cardDrawn > treasure_map) cardDrawn--;
			temphand[z] = cardDrawn;
			state->handCount[currentPlayer]--; // This should just remove the top card (the most recently drawn one).
			z++;
		}
	}
	while (z - 1 >= 0) {
		state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z - 1]; // Discard all cards in play that have been drawn.
		z = z - 1;
	}
}
*/