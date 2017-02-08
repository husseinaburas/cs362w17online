/* 
Program: unittest4.c
Author: Scott Merrill
Date: 02/05/17

Description: This program is designed as a test case for whoseTurn(). 
Preconditions: gamestate is initialized properly.
Postconditions: Printout  to the screen the results of the tests. 
*/


/***************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
    int seed = 101;
    int numPlayers = 2;
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
/*****************************************************************************/
	

	if(whoseTurn(&G) == 0)   
		printf("whoseTurn(): PASS for initial check\n");
    else
        printf("whoseTurn(): FAIL for initial check\n");

    G.whoseTurn = 1; //change the turn to player 2
   	if(whoseTurn(&G) == 1)   
		printf("whoseTurn(): PASS for player 2's turn\n");
    else
        printf("whoseTurn(): FAIL for player 2's turn\n");

	endTurn(&G);
	if(whoseTurn(&G) == 0)   
		printf("whoseTurn(): PASS for end turn function\n");
    else
        printf("whoseTurn(): FAIL for end turn function\n");	    


    return 0;

}