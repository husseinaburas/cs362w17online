/* 
Program: unittest3.c
Author: Scott Merrill
Date: 02/05/17

Description: This program is designed as a test case for isGameOver(). 
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
    
	int i;
    int seed = 101;
    int numPlayers = 2;
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
/*****************************************************************************/

	if(isGameOver(&G) == 0)   
		printf("buyCard(): PASS for initial check\n");
    else
        printf("buyCard(): FAIL for initial check\n"); 


    G.supplyCount[3] = 0;	// change supply count for province
    if(isGameOver(&G) == 1)
    	printf("buyCard(): PASS for proper end if no province cards left\n");
    else
        printf("buyCard(): FAIL for proper end if no province cards left\n"); 	
    G.supplyCount[3] = 45; // reverting change make to supply count

    // making 3 kingdom cards supplies' = 0
    for(i=6;i<8;i++)
    	G.supplyCount[i] = 0;

    if(isGameOver(&G) == 0)
    	printf("buyCard(): PASS for proper end if 3 kingdom cards are out of supply\n");
    else
        printf("buyCard(): FAIL for proper end if kingdom cards are out of supply\n"); 	

    G.supplyCount[9] = 0;

    if(isGameOver(&G) == 1)
    	printf("buyCard(): PASS for proper end if 3 kingdom cards are out of supply\n");
    else
        printf("buyCard(): FAIL for proper end if kingdom cards are out of supply\n"); 	



    return 0;
}