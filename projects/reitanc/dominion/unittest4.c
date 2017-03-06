/*
 * unittest4.c
 */

/*
 * Include the following lines in your makefile:
 *
 * unitest1: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void testIsGameOver(){
	struct gameState MyGame;
	int ReturnValue;

	//Defaults cards, as defined in playDom
	int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	initializeGame(1, kCards, 15, &MyGame);

	/* --- TEST 1: Initialize for one player  ---  */
	ReturnValue = isGameOver(&MyGame);

    printf("\n=== BEGINNING UNIT TESTS for isGameOver()\n\n");
	if (ReturnValue == 0)
        printf("isGameOver(): PASS TEST 1.\n");
    else
        printf("isGameOver(): FAIL TEST 1. ReturnValue = %i\n", ReturnValue);
	/* --- TEST 1: Initialize for one player  ---  */

    /* --- TEST 2: Initialize for two player  ---  */
    MyGame.supplyCount[province] = 0;

    ReturnValue = isGameOver(&MyGame);
	if (ReturnValue == 1)
        printf("isGameOver(): PASS TEST 2.\n");
    else
        printf("isGameOver(): FAIL TEST 2. ReturnValue = %i\n", ReturnValue);
    /* --- TEST 2: Initialize for two player  ---  */

    /* --- TEST 3: Initialize for three player  ---  */
    initializeGame(1, kCards, 15, &MyGame);
    MyGame.supplyCount[8] = 0;

    ReturnValue = isGameOver(&MyGame);
	if (ReturnValue == 1)
        printf("isGameOver(): PASS TEST 3.\n");
    else
        printf("isGameOver(): FAIL TEST 3. ReturnValue = %i\n", ReturnValue);
    /* --- TEST 3: Initialize for three player  ---  */
    printf("\n=== COMPLETED UNIT TESTS for isGameOver()\n\n");

	return;
}

int main(){

	testIsGameOver();
	return 0;
}