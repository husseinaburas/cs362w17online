#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "updateCoins"

int main(){
	int i, r;
	int numPlayers = 2;
	int seed = 1000;
	int player1 = 0, player2 = 1;
	int handCount;
	int bonus;
	struct gameState g;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
			smithy, village, baron, great_hall};

	printf("--------------- Testing Card: %s ---------------\n", TESTCARD);
	// Initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &g);
	// Initially set bonus to 0 and handCount to 0 for both players
	bonus = 0;
	handCount = 0;
	g.handCount[player1] = handCount;
	g.handCount[player2] = handCount;

	// Did the function work correctly (should return a 0)?	
	r = updateCoins(player1, &g, bonus);
	asserttrue("returned 0 as expected", r, 0);
	// Does function update coin count correctly with 0 treasure cards & 0 bonus?
	asserttrue("coins with 0 treasure cards & 0 bonus", g.coins, handCount + bonus);
	// Does function update coin count correctly with 0 treasure cards & 5 bonus?
	bonus = 5;
	r = updateCoins(player1, &g, bonus);
	asserttrue("returned 0 as expected", r, 0);
	asserttrue("coins with 0 treasure cards & 5 bonus", g.coins, handCount + bonus);
	// Does function update coin count correctly with 3 copper cards & 5 bonus?
	handCount = 3;
	g.handCount[player1] = handCount;
	for(i = 0; i < handCount; i++){
		g.hand[player1][i] = copper;
	}
	r = updateCoins(player1, &g, bonus);
	asserttrue("returned 0 as expected", r, 0);
	asserttrue("coins with 3 coppers & 5 bonus", g.coins, handCount * 1 + bonus);
	// Does function update coin count correctly with 3 silver cards & 5 bonus?
	for(i = 0; i < handCount; i++){
		g.hand[player1][i] = silver;
	}
	r = updateCoins(player1, &g, bonus);
	asserttrue("returned 0 as expected", r, 0);
	asserttrue("coins with 3 silvers & 5 bonus", g.coins, handCount * 2 + bonus);
	// Does function update coin count correctly with 3 gold cards & 5 bonus?
	for(i = 0; i < handCount; i++){
		g.hand[player1][i] = gold;
	}
	r = updateCoins(player1, &g, bonus);
	asserttrue("returned 0 as expected", r, 0);
	asserttrue("coins with 3 golds & 5 bonus", g.coins, handCount * 3 + bonus);
	// Does function update coin count correctly with 3 non-treasure cards & 5 bonus?
	for(i = 0; i < handCount; i++){
		g.hand[player1][i] = adventurer;
	}
	r = updateCoins(player1, &g, bonus);
	asserttrue("returned 0 as expected", r, 0);
	asserttrue("coins with 3 non-treasure cards & 5 bonus", g.coins, 0 + bonus);
	
	printf("--------------- Completed Card: %s ---------------\n", TESTCARD);
	return 0;
}