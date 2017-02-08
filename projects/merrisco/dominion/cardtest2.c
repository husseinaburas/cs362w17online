/* 
Program: cardtest2.c
Author: Scott Merrill
Date: 02/05/17

Description: This program is designed as a test case for playadventurer(). 
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
    G.hand[0][5] = 7;
    G.handCount[0]++;
    int handCount = G.handCount[0];
    int discard = G.discardCount[0];

/*****************************************************************************/
	
	if(cardEffect(adventurer,0,0,0,&G,5,0) == 1)   
		printf("playAdventurer(): PASS for initial check\n");
    else
        printf("playAdventurer(): FAIL for initial check\n");

	if(G.discardCount[0] == (discard +1))   
		printf("playAdventurer(): PASS for discard pile check\n");
    else
        printf("playAdventurer(): FAIL for discard pile check\n");

	if(G.handCount[0] == (handCount + 2))   
		printf("playAdventurer(): PASS for hand count check\n");
    else{
        printf("playAdventurer(): FAIL for hand count check\n");
        if(G.handCount[0] == (handCount + 4))
        	printf("playAdventurer(): FAIL for number of cards drawn check\n");
    }

	if( G.hand[0][5] != 6)   
		printf("playAdventurer(): PASS for adventurer not still in hand check\n");
    else
        printf("playAdventurer(): FAIL for adventurer not still in hand check\n");   

	if( G.numActions == 0)   
		printf("playAdventurer(): PASS for adventurer decrement numActions check\n");
    else
        printf("playAdventurer(): FAIL for adventurer decrement numActions check\n");   





    return 0;
}