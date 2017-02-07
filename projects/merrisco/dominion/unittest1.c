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
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 101;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 0;

	//Check to see if the game state is set up
	printf("\n\n\n"); 
	printf("Checking game state for player 1\n");
	printf("hand count is: %d\n", G.handCount[thisPlayer]);
    printf("number of coins before update: %d\n", G.coins);
    // end of check
    updateCoins(thisPlayer,&G,0);
    printf("number of coins before after: %d\n", G.coins);


    


    


// end of program
return 0;
}