/**************************************
Adam Much
CS 362
Assignment 3
updateCoins unit test

Add to Makefile:

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

**************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define UNITTEST "Update Coins"

int main() {    
   
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int bonus = 0;
	struct gameState G, testG;
	
	// Keep the same kingdom cards as the example.
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	// But use a different set for the test to check for changes.
	int testK[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// Initialize a game state and player cards.
	initializeGame(numPlayers, k, seed, &G);
	initializeGame(numPlayers, testK, seed, &testG);	
	
	

	
	printf("----------------- Unit Test: %s ----------------\n\n", UNITTEST);	

	// ----------- TEST 1:  --------------
	updateCoins(thisPlayer, &testG, bonus);	
	printf("TEST 1: Correct number coins for initial hand.\n");	
	printf("Coins = %d, expected = %d\n\n", testG.coins, G.coins);
	
	assert(testG.coins == G.coins);
	
	// ----------- TEST 2:  --------------
	bonus = 2;
	updateCoins(thisPlayer, &testG, bonus);
	printf("TEST 2: Bonus = 2.\n");	
	printf("Coins = %d, expected = %d\n\n", testG.coins, G.coins + bonus);
	
	assert(testG.coins == G.coins + bonus);
	
	// ----------- TEST 3:  --------------
	testG.hand[thisPlayer][0] = silver;
	bonus = 0;
	updateCoins(thisPlayer, &testG, bonus);
	printf("TEST 3: Bonus = 0, Silver in position 0.\n");	
	printf("Coins = %d, expected = %d\n\n", testG.coins, G.coins + bonus + 1);
	
	assert(testG.coins == G.coins + bonus + 1);
	
	// ----------- TEST 4:  --------------
	testG.hand[thisPlayer][0] = silver;
	bonus = 1;
	updateCoins(thisPlayer, &testG, bonus);
	printf("TEST 4: Bonus = 1, Silver in position 0.\n");	
	printf("Coins = %d, expected = %d\n\n", testG.coins, G.coins + bonus + 1);
	
	assert(testG.coins == G.coins + bonus + 1);
	
	// ----------- TEST 5:  --------------
	testG.hand[thisPlayer][4] = gold;
	bonus = 0;
	updateCoins(thisPlayer, &testG, bonus);
	printf("TEST 5: Bonus = 0, Silver in position 0, Gold in position 4.\n");	
	printf("Coins = %d, expected = %d\n\n", testG.coins, G.coins + bonus + 3);
	
	assert(testG.coins == G.coins + bonus + 3);
	
	// ----------- TEST 6:  --------------
	testG.hand[thisPlayer][3] = silver;
	bonus = 1;
	updateCoins(thisPlayer, &testG, bonus);
	printf("TEST 6: Bonus = 1, Silver in positions 0 and 3, Gold in position 4.\n");	
	printf("Coins = %d, expected = %d\n\n", testG.coins, G.coins + bonus + 4);
	
	assert(testG.coins == G.coins + bonus + 4);	
	

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", UNITTEST);


	return 0;
}
