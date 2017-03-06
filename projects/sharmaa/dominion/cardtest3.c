/*
Card to test: council_room

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
	printf("-----CURRENT TEST: Council Room Card-----\n");
	struct gameState currentgame; // create new game and set num players
	int numplayers = 2;
	int x, pre, post, check;
	int randomseed = 777;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall}; // set kingdom cards array
	memset(&currentgame, 23, sizeof(struct gameState));
	int gameinit = initializeGame(numplayers, k, randomseed, &currentgame); // initialize the game
	currentgame.hand[0][0] = council_room; // force card into hand
	council_roomx(&currentgame, 0, 0);
	
	printf("Testing if 4 cards were drawn by the player.\n"); // nets in increase of 3
	comparer(currentgame.handCount[0] , 9);
	
	printf("Testing if deck is decremented by 4\n");
	comparer(currentgame.deckCount[0] , 1); // was 5 before
	
	printf("Testing if the player has their buys incremented.\n");
	comparer(currentgame.numBuys , 2); //starts at 1 every turn, so should be 2 now.
	
	printf("Testing if the other player draws a card.\n");
	comparer(currentgame.handCount[1] , 6);
	
	printf("Testing if other player's deck is decremented.\n");
	comparer(currentgame.deckCount[1], 4);
	
	printf("Checking if the played card count is incremented.\n");
	comparer (currentgame.playedCardCount , 1); // This is the first played card, should be 1.
	
	return 0;
}
	