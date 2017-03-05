/*
 * Unit Test 4: buyCard()
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
	//int player1 = 0; //Player1's identifier index
	int count;
	int seedVal = 150;

	struct gameState gameStateTest;

  	int kingdomCardsList[10] = {adventurer, smithy, village, remodel, gardens, steward, tribute, great_hall, salvager, sea_hag};

 	printf("---- Unit Test 4: buyCard() ----\n");
	
	// ---- Test 1: buyCard() buys 1 village and reduces village supply count  ----
  	printf("---- Test 1: Check 1 Buy - buyCard() buys 1 Village card and decreases supply count to 9. ----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);

 	gameStateTest.coins = 20; //Gives player 20 coins be able to afford.
	
	buyCard(village, &gameStateTest);

	count = gameStateTest.supplyCount[village];	
	printf("Village card supply count: %d Expected supply count: %d \n",count, 9);
	assertTest(count,9);
	printf("\n");

	// ---- Test 2: buyCard() buys 2 smithy and reduces smithy supply count  ----
  	printf("---- Test 2: Check 2 Buy - buyCard() buys 2 Smithy card and decreases supply count to 8. ----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);

 	gameStateTest.coins = 20; //Gives player 20 coins be able to afford.
	gameStateTest.numBuys = 2; //Increases number buys to 2
	
	buyCard(smithy, &gameStateTest);
	buyCard(smithy, &gameStateTest);

	count = gameStateTest.supplyCount[smithy];	
	printf("Smithy card supply count: %d Expected supply count: %d \n",count, 8);
	assertTest(count,8);
	printf("\n");

	// ---- Test 3: buyCard() buys 2 adventurer and checks if supply count for kingdom and victory card changed.  ----
  	printf("---- Test 3: Check if buying 2 adventurer card affects remaining kingdom cards(excluding adventurer). ----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);

 	gameStateTest.coins = 20; //Gives player 20 coins be able to afford.

	int kingDCardsBefore, kingDCardsAfter;
	int i;

	for(i = 1; i<10;i++)
	{
		kingDCardsBefore += gameStateTest.supplyCount[kingdomCardsList[i]];
	}

	buyCard(adventurer, &gameStateTest);
	buyCard(adventurer, &gameStateTest);

	for(i = 1; i<10;i++)
	{
		kingDCardsAfter += gameStateTest.supplyCount[kingdomCardsList[i]];
	}
	
	printf("Kingdom card supply count Before: %d After: %d \n",kingDCardsBefore, kingDCardsAfter);
	assertTest(kingDCardsBefore, kingDCardsAfter);
	printf("\n");
	
	return 0;
}
