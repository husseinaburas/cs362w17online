/*
 * Card Test 2: Adventurer
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
	int begHandCount, decHandCount,tresHandCount, tresHandCountFin, playedHandCount;
	int p2HandCount;

	int seedVal = 120;

	struct gameState gameStateTest, gameStateTest2;

  	int kingdomCardsList[10] = {adventurer, smithy, village, remodel, gardens, steward, tribute, great_hall, salvager, council_room};

 	printf("---- Card Test 2: Adventurer ----\n");
	

	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);
	
	begHandCount = gameStateTest.handCount[player1];	
	decHandCount = gameStateTest.deckCount[player1];
	tresHandCount = gameStateTest.supplyCount[copper]+gameStateTest.supplyCount[silver]+gameStateTest.supplyCount[gold];
	playedHandCount = gameStateTest.playedCardCount;
	p2HandCount = gameStateTest.handCount[1];
	
	gameStateTest.hand[player1][0] = adventurer;

	cardEffect(adventurer,0,0,0,&gameStateTest,0,0);
	
	// ---- Test 1: 2 Treasure Cards should be added to your hand.  ----
  	printf("---- Test 1: 2 Treasure Cards should be added to your hand. ----\n");
	
	printf("Hand count before adventurer card used = %d\n", begHandCount);	
	printf("Hand count after= %d, expected = %d \n", gameStateTest.handCount[player1], begHandCount + 2);
	assertTest(gameStateTest.handCount[player1],begHandCount+2);
		
	printf("\n");

	// ---- Test 2: Your deck pile should decrease by at least 2----	
	printf("---- Test2: Your deck pile should decrease by at least  2 -----\n");
	
	printf("Deck hand count before adventurer card used = %d \n", decHandCount);
	printf("Deck hand count after= %d, expected less than %d \n", gameStateTest.deckCount[player1], decHandCount-1);
	if((decHandCount - gameStateTest.deckCount[player1]) >=  2)
	{
		printf("Test Success.\n");
	}	
	else
	{
		printf("Test Failed.\n");
	}	
	printf("\n");

	// ---- Test 3: Played hand count should be 1 ----
	printf("---- Test3: Played card count should increase by 1 ---- \n");
	
	printf("Played hand count before adventurer card used = %d \n", playedHandCount);
	printf("Played hand count after= %d, expected = %d \n", gameStateTest.playedCardCount, playedHandCount+1);
	if(playedHandCount - gameStateTest.playedCardCount ==  1)
	{
		printf("Test Success.\n");
	}	
	else
	{
		printf("Test Failed.\n");
	}	
	printf("\n");

	// ---- Test 4: Player 2's hand count shouldnt be affected ----
	printf("---- Test4: Player 2's hand count shouldn't be affected ---- \n");
	
	printf("Player 2 hand count before adventurer card used = %d \n", p2HandCount);
	printf("Player 2 hand count after= %d, expected = %d \n", gameStateTest.handCount[1], p2HandCount);
	assertTest(gameStateTest.handCount[1],p2HandCount);
	printf("\n");

	return 0;

}
