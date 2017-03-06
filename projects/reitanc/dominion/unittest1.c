/*
 * unittest1.c
 */

/*
 * Include the following lines in your makefile:
 *
 * unitest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void testInitializeGame(){
	struct gameState MyGame;
	int ReturnValue;
	
	//Defaults cards, as defined in playDom
	int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    printf("\n=== BEGINNING UNIT TESTS for initializeGame()\n\n");
	/* --- TEST 1: Initialize for one player  ---  */
	ReturnValue = initializeGame(1, kCards, 5, &MyGame);
	if (ReturnValue == -1)
        printf("initializeGame(): PASS when testing 1 player setup.\n");
    else
        printf("initializeGame(): FAIL when testing 1 player setup.\n");
	/* --- TEST 1: Initialize for one player  ---  */

    /* --- TEST 2: Initialize for two player  ---  */
    ReturnValue = initializeGame(2, kCards, 5, &MyGame);
    if (ReturnValue == 0 && MyGame.numPlayers == 2)
        printf("initializeGame(): PASS when testing 2 player setup.\n");
    else
        printf("initializeGame(): FAIL when testing 2 player setup.\n");
    /* --- TEST 2: Initialize for two player  ---  */

    /* --- TEST 3: Initialize for three player  ---  */
    ReturnValue = initializeGame(3, kCards, 5, &MyGame);
    if (ReturnValue == 0 && MyGame.numPlayers == 3)
        printf("initializeGame(): PASS when testing 3 player setup.\n");
    else
        printf("initializeGame(): FAIL when testing 3 player setup.\n");
    /* --- TEST 3: Initialize for three player  ---  */

    /* --- TEST 4: Initialize for four player  ---  */
    ReturnValue = initializeGame(4, kCards, 5, &MyGame);
    if (ReturnValue == 0 && MyGame.numPlayers == 4)
        printf("initializeGame(): PASS when testing 4 player setup.\n");
    else
        printf("initializeGame(): FAIL when testing 4 player setup.\n");
    /* --- TEST 4: Initialize for four player  ---  */

    /* --- TEST 5: Initialize for one player  ---  */
	ReturnValue = initializeGame(5, kCards, 5, &MyGame);
	if (ReturnValue == -1)
        printf("initializeGame(): PASS when testing 5 player setup.\n");
    else
        printf("initializeGame(): FAIL when testing 5 player setup.\n");
	/* --- TEST 1: Initialize for one player  ---  */
    printf("\n=== COMPLETED UNIT TESTS for initializeGame()\n\n");

	return;
}

int main(){

	testInitializeGame();
	return 0;
}