/*
 * cardtest2.c
 *
 * Based off a model for testing a card that was provided in class portal.
 * Adapted for the use of the cards that were being tested in Assignment 3
 * Oregon State University - CS 362 Winter 2017
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, great_hall, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	newCards = 1;

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	discarded = testG.discardCount[thisPlayer]-G.discardCount[thisPlayer];

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
	printf("\ncards in player hand before adventurer: ");
	for (i = 0; i < G.handCount[thisPlayer]; i++){
		printf("%i; ", G.hand[thisPlayer][i]);
	}
	printf("\ncards in player hand after adventurer: ");
	for (i = 0; i < testG.handCount[thisPlayer]; i++){
		printf("%i; ", testG.hand[thisPlayer][i]);
	}
	printf("\ncards in player deck before adventurer: ");
	for (i = 0; i < G.deckCount[thisPlayer]; i++){
		printf("%i; ", G.deck[thisPlayer][i]);
	}
	printf("\ncards in player deck after adventurer: ");
	for (i = 0; i < testG.deckCount[thisPlayer]; i++){
		printf("%i; ", testG.discard[thisPlayer][i]);
	}
	printf("\ncards in player discard before adventurer: ");
	for (i = 0; i < G.discardCount[thisPlayer]; i++){
		printf("%i; ", G.discard[thisPlayer][i]);
	}
	printf("\ncards in player discard after adventurer: ");
	for (i = 0; i < testG.discardCount[thisPlayer]; i++){
		printf("%i; ", testG.discard[thisPlayer][i]);
	}

	if (discarded >= 1)
	{
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	}else{
		printf("\n >>>>> FAILED: Testing complete %s <<<<<\n\n", TESTCARD);
	}
	
	return 0;
}


