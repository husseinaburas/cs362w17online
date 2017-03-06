/* 
Program: cardtest3.c
Author: Scott Merrill
Date: 02/05/17

Description: This program is designed as a test case for playvillage(). 
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
    G.hand[0][5] = 14;
    G.handCount[0]++;
    int handCount = G.handCount[0];
    int discard = G.discardCount[0];

/*****************************************************************************/
	
	if(cardEffect(adventurer,0,0,0,&G,5,0) == 1)   
		printf("playVillage(): PASS for initial check\n");
    else
        printf("playVillage(): FAIL for initial check\n");

	if(G.discardCount[0] == (discard +1))   
		printf("playVillage(): PASS for discard pile check\n");
    else
        printf("playVillage(): FAIL for discard pile check\n");

	if(G.handCount[0] == (handCount + 1))   
		printf("playVillage(): PASS for hand count check\n");
    else
        printf("playVillage(): FAIL for hand count check\n");


	if( G.hand[0][5] != 14)   
		printf("playVillage(): PASS for village not still in hand check\n");
    else
        printf("playVillage(): FAIL for village not still in hand check\n");   

	if( G.numActions == 2)   
		printf("playVillage(): PASS for village decrement numActions check\n");
    else
        printf("playVillage(): FAIL for village decrement numActions check\n");   





    return 0;
}