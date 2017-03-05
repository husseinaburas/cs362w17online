/* *****************************************************************************
 * Antonina (Toni) York
 * OSU CS 362 Winter 2017
 * Assignment 3 Unit Test 4
 *
 * Tests isGameOver() in dominion.c
 * ************************************************************************** */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define PRINT_TESTS 0

void printif(char* string, int value1, int value2) {
	if(PRINT_TESTS == 1)
		printf(string, value1, value2);
}

int main() {
	
	int i = 0;
	int provincesleft = 0;
	int emptysupplypiles = 0;
	int result = 0;
	int expected = 0;
	int seed = 1000;
	int numPlayers = 4;
	int allPassed = 1;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           council_room, tribute, smithy};
			   
	struct gameState game;
	
	printf("Testing isGameOver()...\n\n");
	
	for(provincesleft = 0; provincesleft < 4; provincesleft++) {
		for(emptysupplypiles = 0; emptysupplypiles < 6; emptysupplypiles++) {
			// find expected value based on current loop conditions
			if((provincesleft == 0) || (emptysupplypiles > 2))
				expected = 1;
			else expected = 0;
			// clear game state and initialize game
			memset(&game, 23, sizeof(struct gameState));
			result = initializeGame(numPlayers, k, seed, &game);
			// set game state based on loop conditions
			game.supplyCount[province] = provincesleft;
			for(i = 0; i < emptysupplypiles; i++)
				game.supplyCount[5+i] = 0; // make sure to be past where the provinces are stored
			// test and print results
			result = isGameOver(&game);
			if(result != expected) {
				printif("%d provinces left, %d empty supply piles... failed!\n", provincesleft, emptysupplypiles);
				allPassed = 0;
			}
			else printif("%d provinces left, %d empty supply piles... passed!\n", provincesleft, emptysupplypiles);
			printif("   Expected: %d   Actual: %d\n", expected, result);
		}
	}
	
	if(PRINT_TESTS == 1)
		printf("\n");
	if(allPassed == 1)
		printf("All tests passed!\n");
	else printf("One or more tests failed!\n");
	
	return 0;
}