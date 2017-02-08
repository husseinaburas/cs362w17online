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

int main () 
{
	printf("-----CURRENT TEST: Smithy Card-----\n");
	struct gameState currentgame; // create new game and set num players
	int numplayers = 2;
	int x, pre, post, check;
	int randomseed = 777;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall}; // set kingdom cards array
	memset(&currentgame, 23, sizeof(struct gameState));
	int gameinit = initializeGame(numplayers, k, randomseed, &currentgame); // initialize the game
	// Each player now has 5 cards in their hands, either estates or coppers. We force once of the cards
	// to be a smithy.
	currentgame.hand[0][0] = smithy; 

	//need to check if 3 cards were drawn and smithty card is properly discarded, and deck is decremented
	// Since i replaced an initial card with smithy, we still have 5 in the hand and 5 in the deck.
	smithyx(&currentgame, 0, 0); // play smithy
	
	printf("Testing smthyx: Checking for proper hand count.\n");
	comparer (currentgame.handCount[0] , 7); // should have 3 more, minus 1 discarded
	
	printf("Testing smithyx: Checking for proper deck decrement.\n");
	comparer (currentgame.deckCount[0] , 2);
	
	printf("Testing smithyx: Checking for discard pile increment.\n");
	comparer (currentgame.discardCount[0] , 1);
	
	printf("Checking if the card in the discard pile is indeed a smithy.\n");
	comparer (currentgame.discard[0][0] , smithy);
	
	printf("Checking if the played card count is incremented.\n");
	comparer (currentgame.playedCardCount , 1); // This is the first played card, should be 1.
	
	printf("-----Smithy testing complete.-----\n");

   return 0;

}