/**************************************
Adam Much
CS 362
Assignment 3
whoseTurn unit test

Add to Makefile:

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

**************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define UNITTEST "Whose Turn"

int main() {    
   
    int seed = 1000;
    int numPlayers = 3;
   
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
	printf("TEST 1: Player 1's turn.\n");	
	printf("Turn = %d, expected = %d\n\n", whoseTurn(&testG), whoseTurn(&G));
	
	assert(whoseTurn(&testG) == whoseTurn(&G));
	
	
	// ----------- TEST 2:  --------------
	endTurn(&testG);
	printf("TEST 2: Player 2's turn.\n");	
	printf("Turn = %d, expected = %d\n\n", whoseTurn(&testG), whoseTurn(&G) + 1);
	
	assert(whoseTurn(&testG) == whoseTurn(&G) + 1);
	
	// ----------- TEST 3:  --------------
	endTurn(&testG);
	printf("TEST 3: Player 3's turn.\n");	
	printf("Turn = %d, expected = %d\n\n", whoseTurn(&testG), whoseTurn(&G) + 2);
	
	assert(whoseTurn(&testG) == whoseTurn(&G) + 2);
	
	// ----------- TEST 4:  --------------
	endTurn(&testG);
	printf("TEST 4: Player 1's second turn.\n");	
	printf("Turn = %d, expected = %d\n\n", whoseTurn(&testG), whoseTurn(&G));
	
	assert(whoseTurn(&testG) == whoseTurn(&G));	
	

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", UNITTEST);


	return 0;
}
