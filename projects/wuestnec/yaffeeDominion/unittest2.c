#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "isGameOver"

int main(){
	int i;
	int numPlayers = 2;
	int seed = 1000;
	struct gameState g;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
			smithy, village, baron, great_hall};

	printf("--------------- Testing Card: %s ---------------\n", TESTCARD);
	// Initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &g);
	/* set supplyCount of every card to 1 */
	for(i =curse; i <= treasure_map; i++){
		g.supplyCount[i] = 1;
	}
	
	// Does function correctly return 0 with no empty supply piles?
	asserttrue("return value with no empty supply piles", isGameOver(&g), 0);
	
	// Does function correctly return 1 with empty province pile?
	g.supplyCount[province] = 0;
	asserttrue("return value with empty province pile", isGameOver(&g), 1);
	
	// Does function correctly return 1 with 3 empty supply piles?
	g.supplyCount[province] = 1;
	g.supplyCount[curse] = 0;
	g.supplyCount[estate] = 0;
	g.supplyCount[duchy] = 0;
	asserttrue("return value with 3 empty supply piles", isGameOver(&g), 1);
	
	// Does function correctly return 0 with 2 empty supply piles?
	g.supplyCount[curse] = 1;
	asserttrue("return value with 2 empty supply piles", isGameOver(&g), 0);
	
	// Does function correctly return 1 with 3 empty supply piles (including a province pile)?
	g.supplyCount[province] = 0;
	asserttrue("return value with 2 empty supply + empty province pile", isGameOver(&g), 1);
	
	printf("--------------- Completed Card: %s ---------------\n", TESTCARD);
	return 0;
}