#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]) {

	int i;
	int numPlayers;
	int randSeed;
	const int k[10] = { adventurer, gardens, embargo, village, minion, mine,
			cutpurse, sea_hag, tribute, smithy };

	//determine if seed provided, if not use 10 as default
	if (argc != 2) {
		randSeed = 10;
	} else {
		randSeed = (atoi(argv[1]));
	}

	SelectStream(2);
	PutSeed(randSeed);

	const int testNum = 1000;
	//Loop for the number of tests
	for (i = 0; i < testNum; i++) {
		printf(
				"==============================>Starting %d test out of %d\n for the Smithy Card",
				(i + 1), testNum);

		int numPlayers = (int) floor(Random() * 3 + 2); // initialize random player number
		int currentPlayer = (int) floor(Random() * numPlayers); // initialize random current turn
		int startUpSeed = (int) floor(Random() * testNum + 1); // initialize random startup seed

		int initActionNum, initHandNum, initDeckNum;

		struct gameState G;
		initializeGame(numPlayers, k, startUpSeed, &G);

		G.whoseTurn = currentPlayer;
		G.numActions = (int) floor(Random() * (numPlayers - 1) + 1);
		G.handCount[currentPlayer] = (int) floor(Random() * (MAX_HAND - 3) + 1);
		G.deckCount[currentPlayer] = (int) floor(Random() * MAX_DECK);

		//save the initial state
		initActionNum = G.numActions;
		initHandNum = G.handCount[currentPlayer];
		initDeckNum = G.deckCount[currentPlayer];

		printf("Testing Smithy with player number = %d, current player = %d, action number = %d, hand count = %d, deck count = %d \n",
				numPlayers, currentPlayer, initActionNum, initHandNum, initDeckNum);


		int r = (int) floor(Random() * 10);
		if (initDeckNum < 3) {
			G.discardCount[currentPlayer] = 4;
			G.discard[currentPlayer][0] = smithy;
			G.discard[currentPlayer][1] = adventurer;
			G.discard[currentPlayer][2] = gold;
			G.discard[currentPlayer][3] = village;
			if (r == 7) {
				G.discardCount[currentPlayer]++;
				G.discard[currentPlayer][4] = silver;
			}
		}

		G.hand[currentPlayer][0] = smithy;
		playCard(0, 0, 0, 0, &G);

		assertMsg("Checking no additional cards in hands", G.handCount[currentPlayer], initHandNum);
		assertMsg("Checking deck loses one card", G.deckCount[currentPlayer], initDeckNum-1);
		assertMsg("Checking total card number is correct", G.deckCount[currentPlayer] + G.discardCount[currentPlayer], initDeckNum);
		assertMsg("Checking action number changes", G.numActions, initActionNum + 1);
	}

	return 0;
}
