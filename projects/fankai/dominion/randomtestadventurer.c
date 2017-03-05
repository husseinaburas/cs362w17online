//random test for adventurer
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

	  int i, j, n, r, errors=0, handPos = 0, players, player, handCount=0, numActions,deckCount, seed, rseed, address, total_count, before_count = 0, final_count = 0;
	  	  struct gameState G;

	  printf("Running Random Card Test for adventurer\n");

	rseed = time(NULL);
	srand(rseed);
	for(n = 0; n < NUM_TESTS; n++){
		final_count = 0;
		before_count = 0;

		players = rand() % 3 + 2;
		player = players;
		seed = rand();
		r = initializeGame(players, k, seed, &G);//initialize
		new_assert(r == 0, "Init game failed.");
		G.deckCount[player] = rand() % MAX_DECK;
		for(i=0; i < G.deckCount[player]; i++) {
			G.deck[player][i] = rand() % treasure_map;

		}
		G.discardCount[player] = rand() % MAX_DECK;
		for(i=0; i < G.discardCount[player]; i++) {
			G.discard[player][i] = rand() % treasure_map;
		}
		G.handCount[player] = rand() % MAX_HAND;
		for(i=0; i < G.handCount[player]; i++) {
			G.hand[player][i] = rand() % treasure_map;
			if(G.hand[player][i] >= copper && G.hand[player][i] <= gold) {
					before_count++;
			}
		}
		total_count = G.deckCount[player] + G.deckCount[player] + G.discardCount[player];
		G.hand[player][0] = adventurer;
		printf("HandCount: %d\n", G.handCount[player]);
		printf("DeckCount: %d\n", G.deckCount[player]);
		printf("DiscardCount: %d\n", G.discardCount[player]);
		printf("total_count: %d\n", total_count);
		printf("before_count: %d\n", before_count);

		handCount =  G.handCount[player];


		//Asserts
		r = cardEffect(adventurer, 1, 1, 1, &G, 0, 0);
		if(r!=0)
			errors++;

		for(i=0; i < G.handCount[player]; i++) {
			if(G.hand[player][i] >= copper && G.hand[player][i] <= gold) {
					final_count++;
			}
		}
		r = new_assert((handCount + 2) == G.handCount[player],"handCount"); // Check card was discarded and one was drawn for a net change of nothing
		if(r!=0)
			errors++;

		r = new_assert((before_count + 2) == final_count,"Treasures"); // Check action was added
		if(r!=0)
			errors++;

		printf("After\n");
		printf("HandCount: %d\n", G.handCount[player]);
		printf("DeckCount: %d\n", G.deckCount[player]);
		printf("DiscardCount: %d\n", G.discardCount[player]);
		total_count = G.deckCount[player] + G.deckCount[player] + G.discardCount[player];
		printf("total_count: %d\n", total_count);
		printf("final_count: %d\n", final_count);

	}
	if(errors > 0)
		printf("There were %d errors", errors);
	else
		printf("ALL TESTS Done\n");
	exit(0);
}

int new_assert(int c, char *s) {
	if(!c) {
		printf("Assertion failed: %s\n", s);
		if(END_Flag) {
				exit(1);
		}
		return 1;
	}
	return 0;
}
