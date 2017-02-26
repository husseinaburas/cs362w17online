/* Author: Bilal Saleem
 * Date: 1/31/17
 * Testing function: struct gameState* newGame()
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0

void assert(bool j){
	if (j == 0){
		printf("Test failed");
	}
} 

int main() {
	printf("unittest1.c\n");
	/*************** TEST ONE ******************
 	* The function shouldn't return null value
 	********************************************/
	struct gameState * G = 0;

	G = newGame();

	assert(G != 0); 

	/************* TEST TWO ***********************
 	* See if you  can alter some  of the variables of 
 	* struct gameState object -- and hence what
 	* you allocated memory for is actually a 
 	* struct gameState
 	***********************************************/
	
	G->numPlayers = 2;
	G->outpostPlayed = 1;
	G->whoseTurn = 1;
	G->numActions = 3;
	G->coins = 10;

	assert(G->numPlayers == 2);
	assert(G->outpostPlayed == 1);
	assert(G->whoseTurn == 1);
	assert(G->numActions == 3);
	assert(G->coins == 10);

	
	
	return 0;
}

