/*
 * cardtest4.c
 *
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

#define TESTCARD "adventurer"

void cus_assert(int test)
{
	if (test == 0) {
		printf ("Test Failed");
	}
	return;
}

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
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	G.handCount[0] = 1;
	
	G.hand[0][0] = adventurer;
	
	//Setup deck with 2 treasure cards 
	G.deck[0][1] = copper;
	G.deck[0][2] = mine;
	G.deck[0][3] = copper;
	G.deck[0][4] = smithy;
	//Run adventurer
	G.
	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);


	

	

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


