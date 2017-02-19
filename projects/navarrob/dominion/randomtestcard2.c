//
// Created by Rob Navarro on 2/18/17.
//

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>


int main(int argc, char **argv) {
	struct gameState G;
	int numPlayers;
	int seed;
	int i, p;

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
				 sea_hag, tribute, smithy};

	//determine if seed provided, if not use 10 as default
	if (argc != 2) {
		printf("No seed provided, using default of 10\n");
		seed = 10;
	}

	else
		seed = (int) argv[1];

	SelectStream(2);
	PutSeed(seed);

	for (i = 0; i < 2000; i++) {
		printf("\n*** Random Card Test %d: Village ***\n", i + 1);
		int initialDeckCount = 0;
		int initialHandCount = 0;
		int initialActions = 0;

		//Set a random amount of players for game
		numPlayers = (int) floor(Random() * 3 + 2);

		//initialize game with random players and seed
		initializeGame(numPlayers, k, seed, &G);

		//randomly choose the current player and set actions to random number between 1 and num players
		p = G.whoseTurn = (int) floor(Random() * numPlayers);
		initialActions = G.numActions = (int) floor(Random() * (numPlayers - 1) + 1);

		//randomly set hand and deck count
		initialHandCount = G.handCount[p] = (int) floor(Random() * MAX_HAND + 1);
		initialDeckCount = G.deckCount[p] = (int) floor(Random() * (MAX_DECK - 3) + 1);

		printf("Test initialized with %d players, %d hand count, %d deck count, and %d actions.\n", numPlayers, initialHandCount, initialDeckCount, initialActions);
		printf("Testing village with player %d\n", p + 1);

		//Set hand so that adventurer card is next card played
		G.hand[p][0] = village;

		playCard(0, 0, 0, 0, &G);

		printf("Before card play: handcount - %d, deckcount - %d\n", initialHandCount, initialDeckCount);
		printf("After card play: handcount - %d, deckcount - %d\n", G.handCount[p], G.deckCount[p]);

		printf("Confirm that hand now has no additonal cards, village should be discarded.\n");
		customAssert(G.handCount[p] ==  initialHandCount);
		printf("Confirm that deck now has one less cards.\n");
		customAssert(G.deckCount[p] == initialDeckCount - 1);
		printf("Confirm that deck + discard is equal to initial deck count\n");
		customAssert(G.playedCardCount  == 1);
		printf("Confirm that number of actions has increased by 1, playing village should have taken 1 action off, which would only increase action total by 1 instaed of 2. \n");
		customAssert(G.numActions == initialActions + 1);

		seed++;
	}

	return 0;
}
