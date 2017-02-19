//
// Created by Rob Navarro on 2/18/17.
//

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
		printf("\n*** Random Card Test %d: Smithy ***\n", i + 1);
		int initialDeckCount = 0;
		int initialHandCount = 0;
		int initialActions = 0;
		int r;

		//Set a random amount of players for game
		numPlayers = (int) floor(Random() * 3 + 2);

		//initialize game with random players and seed
		initializeGame(numPlayers, k, seed, &G);

		//randomly choose the current player and set actions to random number between 1 and num players
		p = G.whoseTurn = (int) floor(Random() * numPlayers);
		initialActions = G.numActions = (int) floor(Random() * (numPlayers - 1) + 1);

		//randomly set hand and deck count
		initialHandCount = G.handCount[p] = (int) floor(Random() * (MAX_HAND - 3) + 1);
		initialDeckCount = G.deckCount[p] = (int) floor(Random() * MAX_DECK);

		r = (int) floor(Random() * 10);
		if (initialDeckCount < 3) {
			G.discardCount[p] = 4;
			G.discard[p][0] = smithy;
			G.discard[p][1] = adventurer;
			G.discard[p][2] = gold;
			G.discard[p][3] = village;
			if (r == 7) {
				G.discardCount[p]++;
				G.discard[p][4] = silver;
			}
		}

		printf("Test initialized with %d players, %d hand count, %d deck count.\n", numPlayers, initialHandCount, initialDeckCount);
		printf("Testing smithy with player %d\n", p + 1);

		//Set hand so that adventurer card is next card played
		G.hand[p][0] = smithy;

		playCard(0, 0, 0, 0, &G);

		printf("Before card play: handcount - %d, deckcount - %d\n", initialHandCount, initialDeckCount);
		printf("After card play: handcount - %d, deckcount - %d\n", G.handCount[p], G.deckCount[p]);
		printf("Confirm that hand now has two additional cards, smithy should be discarded.\n");
		customAssert(G.handCount[p] ==  initialHandCount + 2);
		printf("Confirm that deck now has three less cards.\n");
		customAssert(G.deckCount[p] == initialDeckCount - 3);
		printf("Confirm that deck + discard is equal to initial deck count\n");
		customAssert(G.playedCardCount  == 1);
		printf("Confirm that number of actions has decreased by 1\n");
		customAssert(G.numActions == initialActions - 1);

		seed++;
	}

	return 0;
}
