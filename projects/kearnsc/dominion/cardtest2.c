/******************************************************************************
* cardtest 1: function runAdventure() tests dominion.c::cardEffect::adventurer.
* cardtest1.c is a unit testing program for the above function contained within
* dominion.c, compiled via MakeFile.
* Chris Kearns, kearnsc@oregonstate.edu, CS325-400-W17, Assign_3, 5 Feb 2017
* Reveal cards from your deck until 2 Treasure cards are revealed.
* Add those cards to your hand.
* Discard the other revealed cards.
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "dominion.h"

// Prototypes.
void softAssert(_Bool result, int testNum);

int main() {
	int temphand[MAX_HAND];
	struct gameState G1;	// Our gameState to be tested.
	struct gameState G2;	// Our gameState used to reset G1.

	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	// Bypasses CLI input with randomseed = 66 (totally random pick by tester...)
	initializeGame(2, k, 66, &G1);

	// Set gameState G2 to the initial settings following initialization of G1.
	memcpy(&G2, &G1, sizeof(struct gameState));

	int T1pre = G1.handCount[0];
	int T2pre = G1.deckCount[0];
	int T3pre = G1.discardCount[0];
	int T4pre = G1.playedCardCount;

	runAdventurer(&G1, 0, temphand); // Note second arg == 0 for player 0.

	int T1post = G1.handCount[0];
	int T2post = G1.deckCount[0];
	int T3post = G1.discardCount[0];
	int T4post = G1.playedCardCount;

	// Test 1: Does handCount for player[0] increase by 2 (2 Treasure cards less discarded).
	softAssert((T1pre + 2 == T1post), 1);

	// Test 2: Does deckCount for player[0] decrease by 2 (-2 Treasure cards + discarded).
	softAssert((T2pre - 2 == T2post), 2);

	// Test 3: Does discardCount[0] increment when cards are discarded. Fails! **** POTENTIAL BUG ****
	softAssert((T3pre < T3post), 3);

	// Test 4: Does playedCardCount increment when Adventurer card is played.  Fails! **** POTENTIAL BUG ****
	softAssert((T4pre + 1 == T4post), 4);

	// Redo but with player[1] running Adventurer card.  No changes should be seen with player[0].
	T1pre = G1.handCount[0];
	T2pre = G1.deckCount[0];
	T3pre = G1.discardCount[0];
	T4pre = G1.playedCardCount;

	runAdventurer(&G1, 1, temphand); // Note second arg == 1 for player 1.

	T1post = G1.handCount[0];
	T2post = G1.deckCount[0];
	T3post = G1.discardCount[0];
	T4post = G1.playedCardCount;

	// Test 5: Does handCount for player[0] not change by 2 (2 Treasure cards less discarded but for player[1])?
	softAssert((T1pre == T1post), 5);

	// Test 6: Does deckCount for player[0] not change by 2 (-2 Treasure cards + discarded but for player[1])?
	softAssert((T2pre == T2post), 6);

	// Test 7: Does discardCount[0] increment when cards are discarded by player[1]?
	softAssert((T3pre == T3post), 7);

	// Test 8: Does playedCardCount not increment when Adventurer card is played by player[1]?
	softAssert((T4pre == T4post), 8);

	return 0;
}

/* "Roll your own" less intrusive assert function. NOTE: When the expectation
is result should be false, call softAssert with "!result" as argument. */
void softAssert(_Bool result, int testNum) {
	printf("Card Adventurer - ");
	if (result)
		printf("TEST %d SUCCESFULLY COMPLETED\n", testNum);
	else
		printf("TEST %d FAILED - Potential bug!\n", testNum);
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