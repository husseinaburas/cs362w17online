/*
Card to test:  village
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>


void comparer(int x, int y) // used to check if two values are the same. 
{
	if (x != y)
	{
		printf("Test failed!\n");
		return 1;
	}
	else 
	{
		printf("Test passed!\n");
		return 0;
	}
}

int main () 
{
	printf("-----CURRENT TEST: Village Card -----\n");
	struct gameState currentgame; // create new game and set num players
	int numplayers = 2;
	int x, pre, post, check;
	int randomseed = 777;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall}; // set kingdom cards array
	memset(&currentgame, 23, sizeof(struct gameState));
	int gameinit = initializeGame(numplayers, k, randomseed, &currentgame); // initialize the game
	currentgame.hand[0][0]  = village; // force into players hand
	
	int * bonus = 0;
	cardEffect(village, 1,1,1, &currentgame, 0, bonus); // play the card
	
	printf("Testing if the player's hand count is the same.\n");
	comparer(currentgame.handCount[0] , 5);
	
	printf("Testing if the player's actions is increased by 2.\n");
	comparer(currentgame.numActions , 3); //starts at 1
	
	printf("Checking if the played card count is incremented.\n");
	comparer (currentgame.playedCardCount , 1); // This is the first played card, should be 1.
	
	return 0;
}
	