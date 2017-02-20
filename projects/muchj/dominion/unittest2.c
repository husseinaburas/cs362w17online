/**************************************
Adam Much
CS 362
Assignment 3
Get Cost unit test

Add to Makefile:

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

**************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define UNITTEST "Get Cost"

int main() {    
   
    int seed = 1000;
    int numPlayers = 2;
    //int thisPlayer = 0;
	int cost, difference;
	int i;
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
	printf("TEST 1: Difference should always be zero regardless of index.\n");	
	for(i = -1; i < 28; i++){
		cost = getCost(i);
		
		// Cost 0
		if(i == 0 || i == 4){
			difference = cost - 0;
			printf("index = %d, difference = %d\n\n", i, difference);
		}
		
		// Cost 2
		else if (i == 1 || i == 22){
			difference = cost - 2;
			printf("index = %d, difference = %d\n\n", i, difference);
		}
		
		// Cost 3
		else if (i == 5 || i == 14 || i == 16 || i == 18 || i == 20){
			difference = cost - 3;
			printf("index = %d, difference = %d\n\n", i, difference);
		}
		
		// Cost 4
		else if (i == 9 || i == 10 || i == 12 || i == 13 || i == 15 || i == 21 || i == 24 || i == 25 || i == 26){
			difference = cost - 4;
			printf("index = %d, difference = %d\n\n", i, difference);
		}
		
		// Cost 5
		else if (i == 2 || i == 8 || i == 11 || i == 17 || i == 19 || i == 23){
			difference = cost - 5;
			printf("index = %d, difference = %d\n\n", i, difference);
		}
		
		// Cost 6
		else if (i == 6 || i == 7){
			difference = cost - 6;
			printf("index = %d, difference = %d\n\n", i, difference);
		}
		
		// Cost 8
		else if (i == 3){
			difference = cost - 8;
			printf("index = %d, difference = %d\n\n", i, difference);
		}
		
		// Cost -1
		else{
			difference = cost + 1;
			printf("index = %d, difference = %d\n\n", i, difference);
		}
	};
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", UNITTEST);


	return 0;
}
