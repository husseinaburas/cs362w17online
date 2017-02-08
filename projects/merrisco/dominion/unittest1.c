/* 
Program: unittest1.c
Author: Scott Merrill
Date: 02/03/17

Description: This program is designed as a test case for updateCoins(). 
Preconditions: gamestate is properly so that updateCoins will function.
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
    int xtraCoins = 0;
    int dummy = 0;

    int seed = 101;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 0;

	/*Check to see if the game state is set up
	printf("\n\n\n"); 
	printf("Checking game state for player 1\n");
	printf("hand count is: %d\n", G.handCount[thisPlayer]);
    printf("number of coins before update: %d\n", G.coins);
    updateCoins(thisPlayer,&G,0);
    printf("number of coins before after: %d\n", G.coins); */
/**********************************************************************************************/

    if(updateCoins(thisPlayer,&G,0) == 0)
        printf("updateCoins(): PASS for initial run.\n");
    else
        printf("updateCoins(): FAIL for initial run\n");

    if(G.coins == 4)
        printf("updateCoins(): PASS for correct update to coins.\n");
    else
        printf("updateCoins(): FAIL for correct update to coins\n");
   
    if(updateCoins(3,&G,0) == 0)
        printf("updateCoins(): FAIL when wrong player was passed in.\n");
    else
        printf("updateCoins(): PASS when wrong player was passed in\n");
    
// check to see if bonus is counted.    
    xtraCoins = 2;
    updateCoins(thisPlayer,&G,0);
    dummy = G.coins;
    updateCoins(thisPlayer,&G,xtraCoins);

    if(G.coins == (dummy + xtraCoins))
        printf("updateCoins(): PASS when bonus is factored in.\n");
    else
        printf("updateCoins(): FAIL when bonus is factored in\n");
          
    



    


    


// end of program
return 0;
}