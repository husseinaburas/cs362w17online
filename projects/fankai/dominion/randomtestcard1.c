//random test for great_hall
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define END_Flag 0
#define NUM_TESTS 10000

int new_assert(int c, char *s);

int main() {

	  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, great_hall};

	  int i, j, n, r, errors=0, handPos = 0, players, player, handCount, numActions,deckCount, seed, rseed, address, total_count;
	  	  struct gameState G;

	  printf("Running Random Card Test for great_hall\n");

	rseed = time(NULL);
	srand(rseed);
	for(n = 0; n < NUM_TESTS; n++){

		players = rand() % 3 + 2;
		player = players;
		seed = rand();

		printf("Init Game...\n");
		r = initializeGame(players, k, seed, &G);
		new_assert(r == 0, "Init game failed.");

		G.deckCount[player] = rand() % MAX_DECK;
		G.discardCount[player] = rand() % MAX_DECK;
		G.handCount[player] = rand() % MAX_HAND;
		total_count = G.deckCount[player] + G.deckCount[player] + G.discardCount[player];


		printf("HandCount: %d\n", G.handCount[player]);
		printf("DeckCount: %d\n", G.deckCount[player]);
		printf("DiscardCount: %d\n", G.discardCount[player]);
		printf("total_count: %d\n", total_count);

		handCount =  G.handCount[player];
		numActions = G.numActions;


		r = cardEffect(great_hall, 0, 0, 0, &G, 0, 0);
		if(r!=0)
			errors++;

		r = new_assert(handCount == G.handCount[player],"handCount");
		if(r!=0)
			errors++;

		r = new_assert(G.numActions == numActions + 1,"numActions");
		if(r!=0)
			errors++;

		printf("HandCount: %d\n", G.handCount[player]);
		printf("DeckCount: %d\n", G.deckCount[player]);
		printf("DiscardCount: %d\n", G.discardCount[player]);
		total_count = G.deckCount[player] + G.deckCount[player] + G.discardCount[player];
		printf("total_count: %d\n", total_count);

	}	//End test block
	if(errors > 0)
		printf("There were %d errors", errors);
	else
		printf("ALL TESTS DONE\n");
	exit(0);
}

int new_assert(int c, char *s) {
	if(!c) {
		printf("Assertion failed: %s\n", s);
		return 1;
		if(END_Flag) {
				exit(1);
		}
	}
	return 0;
}
