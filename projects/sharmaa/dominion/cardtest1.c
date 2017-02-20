/*
Card to test: Adventurer
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
	printf("-----CURRENT TEST: Adventurer Card-----\n");
	struct gameState currentgame; // create new game and set num players
	int numplayers = 2;
	int x, cardDrawn;
	int randomseed = 777;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall}; // set kingdom cards array
	memset(&currentgame, 23, sizeof(struct gameState));
	int gameinit = initializeGame(numplayers, k, randomseed, &currentgame); // initialize the game
	currentgame.hand[0][0] = adventurer; // force adventurer into player's hand
	int old = currentgame.playedCardCount;
	//Control the deck to predict behavior i.e manipulate the deck 
	currentgame.deck[0][3] = gold;
	currentgame.deck[0][2] = smithy;
	currentgame.deck[0][1] = silver;
	currentgame.deck[0][0] = estate; // make sure the first card is NOT a treasure.
	
	// Now we know there should be 2 discards during the adventurer call.
	
	int temphand[MAX_HAND];
	adventurerx(&currentgame, 0, temphand,  cardDrawn);
	
	//Test hand count, should be 2 more
	printf("Testing if hand count is properly increased.\n");
	comparer(currentgame.handCount[0] , 7);
	
	// Test that these new cards are treasures
	printf("Testing if new cards in hand are treasures.\n");
	comparer(currentgame.hand[0][6] , 5);
	comparer(currentgame.hand[0][5] , 6);
	
	// Test to see if the discard pile was incremented by 2
	printf("Testing if discard pile is properly incremented.\n");
	comparer(currentgame.discardCount[0] , 2); // was empty before so we should have 2
	
	//Test to see if the played card pile is incremented
	printf("Checking if the played card count is incremented.\n");
	comparer (old + 1 , currentgame.playedCardCount); // This is the first played card, should have 1 more

	// Test to see if the discarded cards are not treasures
	printf("Testing is the discarded cards are NOT treasures.\n");
	int t;
	for(t = 0; t < 2; t++)
	{
		if ((currentgame.discard[0][t] > 4) && (currentgame.discard[0][t] < 6))
		{
			printf("Test failed! Cards in discard pile are treasure.\n");
		}
		else 
		{
			printf("Test passed! Cards in discard pile are not treasure.\n");
		}
	}

	// Make sure deck count is decremented by 4
	printf("Checking if deck count is decremented by 4.\n");
	comparer(currentgame.deckCount[0] , 1); // was 5 before
	
	return 0;
}