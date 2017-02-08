/*
File Name : unittest3.c
purpose : test endTurn function
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main(){
    //access struct variable
	struct gameState E;
	struct gameState testEndTurn;

	//give to pass the initializeGame()
	int numPlayer = 2;
	int kCards[10] = {adventurer, council_room, copper, silver, gold, remodel, smithy, village, baron, great_hall};
    int seed = 2000;
    int result;


	//init the gameState and test endTurn
	initializeGame (numPlayer,kCards, seed, &E);
    //copy memory from E to testEndTurn and give size of the struct gameState
	memcpy(&testEndTurn, &E, sizeof(struct gameState));
/*--------------------------------------*/

    printf("--------------------------------------------------------------------- \n");
    printf("Test endTurn()\n");

    // whoseTurn = 0
    testEndTurn.whoseTurn = 0;
    // pass the copy game state to endTurn function
    result =  endTurn(&testEndTurn);
    printf("Expected = 0\n");
    printf("Result = %d\n", result);
    printf("testEndTurn.whoseTurn: expected = 1, actual = %d\n\n", testEndTurn.whoseTurn);
    memcpy(&testEndTurn, &E, sizeof(struct gameState));

    // whoseTurn = 1
    printf("testEndTurn.whoseTurn = 1 \n");
    testEndTurn.whoseTurn = 1;
    result =  endTurn(&testEndTurn);
    printf("Expected = 0\n");
    printf("Result = %d\n", result);
    printf("testEndTurn.whoseTurn: expected = 0, actual = %d\n\n", testEndTurn.whoseTurn);

    return 0;
}
