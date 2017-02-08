/**************************************
Adam Much
CS 362
Assignment 3
Is Game Over unit test

Add to Makefile:

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

**************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define UNITTEST "Is Game Over"

int main() {    
   
    int seed = 1000;
    int numPlayers = 2;
    //int thisPlayer = 0;
	//int bonus = 0;
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
	printf("TEST 1: No game changes.\n");	
	printf("Test Game = %d, expected = %d\n\n", isGameOver(&testG), isGameOver(&G));
	
	assert(isGameOver(&testG) == isGameOver(&G));
	
	
	// ----------- TEST 2:  --------------
	testG.supplyCount[province] = 0;
	printf("TEST 2: Province stack empty.\n");	
	printf("Test Game = %d, expected = %d\n\n", isGameOver(&testG), isGameOver(&G) + 1);
	
	assert(isGameOver(&testG) == isGameOver(&G) + 1);
	
	// ----------- TEST 3:  --------------
	testG.supplyCount[province] = 8;
	testG.supplyCount[1] = 0;
	testG.supplyCount[2] = 0;	
	printf("TEST 3: Province stack non-empty two other piles empty.\n");	
	printf("Test Game = %d, expected = %d\n\n", isGameOver(&testG), isGameOver(&G));
	
	assert(isGameOver(&testG) == isGameOver(&G));
	
	// ----------- TEST 4:  --------------	
	testG.supplyCount[3] = 0;	
	printf("TEST 4: Province stack non-empty three other piles empty.\n");	
	printf("Test Game = %d, expected = %d\n\n", isGameOver(&testG), isGameOver(&G) + 1);
	
	assert(isGameOver(&testG) == isGameOver(&G) + 1);
	
	// ----------- TEST 5:  --------------	
	testG.supplyCount[4] = 0;	
	printf("TEST 5: Province stack non-empty four other piles empty.\n");	
	printf("Test Game = %d, expected = %d\n\n", isGameOver(&testG), isGameOver(&G) + 1);
	
	assert(isGameOver(&testG) == isGameOver(&G) + 1);
	
	// ----------- TEST 6:  --------------	
	testG.supplyCount[province] = 0;	
	printf("TEST 6: Province stack empty four other piles empty.\n");	
	printf("Test Game = %d, expected = %d\n\n", isGameOver(&testG), isGameOver(&G) + 1);
	
	assert(isGameOver(&testG) == isGameOver(&G) + 1);	
	

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", UNITTEST);


	return 0;
}
