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
	}
	else 
	{
		printf("Test passed!\n");
	}
}


int main (int argc , char * argv[]) 
{
	srand(time(NULL));
	printf("-----CURRENT TEST: Random Village Card-----\n");
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
		int preactions = currentgame.numActions;
		int bonus = 0;
	
		cardEffect(village, 1,1,1, &currentgame, 0, bonus); // play the card
		
		printf("Testing if the player's hand count is the same. Iteration %d\n", n +1);
		comparer(currentgame.handCount[random_player] , prehand);
		
		printf("Testing if the player's actions is increased by 2. Iteration %d\n" , n + 1);
		comparer(currentgame.numActions , (preactions + 2)); //starts at 1
		
		printf("Checking if the played card count is incremented. Iteration %d\n" , n + 1);
		comparer (currentgame.playedCardCount , (preplayed + 1)); // This is the first played card, should be 1.
		printf("------------------------------------------------------------\n");
	}
	
	return 0;
}