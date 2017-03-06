/*
Card to test: Adventurer
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
	printf("-----CURRENT TEST: Random Adventurer Card-----\n");
	struct gameState currentgame; // create new game and set num players
	int x, n, i, drawnCard, cardDrawn = 0;
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
		// currentgame.hand[random_player][0]  = adventurer; // force into players hand

		int prehand = currentgame.handCount[random_player]; 
		int predeck = currentgame.deckCount[random_player];
		int prediscard = currentgame.discardCount[random_player];
		int preplayed = currentgame.playedCardCount;
		
		int drawntreasure, cardsDrawn, drawnCard = 0;
		
		for(x = currentgame.deckCount[random_player]; x >= 0; x--)
		{
			if (drawntreasure >= 2)
			{
				break;
			}
			drawnCard = currentgame.deck[random_player][x - 1];
			if (drawnCard == copper || drawnCard == silver || drawnCard == gold)
			{
				drawntreasure++;
				cardsDrawn++;
			}
			else
			{
				cardsDrawn++;
			}
		}
		
		if (drawntreasure < 2) // if there arent enough in the deck
		{
			continue;
		}
		
		int temphand[MAX_HAND];
		
		adventurerx(&currentgame, random_player, temphand,  cardDrawn); // call it
		
		//Test hand count, should be 2 more
		printf("Testing if hand count is properly increased. Iteration %d.\n" , n + 1);
		comparer(currentgame.handCount[random_player] , prehand + 2);
		
		// Test that these new cards are treasures
		printf("Testing if new cards in hand are treasures. Iteration %d.\n" , n + 1);
		int card1 = currentgame.hand[random_player][prehand + 1];
		int card2 = currentgame.hand[random_player][prehand];
		int check = 0;
		if (!(card1 == copper || card1 == silver || card1 == gold))
		{
			printf("Test failed! One of the kept cards is not a treasure card!\n");
			check = 1;
		}
		if (!(card2 == copper || card2 == silver || card2 == gold))
		{
			printf("Test failed! One of the kept cards is not a treasure card!\n");
			check = 1;
		}
		if (check == 0)
		{
			printf("Test passed! All drawn cards are indeed treasures!\n");
		}
		
		// Test to see if the discard pile was incremented by cardsDrawn - 2
		printf("Testing if discard pile is properly incremented. Iteration %d.\n" , n + 1);
		comparer(currentgame.discardCount[0] , prediscard + cardsDrawn - 2); // was empty before so we should have 2
		
		//Test to see if the played card pile is incremented
		printf("Checking if the played card count is incremented. Iteration %d.\n" , n + 1);
		comparer (preplayed + 1 , currentgame.playedCardCount); // This is the first played card, should have 1 more

		// Test to see if the discarded cards are not treasures
		printf("Testing is the discarded cards are NOT treasures. Iteration %d.\n" , n + 1);
		int t, checker;
		for(t = 1; t < cardsDrawn - 2; t++)
		{
			int currentcard = currentgame.discard[random_player][currentgame.discardCount[random_player] - t];
			if (currentcard == copper || currentcard == silver || currentcard == gold)
			{
				printf("Test failed! Treasure cards were discarded!\n");
			}
			else
			{
				checker = 1;
			}
		}
		if (checker == 1)
		{
			printf("Test passed! No treasure cards were discarded!\n");
			
		}
		// Make sure deck count is decremented by 4
		printf("Checking if deck count is decremented properly. Iteration %d. \n" , n + 1);
		comparer(currentgame.deckCount[random_player] , predeck - cardsDrawn); // was 5 before
		printf("-------------------------------------------------------------------\n");
	}
	return 0;
}