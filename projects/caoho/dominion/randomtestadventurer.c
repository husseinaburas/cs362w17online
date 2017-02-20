#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "math.h"



int main(int argc, char **argv) {


	int i;
	int randSeed;
	int const k[10] = { adventurer, gardens, embargo, village, minion, mine,
			cutpurse, sea_hag, tribute, smithy };

	//determine if seed provided, if not use 10 as default
	if (argc != 2) {
		randSeed = 10;
	} else {
		randSeed = (atoi(argv[1]));
	}
	PutSeed(randSeed);

	const int testNum = 1000;
	int loopCounter;
	// loop through tests
	for (loopCounter = 0; loopCounter < testNum; loopCounter++) {

		printf(
				"==============================>Starting %d test out of %d\n for the Village Card",
				(loopCounter + 1), testNum);

		int numPlayers = (int) floor(Random() * 3 + 2); // initialize random player number
		int currentPlayer = (int) floor(Random() * numPlayers); // initialize random current turn
		int startUpSeed = (int) floor(Random() * testNum + 1); // initialize random startup seed

		int initActionNum, initHandNum, initDeckNum;

		struct gameState G;

		G.whoseTurn = currentPlayer;
		G.numActions = (int) floor(Random() * (numPlayers - 1) + 1);
		G.handCount[currentPlayer] = 1;


		// clear game state and initialize game
		initializeGame(numPlayers, k, startUpSeed, &G);
		//save the initial state
		initActionNum = G.numActions;
		initHandNum = G.handCount[currentPlayer];
		initDeckNum = G.deckCount[currentPlayer];

		printf(
				"Testing Adventurer with player number = %d, current player = %d, action number = %d, hand count = %d, deck count = %d \n",
				numPlayers, currentPlayer, initActionNum, initHandNum,
				initDeckNum);


		int card = (int) floor(Random() * 3 + 4);
		int state = (int) floor(Random() * 3 + 1);
		int maxHandSize = 5;
		int initHandSize = 1;
		int initDeckSize = 15;
		int total = 0;

		int expected, result;

		switch (state) {
		// case where cards are all in deck
		case 1:
			G.phase = 0;
			G.hand[currentPlayer][0] = adventurer;
			for (i = 1; i < maxHandSize; i++)
				G.hand[currentPlayer][i] = estate;
			G.deckCount[currentPlayer] = initDeckNum;
			for (i = 0; i < total; i++)
				G.deck[currentPlayer][i] = card;
			for (i = total; i < initDeckSize; i++)
				G.deck[currentPlayer][i] = estate;
			playAdventurer(&G);
			// cards added to currentPlayer's hand
			expected = 2;
			result = 0;
			for (i = 0; i < G.handCount[currentPlayer]; i++)
				if (G.hand[currentPlayer][i] == card)
					result++;
			assertMsg("Checking deck loses one card", expected, result);

			expected = initHandSize - 1 + 2; // Adventurer removed, 2 treasure gained
			result = G.handCount[currentPlayer];
			assertMsg(
					"Checking Adventurer removed, all in deck, hand size adjusted",
					expected, result);

			expected = 0;
			result = 0;
			for (i = 0; i < G.deckCount[currentPlayer]; i++)
				if (G.deck[currentPlayer][i] == card)
					result++;
			assertMsg(
					"Checking cards removed from currentPlayer's deck, all in deck, removed from deck",
					expected, result);

			expected = initDeckSize - 2;
			result = G.deckCount[currentPlayer];
			assertMsg(
					"Checking cards removed from currentPlayer's deck, all in deck, deck size adjusted",
					expected, result);
			break;

		case 2:
			// case where cards are all in discards
			G.phase = 0;
			G.hand[currentPlayer][0] = adventurer;
			for (i = 1; i < maxHandSize; i++)
				G.hand[currentPlayer][i] = estate;
			G.deckCount[currentPlayer] = initDeckSize - total;
			for (i = 0; i < initDeckSize - total; i++)
				G.deck[currentPlayer][i] = estate;
			G.discardCount[currentPlayer] = total;
			for (i = 0; i < total; i++)
				G.discard[currentPlayer][i] = card;
			playAdventurer(&G);
			// cards added to currentPlayer's hand
			expected = 2;
			result = 0;
			for (i = 0; i < G.handCount[currentPlayer]; i++)
				if (G.hand[currentPlayer][i] == card)
					result++;
			assertMsg("Checking all in discard, added to hand", expected,
					result);

			expected = initHandSize - 1 + 2; // Adventurer removed, 2 treasure gained
			result = G.handCount[currentPlayer];
			assertMsg(
					"Checking Adventurer removed, all in deck, hand size adjusted",
					expected, result);

			expected = 0;
			result = 0;
			for (i = 0; i < G.deckCount[currentPlayer]; i++)
				if (G.deck[currentPlayer][i] == card)
					result++;
			assertMsg(
					"Checking cards removed from currentPlayer's deck, all in deck, removed from deck",
					expected, result);

			expected = initDeckSize - total - 2;
			result = G.deckCount[currentPlayer];
			assertMsg(
					"Checking cards removed from currentPlayer's deck, all in deck, deck size adjusted",
					expected, result);
			break;
			// case where 1 is in deck and rest are in discards
		case 3:
			G.phase = 0;
			for (i = 1; i < maxHandSize; i++)
				G.hand[currentPlayer][i] = estate;
			G.deckCount[currentPlayer] = initDeckSize - (total - 1);
			G.deck[currentPlayer][0] = card;
			for (i = 1; i < initDeckSize - (total - 1); i++)
				G.deck[currentPlayer][i] = estate;
			G.discardCount[currentPlayer] = (total - 1);
			for (i = 0; i < (total - 1); i++)
				G.discard[currentPlayer][i] = card;
			playAdventurer(&G);
			// cards added to currentPlayer's hand
			// cards added to currentPlayer's hand
			expected = 2;
			result = 0;
			for (i = 0; i < G.handCount[currentPlayer]; i++)
				if (G.hand[currentPlayer][i] == card)
					result++;
			assertMsg("Checking all in discard, added to hand", expected,
					result);

			expected = initHandSize - 1 + 2; // Adventurer removed, 2 treasure gained
			result = G.handCount[currentPlayer];
			assertMsg(
					"Checking Adventurer removed, all in deck, hand size adjusted",
					expected, result);

			expected = 0;
			result = 0;
			for (i = 0; i < G.deckCount[currentPlayer]; i++)
				if (G.deck[currentPlayer][i] == card)
					result++;
			assertMsg(
					"Checking cards removed from currentPlayer's deck, all in deck, removed from deck",
					expected, result);

			expected = initDeckSize - (total - 1) - 2;
			result = G.deckCount[currentPlayer];
			assertMsg(
					"Checking cards removed from currentPlayer's deck, all in deck, deck size adjusted",
					expected, result);
			break;

			// default case - should never see this
		default:
			printf("Something went terribly awry with treasureState!\n");
		}
	}
	return 0;
}
