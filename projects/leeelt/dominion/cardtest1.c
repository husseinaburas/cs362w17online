/*
 * cardtest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
	int i, j, m;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int handCount;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// set up deck for player 1 and player 2
	G.deck[0][0] = copper;
	G.deck[0][1] = smithy;
	G.deck[0][2] = province;
	G.deck[0][3] = smithy;
	G.deck[0][4] = gold;
	G.deckCount[0] = 5;

	G.deck[1][0] = gold;
	G.deck[1][1] = silver;
	G.deck[1][2] = province;
	G.deck[1][3] = duchy;
	G.deck[1][4] = gold;
	G.deckCount[1] = 5;


	// set up hand for player 1 and player 2
	G.hand[0][0] = adventurer;
	G.hand[0][1] = gold;
	G.hand[0][2] = silver;
	G.hand[0][3] = smithy;
	G.hand[0][4] = adventurer;
	G.handCount[0] = 5;

	memcpy(&testG, &G, sizeof(struct gameState));
	printf("Running playAdventurer...\n");
	playAdventurer(&testG);
	printf("Number of cards in hand = %d, expected = %d\n", testG.handCount[0], G.handCount[0] + 1);
	printf("New cards are %d and %d, expected = %d (copper) and %d (gold)\n",testG.hand[0][4], testG.hand[0][5], copper, gold);
	printf("Discard pile has %d cards, expected = %d", testG.discardCount[0], 4);
	return 0;
}


void asserttrue(int val1, int val2){
	if (val1 != val2) printf("Test failed.");
	else printf("Test passed.");
}