/******************************************************************************
* Unittest 2: function getWinners() tests dominion.c::getWinners().
* unittest2.c is a unit testing program for the above function contained within
* dominion.c, compiled via MakeFile.
* Chris Kearns, kearnsc@oregonstate.edu, CS325-400-W17, Assign_3, 5 Feb 2017
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "dominion.h"

// Prototypes.
void softAssert(_Bool result, int testNum);
int testGetWinners(int players[MAX_PLAYERS], struct gameState *state, int flag);

int main() {
	struct gameState G1;	// Our gameState to be tested.
	struct gameState G2;	// Our gameState used to reset G1.

	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	// Bypasses CLI input with randomseed = 22 (randomly pick by tester...)
	initializeGame(2, k, 22, &G1);

	// Set gameState G2 to the initial settings following initialization of G1.
	memcpy(&G2, &G1, sizeof(struct gameState));

	int players[MAX_PLAYERS];

	// Test 1 - does getWinners run and return 0?  Should be 0.
	int result = testGetWinners(players, &G1, 0);
	softAssert(!result, 1);

	// Test 2 - we initialized the game with 2 players, so there should be 2 and only 2.
	softAssert(!(G1.numPlayers > 2) && !(G1.numPlayers < 2), 2);

	// Test 3 - Manually set the number of players to 1 and rerun Test 2.
	G1.numPlayers = 1;
	result = testGetWinners(players, &G1, 1);
	softAssert(((G1.numPlayers > 0) && (G1.numPlayers < 2)), 3);

	// Reset gameState G1 and run with flag == 1.
	memcpy(&G1, &G2, sizeof(struct gameState));
	result = testGetWinners(players, &G1, 1);

	/* Should result in players[1] == 1 and players[0, 2, & 3] == 0.
	   Test 4. Test for correct player winning and if players array is being
	   reset to 0/1 rather than the actual scores as we manually inject scores below. */
	softAssert((players[0] == 0 && players[1] == 1 && players[2] == 0 && players[3] == 0), 4);

	return 0;
}

/* "Roll your own" less intrusive assert function. NOTE: When the expectation
is result should be false, call softAssert with "!result" as argument. */
void softAssert(_Bool result, int testNum) {
	printf("Function getWinners() - ");
	if (result)
		printf("TEST %d SUCCESFULLY COMPLETED\n", testNum);
	else
		printf("TEST %d FAILED - Potential bug!\n", testNum);
}


int testGetWinners(int players[MAX_PLAYERS], struct gameState *state, int flag) {

	int i;
	int j;
	int highScore;
	int currentPlayer;

	// Get score for each player.
	for (i = 0; i < MAX_PLAYERS; i++) {
		// Set unused player scores to -9999
		if (i >= state->numPlayers) {
			players[i] = -9999;
		}
		else {
			if (flag == 1) {
				players[i] = i + 10;	// Forces a winner since i is incrementing.
			}
			else {
				players[i] = scoreFor(i, state);
			}

		}
	}

	// Find highest score.
	j = 0;
	for (i = 0; i < MAX_PLAYERS; i++) {
		if (players[i] > players[j]) {
			j = i;
		}
	}
	highScore = players[j];

	// Add 1 to players who had less turns.
	currentPlayer = whoseTurn(state);
	for (i = 0; i < MAX_PLAYERS; i++) {
		if (players[i] == highScore && i > currentPlayer) {
			players[i]++;
		}
	}

	// Find new highest score.
	j = 0;
	for (i = 0; i < MAX_PLAYERS; i++) {
		if (players[i] > players[j]) {
			j = i;
		}
	}
	highScore = players[j];

	// Set winners in array to 1 and rest to 0.
	for (i = 0; i < MAX_PLAYERS; i++) {
		if (players[i] == highScore) {
			players[i] = 1;
		}
		else {
			players[i] = 0;
		}
	}

	return 0;
}
