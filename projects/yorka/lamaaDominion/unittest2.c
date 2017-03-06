/*
 * Unit Test 2: numHandCards()
 *
 * 
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int assertTest(int a, int b)
{
	if(a == b)
	{
		printf("Test Success.\n");
		return 1;
	}
	else
	{
		printf("Test Failed.\n");
		return 0;
	}
}
int main()
{

	int numPlayers = 2; //Number of players in the game
	int player1 = 0; //Player1's identifier index
	int player1HandBefore, player2HandBefore; //Coin before
	int player1HandAfter, player2HandAfter; //Coin after
	int handCount;

	int seedVal = 300;

	struct gameState gameStateTest;

  	int kingdomCardsList[10] = {adventurer, smithy, village, remodel, gardens, steward, tribute, great_hall, salvager, sea_hag};

 	printf("---- Unit Test 2: numHandCards() ----\n");
	
	// ---- Test 1: numHandCards properly gives correct amount of hands  ----
  	printf("---- Test 1: Check to see numHandCards() counts correct number of Player1's hand at start. ----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);
	
	gameStateTest.whoseTurn = 0; //Initializing player1's turn.
	
	handCount = numHandCards(&gameStateTest);

	printf("Player 1 Number of Hands = %d, Expected Number of Hands = %d \n", handCount, 5);
	assertTest(handCount,5);
	
	printf("\n");
	// ---- Test 2: numHandCards properly gives correct amount after gaining a card  ----
  	printf("---- Test 2: Check to see numHandCards() counts correct number of Player1's hand  after gaining a card----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);
	
	gameStateTest.whoseTurn = 0; //Initializing player1's turn.
	
	player1HandBefore = numHandCards(&gameStateTest);
	gainCard(copper, &gameStateTest, 2, player1);	
	
	player1HandAfter = numHandCards(&gameStateTest);

	printf("Player 1 Number of Hands = %d, Expected Number of Hands = %d \n", player1HandAfter, player1HandBefore + 1);
	assertTest(player1HandAfter, player1HandBefore + 1);
	
	printf("\n");
	// ---- Test 3: numHandCards properly gives correct amount after discarding a card  ----
  	printf("---- Test 3: Check to see numHandCards() counts correct number of Player1's hand  after discarding a card----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);
	
	gameStateTest.whoseTurn = 0; //Initializing player1's turn.
	
	player1HandBefore = numHandCards(&gameStateTest);
	discardCard(4, player1, &gameStateTest, 0);	
	
	player1HandAfter = numHandCards(&gameStateTest);

	printf("Player 1 Number of Hands = %d, Expected Number of Hands = %d \n", player1HandAfter, player1HandBefore -1);
	assertTest(player1HandAfter,player1HandBefore - 1);
	
	printf("\n");
	// ---- Test 4: numHandCards should leave 5 cards remaining in the deck at start with no buying/action  ----
  	printf("---- Test 4: If current player has 5 cards in hand, then the deck should have 5 cards. So we check that. ----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);
	
	gameStateTest.whoseTurn = 0; //Initializing player1's turn.
	
	int discardedHands = gameStateTest.deckCount[0];

	printf("Player 1 Number of Hands in Deck = %d, Expected Number of Hands in Deck = %d \n", discardedHands, 5);
	assertTest(discardedHands,5);	
	printf("\n");

	return 0;
}	
