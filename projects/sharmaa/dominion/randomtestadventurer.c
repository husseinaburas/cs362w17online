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
	
	for(j = 0; j < 200; j++) // major loop to test new game states every time
	{
	int players[3] = {2,3,4};
	int numplayers  = players[rand() % 3]; 
	memset(&currentgame, 23, sizeof(struct gameState));
	int gameinit = initializeGame(numplayers, k, randoomseed, &currentgame); // initialize the game
	// randoomize the game state so that we are at some randoom point in the game rather than the beginning

	int randoom_player =  players[rand() % 3]; // randoom player to play the card
	
	
 	currentgame.numActions = rand() % 4 + 1;
	pre2 = currentgame.numActions;
	currentgame.numBuys = rand() % 3 + 1;
	
	for (i = 0; i < currentgame.numPlayers; i ++) // randoomize everyones hands
	{
		int x;
		int rando =  rand() % 8;
		currentgame.handCount[i] = rando;
		prehand = rando;
		for (x = 0; x < rando; x++)
		{
			currentgame.hand[i][x] = rand() % 20;
		}
	}
	
	for (i = 0; i < currentgame.numPlayers; i ++) // randoomize everyones decks
	{
		int x;
		int rando =  rand() %  75;
		currentgame.deckCount[i] = rando;
		predeck = rando;
		for (x = 0; x < rando; x++)
		{
			currentgame.deck[i][x] = rand() % 20;
		}
	}
	
	for (i = 0; i < currentgame.numPlayers; i ++) // randoomize everyones discards
	{
		int x;
		int rando =  rand() % 75;
		currentgame.discardCount[i] = rando;
		predis = rando;
		for (x = 0; x < rando; x++)
		{
			currentgame.discard[i][x] = rand() % 20;
		}
	}
	
	currentgame.playedCardCount = rand() % 5;  // randoomize played card pile
	preplay = currentgame.playedCardCount;
	for (i = 0; i < currentgame.playedCardCount; i++)
	{
		currentgame.playedCards[i] = rand() % 20;
	} 

	
	currentgame.whoseTurn = randoom_player;
	currentgame.hand[randoom_player][0]  = adventurer; // force into players hand
	
	// Now we know there should be 2 discards during the adventurer call.
	
	int temphand[MAX_HAND];
	adventurerx(&currentgame, randoom_player, temphand,  cardDrawn);
	
	//Test hand count, should be 2 more
	printf("Testing if hand count is properly increased.\n");
	comparer(currentgame.handCount[0] , prehand + 2);
	
	// Test that these new cards are treasures
	printf("Testing if new cards in hand are treasures.\n");
	comparer(currentgame.hand[randoom_player][prehand + 2] , 5);
	comparer(currentgame.hand[randoom_player][prehand + 1] , 6);
	
	// Test to see if the discard pile was incremented by 2
	printf("Testing if discard pile is properly incremented.\n");
	comparer(currentgame.discardCount[0] , predis + 2); // was empty before so we should have 2
	
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