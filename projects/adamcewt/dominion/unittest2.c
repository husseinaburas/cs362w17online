/* 
 * Name: Thomas Adamcewicz
 * Due Date: 2/7/17
 * Function: isGameOver(struct gamestate *state)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


 //assertTrue function in place of assert
 void assertTrue(int val) {
	if (val){
		printf("TEST PASSED\n");
	}
	else{
		printf("TEST FAILED\n");
	}
}


int main() {

	printf("\n**** isGameOver() TESTING BEGINNING ****\n");

	int i;
	int tFlag = 0;
    int seed = 1000;
    int numPlayers = 2;
    int p1 = 0;
    int p2 = 1;
    int cards[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall};
    struct gameState G;

    //start game
    initializeGame(numPlayers, cards, seed, &G);

    //TEST-1: Fresh game, make sure isGameOver returns 0
	printf("TEST-1\n **GAME INITIALIZED CHECKING isGameOver()**\n");
	printf("Checking isGameOver returns 0: ");
	assertTrue(isGameOver(&G) == 0);

	//TEST-2: Set province equal to 0 and check that isGameOver returns 1
	printf("TEST-2\n **CHECKING  isGameOver BASED ON NUMBER OF PROVINCES**\n");
	printf("Checking isGameOver returns 1 when 0 provinces: ");
	G.supplyCount[province] = 0;
	assertTrue(isGameOver(&G) == 1);
	printf("Checking isGameOver returns 0 when there is 1 province: ");
	G.supplyCount[province] = 1;
	assertTrue(isGameOver(&G) == 0);
	printf("Checking isGameOver returns 0 when there is -1 province: ");
	G.supplyCount[province] = -1;
	assertTrue(isGameOver(&G) == 0);


	//TEST-3: Check isGameOver based on 3 supply piles being empty
	printf("TEST-3\n **CHECKING  isGameOver BASED ON 3 SUPPLY PILES EMPTY OR NOT**\n");
	printf("Checking isGameOver returns 0 when curse pile is empty: ");
	G.supplyCount[0] = 0;
	assertTrue(isGameOver(&G) == 0);
	printf("Checking isGameOver returns 0 when curse and estate piles are empty: ");
	G.supplyCount[1] = 0;
	assertTrue(isGameOver(&G) == 0);
	printf("Checking isGameOver returns 1 when curse, estate and duchy piles are empty: ");
	G.supplyCount[2] = 0;
	assertTrue(isGameOver(&G) == 1);
	printf("Checking isGameOver returns 1 when curse and province piles are empty: ");
	G.supplyCount[province] = 0;
	G.supplyCount[1] = 1;
	G.supplyCount[2] = 1;
	assertTrue(isGameOver(&G) == 1);
	printf("Checking isGameOver returns 1 when 4 supply piles are empty (not province): ");
	G.supplyCount[province] = 1;
	G.supplyCount[1] = 0;
	G.supplyCount[2] = 0;
	G.supplyCount[4] = 0;
 	assertTrue(isGameOver(&G) == 1);

 	printf("\n**** isGameOver() TESTING COMPLETE ****\n");

    return 0;
}