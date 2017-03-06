/*
Card to test: Smithy
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

int main (int argc , char * argv[]) 
{
	printf("-----CURRENT TEST: Smithy Card-----\n");
	srand(time(NULL));
	struct gameState currentgame; // create new game and set num players
	int x, n, i;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall}; // set kingdom cards array
	int numplayers  = (rand() % 3) + 2;
	int randomseed = argv[1];
	initializeGame(numplayers, k, randomseed, &currentgame);

	
	for(n = 0; n < 2000; n++) // for loop determines how many tests to run
	{
		for(i=0; i < sizeof(struct gameState); i++)// loop to populate random struct
		{
			((char*)&currentgame)[i] = floor(Random() * 256);
		}
		
		//--------POPULATE ALL PROPER VARIABLES BEFORE PLAYING THE CARD---------
		

		int random_player = 0; // random player to play the card
		currentgame.whoseTurn = random_player;
		currentgame.deckCount[random_player] = floor(rand() % (MAX_DECK - 1)); // define variables to meet preconditions
		currentgame.discardCount[random_player] = floor(rand() % (MAX_DECK - 1));
		currentgame.handCount[random_player] = floor(rand() % (MAX_HAND - 1));
		currentgame.playedCardCount = floor(rand() % 25);
		currentgame.numActions = 1; // must be 1 to start every turn
		// currentgame.hand[random_player][0]  = adventurer; // force into players hand

		int prehand = currentgame.handCount[random_player]; 
		int predeck = currentgame.deckCount[random_player];
		int preplayed = currentgame.playedCardCount;
		int prediscard = currentgame.discardCount[random_player];
		int preactions = currentgame.numActions;
		int bonus = 0;

	
	currentgame.whoseTurn = random_player;
	currentgame.hand[random_player][0]  = smithy; // force into players hand
	smithyx(&currentgame, random_player, 0); // play smithy
	
	printf("Testing smthyx: Checking for proper hand count.\n");
	comparer (currentgame.handCount[random_player] , (prehand + 2)); // should have 3 more, minus 1 discarded
	
	printf("Testing smithyx: Checking for proper deck decrement.\n");
	comparer (currentgame.deckCount[random_player] , predeck - 2);
	
	printf("Testing smithyx: Checking for discard pile increment.\n");
	comparer (currentgame.discardCount[random_player] , prediscard + 1);
	
	printf("Checking if the played card count is incremented.\n");
	comparer (currentgame.playedCardCount , preplayed + 1); // This is the first played card, should be 1.
	
	printf("----------------------------------------------------------\n");
	
	}

   return 0;

}