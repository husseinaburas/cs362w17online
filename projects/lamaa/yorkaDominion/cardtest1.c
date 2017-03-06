/*
 * Card Test 1: Smithy
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
	int player2 = 1;
	int begHandCount;

	int seedVal = 120;

	struct gameState gameStateTest, gameStateTest2;

  	int kingdomCardsList[10] = {smithy, adventurer, village, remodel, gardens, steward, tribute, great_hall, salvager, council_room};

 	printf("---- Card Test 1: Smithy ----\n");
	
	// ---- Test 1: Player receives exact 3 cards after playing Smithy  ----
  	printf("---- Test 1: Smithy should allow to draw exact 3 cards to Player1. ----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);
	
	begHandCount = gameStateTest.handCount[player1];	
	gameStateTest.whoseTurn = player1;
	gameStateTest.coins = 20; //make sure we have enough coins to buy 
	
	gameStateTest.hand[player1][0] = smithy;

	cardEffect(smithy,0,0,0,&gameStateTest,0,0);
	
	printf("Hand count = %d, expected = %d \n", gameStateTest.handCount[player1], begHandCount + 3);
	assertTest(gameStateTest.handCount[player1],begHandCount+3);
	
	printf("\n");	
	// ---- Test 2: 3 cards should come from Player1's pile after using Smithy  ----
  	printf("---- Test 2: 3 drawn cards should come from Player's deck pile after using Smithy. ----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);
	
	int begDeckCount = gameStateTest.deckCount[player1];	
	gameStateTest.whoseTurn = player1;
	gameStateTest.coins = 20; //make sure we have enough coins to buy 
	
	gameStateTest.hand[player1][0] = smithy;

	cardEffect(smithy,0,0,0,&gameStateTest,0,0);
	
	printf("Deck count = %d, expected = %d \n", gameStateTest.deckCount[player1], begDeckCount - 3);
	assertTest(gameStateTest.deckCount[player1],begDeckCount-3);

	printf("\n");	
	// ---- Test 3: No state change should occur for other players.  ----
  	printf("---- Test 3: No state change(hand count) should occur for Player2,. ----\n");
	int handCountPlayer2Before, handCountPlayer2After;

	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);
		
	handCountPlayer2Before = gameStateTest.handCount[player2];
	gameStateTest.coins = 20; //make sure we have enough coins to buy 
	
	gameStateTest.hand[player1][0] = smithy;
	
	cardEffect(smithy,0,0,0,&gameStateTest,0,0);

	handCountPlayer2After = gameStateTest.handCount[player2];
	
	printf("Player 1 uses smithy and no hand count change should occur in player2\n");
	printf("Player 2 hand count before Player 1 uses Smithy= %d \n Player 2 hand count after Player 1 uses Smithy = %d \n", handCountPlayer2Before, handCountPlayer2After); 
	assertTest(handCountPlayer2Before, handCountPlayer2After);
	printf("\n");
	
	// ---- Test 4: No state change should occur to the victory card piles and kingdom card piles---
  	printf("---- Test 4: No state change should occur to victory card piles and kingdom card piles ----\n");

	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);
		
	gameStateTest.coins = 20; //make sure we have enough coins to buy 
	
	gameStateTest.hand[player1][0] = smithy;
	
	int kingDCardsBefore, kingDCardsAfter, estateBefore, estateAfter, duchyBefore, duchyAfter, provBefore, provAfter;
    	int i;

      	for(i = 1; i<10;i++)
	{	
		kingDCardsBefore += gameStateTest.supplyCount[kingdomCardsList[i]];
   	}
	
	estateBefore = gameStateTest.supplyCount[estate];
	duchyBefore = gameStateTest.supplyCount[estate];
	provBefore = gameStateTest.supplyCount[province];

	cardEffect(smithy,0,0,0,&gameStateTest,0,0);

	for(i= 1; i<10;i++)
        {
               	kingDCardsAfter += gameStateTest.supplyCount[kingdomCardsList[i]];
        }

	estateAfter = gameStateTest.supplyCount[estate];
	duchyAfter = gameStateTest.supplyCount[estate];
	provAfter = gameStateTest.supplyCount[province];

	printf("Amount of Kingdom cards before using Smithy = %d, after using Smithy = %d \n", kingDCardsBefore, kingDCardsAfter);
	assertTest(kingDCardsBefore, kingDCardsAfter);
	printf("Amount of Estate cards before using Smithy = %d, after using Smithy = %d \n", estateBefore, estateAfter);
	assertTest(estateBefore, estateAfter);
	printf("Amount of Duchy cards before using Smithy = %d, after using Smithy = %d \n", duchyBefore, duchyAfter);
	assertTest(duchyBefore, duchyAfter);
	printf("Amount of Province cards before using Smithy = %d, after using Smithy = %d \n", provBefore, provAfter);
	assertTest(provBefore, provAfter);
	printf("\n");	

	return 0;
}
