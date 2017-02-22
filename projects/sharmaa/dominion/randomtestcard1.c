/*
Card to test:  village
struct gameState {
  int numPlayers; //number of players
  int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
  int embargoTokens[treasure_map+1];
  int outpostPlayed;
  int outpostTurn;
  int whoseTurn;
  int phase;
  int numActions; /* Starts at 1 each turn 
  int coins; /* Use as you see fit! 
  int numBuys; /* Starts at 1 each turn 
  int hand[MAX_PLAYERS][MAX_HAND];
  int handCount[MAX_PLAYERS];
  int deck[MAX_PLAYERS][MAX_DECK];
  int deckCount[MAX_PLAYERS];
  int discard[MAX_PLAYERS][MAX_DECK];
  int discardCount[MAX_PLAYERS];
  int playedCards[MAX_DECK];
  int playedCardCount;
};
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
	srand(time(NULL));
	int i , j;
	printf("-----CURRENT TEST: Village Card -----\n");
	struct gameState currentgame; // create new game and set num players

	int x, pre1 , pre2, pre3, post, check;
	int randoomseed = 777;
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
		pre1 = rando;
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
		for (x = 0; x < rando; x++)
		{
			currentgame.discard[i][x] = rand() % 20;
		}
	}
	
	currentgame.playedCardCount = rand() % 5;  // randoomize played card pile
	pre3 = currentgame.playedCardCount;
	for (i = 0; i < currentgame.playedCardCount; i++)
	{
		currentgame.playedCards[i] = rand() % 20;
	} 

	
	currentgame.whoseTurn = randoom_player;
	currentgame.hand[randoom_player][0]  = village; // force into players hand
	
	int * bonus = 0;
	cardEffect(village, 1,1,1, &currentgame, 0, bonus); // play the card
	
	printf("Testing if the player's hand count is the same.\n");
	comparer(currentgame.handCount[randoom_player] , pre1);
	
	printf("Testing if the player's actions is increased by 2.\n");
	comparer(currentgame.numActions , (pre2 + 2)); //starts at 1
	
	printf("Checking if the played card count is incremented.\n");
	comparer (currentgame.playedCardCount , (pre3 +1)); // This is the first played card, should be 1.
	}
	
	return 0;
}