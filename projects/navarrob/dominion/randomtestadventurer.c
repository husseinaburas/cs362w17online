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
	int numOneTreasure = 0;
	int i, j, p;

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
		printf("\n*** Random Card Test %d: Adventurer ***\n", i + 1);
		int treasureDeckBefore = 0;
		int treasureHandBefore = 0;
		int treasureDeckAfter = 0;
		int treasureHandAfter = 0;
		int initialDeckCount = 0;
		int initialHandCount = 0;
		int initialActions = 0;
		int checkOneTreasure = 0;
		int r;

		//Set a random amount of players for game
		numPlayers = (int) floor(Random() * 3 + 2);

		//initialize game with random players and seed
		initializeGame(numPlayers, k, seed, &G);

		//randomly choose the current player and set actions to random number between 1 and num players
		p = G.whoseTurn = (int) floor(Random() * numPlayers);
		initialActions = G.numActions = (int) floor(Random() * (numPlayers - 1) + 1);

		//randomly set hand and deck count
		initialHandCount = G.handCount[p] = (int) floor(Random() * MAX_HAND + 1);
		initialDeckCount = G.deckCount[p] = (int) floor(Random() * MAX_DECK);

		//If we have an empty deck, we need to fill the discard pile
		r = (int) floor(Random() * 10);
		if (initialDeckCount == 0) {
			G.discardCount[p] = 3;
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
		G.hand[p][0] = adventurer;

		//Random case where only 1 treasure in deck
		checkOneTreasure = (int) floor(Random() * 50);
		if (checkOneTreasure == 25) {
			for (j = 0; j < G.deckCount[p]; j++) {
				int card = G.deck[p][j];
				if (card == copper || card == silver || card == gold) {
					G.deck[p][j] = smithy;
				}
			}
			G.deck[p][G.deckCount[p] - 1] = gold;
			numOneTreasure++;
		}

		//Check deck for treasure count before play
		for (j = 0; j < G.deckCount[p]; j++) {
			int card = G.deck[p][j];
			if (card == copper || card == silver || card == gold) {
				treasureDeckBefore++;
			}
		}

		//Check hand for treasure count before play
		for (j = 0; j < G.handCount[p]; j++) {
			int card = G.hand[p][j];
			if (card == copper || card == silver || card == gold) {
				treasureHandBefore++;
			}
		}


		playCard(0, 0, 0, 0, &G);

		//Check deck for treasure count after play
		for (j = 0; j < G.deckCount[p]; j++) {
			int card = G.deck[p][j];
			if (card == copper || card == silver || card == gold) {
				treasureDeckAfter++;
			}
		}

		//Check hand for treasure count after play
		for (j = 0; j < G.handCount[p]; j++) {
			int card = G.hand[p][j];
			if (card == copper || card == silver || card == gold) {
				treasureHandAfter++;
			}
		}

		if (checkOneTreasure == 25) {
			printf("The initial deck count: %d, hand count: %d, post deck: %d, post hand: %d\n", initialDeckCount, initialHandCount, G.deckCount[p], G.handCount[p]);
			printf("Confirm that hand now has one additional treasure cards.\n");
			customAssert(treasureHandAfter == treasureHandBefore + 1);
			printf("Confirm that deck now has one less treasure cards.\n");
			customAssert(treasureDeckAfter == treasureDeckBefore - 1);
			printf("Confirm that hand now has no additional cards, adventurer should be discarded\n");
			customAssert(G.handCount[p] == initialHandCount);
			printf("Confirm that deck + discard is equal to initial deck count\n");
			customAssert(G.deckCount[p] + G.discardCount[p] + 1 == initialDeckCount);

		}

		else if (treasureDeckBefore == 0) {
			printf("Confirm that hand count has no treasure.\n");
			customAssert(treasureHandAfter == treasureHandBefore);
			printf("Confirm that deck now has no treasure\n");
			customAssert(treasureDeckAfter == treasureDeckBefore );
			printf("Confirm that hand now has -1  cards, adventurer should be discarded\n");
			customAssert(G.handCount[p] == initialHandCount - 1);
			printf("Confirm that deck + discard is equal to initial deck count\n");
			customAssert(G.deckCount[p] + G.discardCount[p] == initialDeckCount);
		}
		else {
			printf("Confirm that hand now has two additional treasure cards.\n");
			customAssert(treasureHandAfter == treasureHandBefore + 2);
			printf("Confirm that deck now has two less treasure cards.\n");
			customAssert(treasureDeckAfter == treasureDeckBefore - 2);
			printf("Confirm that hand now has one additional card, adventurer should be discarded\n");
			customAssert(G.handCount[p] == initialHandCount + 1);
			printf("Confirm that deck + discard is equal to initial deck count\n");
			customAssert(G.deckCount[p] + G.discardCount[p] + 2 == initialDeckCount);
		}
		printf("Confirm that number of actions has decreased by 1\n");
		customAssert(G.numActions == initialActions - 1);

		seed++;
	}

	return 0;
}
