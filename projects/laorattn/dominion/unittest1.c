/* -----------------------------------------------------------------------
 * Unit test for isGameOver function
 * Author: Namtalay Laorattanavech
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"



int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    
	printf("Unittest1: isGameOver\n");
	printf("Starting the game...\n");
	int maingame = initializeGame(numPlayer, k, seed, &G);
	assert(maingame==0);
	
	//check no more Province card
	G.supplyCount[province]=0;
	printf("Checking: no more Province card in the deck\n");
	assert(isGameOver(&G)==1 && ": failed\n");
	
	//check still have Province card
	G.supplyCount[province]=3;
	printf("Checking: still have Province card in the deck\n");
	assert(isGameOver(&G)==0 && ": failed\n");
	
	//set supply pile to 0
	G.supplyCount[0] = 0;
	G.supplyCount[1] = 0;
	G.supplyCount[2] = 0;
	printf("Checking: supply pile is empty\n");
	assert(isGameOver(&G)==1 && ": failed\n");
	
	//set supply pile not empty
	G.supplyCount[0] = 1;
	G.supplyCount[1] = 1;
	G.supplyCount[2] = 1;
	printf("Checking: supply pile is NOT empty\n");
	assert(isGameOver(&G)==0 && ": failed\n");
   

    printf("All tests passed!\n");

    return 0;
}