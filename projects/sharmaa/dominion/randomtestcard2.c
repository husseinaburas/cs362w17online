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
	int x, prehand, predis, predeck, preplay, preaction,  post, check;
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
	currentgame.hand[randoom_player][0]  = smithy; // force into players hand
	smithyx(&currentgame, randoom_player, 0); // play smithy
	
	printf("Testing smthyx: Checking for proper hand count.\n");
	comparer (currentgame.handCount[0] , (prehand + 2)); // should have 3 more, minus 1 discarded
	
	printf("Testing smithyx: Checking for proper deck decrement.\n");
	comparer (currentgame.deckCount[0] , predeck - 2);
	
	printf("Testing smithyx: Checking for discard pile increment.\n");
	comparer (currentgame.discardCount[0] , predis + 1);
	
	printf("Checking if the card in the discard pile is indeed a smithy.\n");
	comparer (currentgame.discard[randoom_player][predis+1] , smithy);
	
	printf("Checking if the played card count is incremented.\n");
	comparer (currentgame.playedCardCount , preplay + 1); // This is the first played card, should be 1.
	
	printf("-----Smithy testing complete.-----\n");

   return 0;

}