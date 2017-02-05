/******************************************************************************
* Unittest 4: function gainCard() tests dominion.c::gainCard().
* unittest4.c is a unit testing program for the above function contained within
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

	// Bypasses CLI input with randomseed = 44 (totally random pick by tester...)
	initializeGame(2, k, 44, &G1);

	// Set gameState G2 to the initial settings following initialization of G1.
	memcpy(&G2, &G1, sizeof(struct gameState));
	
	// TEST 1: Does a card that is not in the supplyCount array return -1.
	enum aCard { gold = 27 }; // A fraudulent card!
	int result = gainCard(gold, &G1, 0, 0);
	softAssert((result == -1 && G1.supplyCount[gold] == 0), 1);

	// TEST 2: Zero out a card in the supplyCount array and recheck.
	G1.supplyCount[k[0]] = 0;	// k[0] == Adventurer.
	result = gainCard(k[0], &G1, 0, 0);
	softAssert((result == -1 && G1.supplyCount[k[0]] == 0), 2);

	// TEST 3: Add 2 cards back to adventuer supplyCount and recheck. Should have decremented to 1.
	G1.supplyCount[k[0]] = 2;	// Adventurer.
	result = gainCard(k[0], &G1, 0, 0);
	softAssert((result == 0 && G1.supplyCount[k[0]] == 1), 3);

	// Reset gameState G1.
	memcpy(&G1, &G2, sizeof(struct gameState));

	// TEST 4 & 5: Gain an Adventurer, toFlag = 0.
	int temp = G1.discardCount[0];
	result = gainCard(7, &G1, 0, 0);
	softAssert((result == 0 && G1.discard[0][G1.discardCount[0]] == 7), 4);// **** POTENTIAL BUG ****
	softAssert((G1.discardCount[0] == temp + 1) , 5);					 // Incremented OK.

	// Reset gameState G1.
	memcpy(&G1, &G2, sizeof(struct gameState));

	// TEST 6 & 7: Gain an Adventurer, toFlag = 1.
	temp = G1.deckCount[0];
	result = gainCard(7, &G1, 1, 0);
	softAssert((result == 0 && G1.deck[0][G1.deckCount[0]] == 7), 6);// **** POTENTIAL BUG ****
	softAssert((G1.deckCount[0] == temp + 1), 7);				// Incremented OK.

	// Reset gameState G1.
	memcpy(&G1, &G2, sizeof(struct gameState));

	// TEST 8 & 9: Gain an Adventurer, toFlag = 2.
	temp = G1.handCount[0];
	result = gainCard(7, &G1, 2, 0);
	softAssert((result == 0 && G1.hand[0][G1.handCount[0]] == 7), 8);// **** POTENTIAL BUG ****
	softAssert((G1.handCount[0] == temp + 1), 9);				// Incremented OK.

	return 0;
}


/* "Roll your own" less intrusive assert function. NOTE: When the expectation
is result should be false, call softAssert with "!result" as argument. */
void softAssert(_Bool result, int testNum) {
	printf("Function gainCard() - ");
	if (result)
		printf("TEST %d SUCCESFULLY COMPLETED\n", testNum);
	else
		printf("TEST %d FAILED - Potential bug!\n", testNum);
}


/* For reference only. 
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player) {
	// Note: supplyPos is enum of choosen card.
	// Check if supply pile is empty (0) or card is not used in game (-1).
	if (supplyCount(supplyPos, state) < 1) {
		return -1;
	}

	// Added card for [whoseTurn] current player:
	// toFlag = 0 : add to discard
	// toFlag = 1 : add to deck
	// toFlag = 2 : add to hand

	if (toFlag == 1) {
//		printf("In testGainCard, supplyPos = %d\n", supplyPos);
		state->deck[player][state->deckCount[player]] = supplyPos;
		state->deckCount[player]++;
	}
	else if (toFlag == 2) {
//		printf("In testGainCard, supplyPos = %d\n", supplyPos);
		state->hand[player][state->handCount[player]] = supplyPos;
		state->handCount[player]++;
	}
	else {
//		printf("In testGainCard, supplyPos = %d\n", supplyPos);
		state->discard[player][state->discardCount[player]] = supplyPos;
		state->discardCount[player]++;
	}
	// Decrease number in supply pile.
	state->supplyCount[supplyPos]--;

	return 0;
}
*/
