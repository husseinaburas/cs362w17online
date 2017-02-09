/**************************************************************************
Test SeaHag
**************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


//custom assert function
void assertTrue(int result, int expectedResult, int testNumber)
{
	if(result == expectedResult)
	{
		printf("Cardtest3-cardEffect - Sea Hag: test# %d PASS \n", testNumber);
	}

	else
	{
		printf("Cardtest3-cardEffect - Sea Hag: test# %d FAIL \n", testNumber);
	}
}
	
int main() 
{
    int i;
	int result1;
	int result2;
	int result3;
    int numPlayer = 3;
    struct gameState testGameState;
	int expectedResult;
	int expectedHandCount;
	int expectedDeckCount;
	int expectedDiscardCount;
	int testNumber = 0;
	int choice1, choice2, choice3;
	
	//set number of players
	testGameState.numPlayers = numPlayer;	
  
	//set whoseTurn
	testGameState.whoseTurn = 0;
	
	//set playedCardCount
	testGameState.playedCardCount = 0;

  	for (i = 0; i < numPlayer; i++)
    {
		//populate hand with sample cards equal to max handcount, score should 	equal 10
		testGameState.hand[i][0] = sea_hag;
		testGameState.hand[i][1] = estate;
		testGameState.hand[i][2] = estate;
		testGameState.hand[i][3] = estate;
		testGameState.hand[i][4] = estate;	
				
		testGameState.handCount[i] = 5;					//set handCount for number of sample cards
		
		testGameState.deck[i][0] = gardens;
	
		testGameState.deckCount[i] = 1;
		testGameState.discardCount[i] = 0;
	}
	

	cardEffect(sea_hag, choice1, choice2, choice3, &testGameState, 0, &choice3);
	
/****************************************************************/	
	//test that sea hag player no longer has sea hag in hand
	expectedResult = 0;
	
	testNumber++;
	if(testGameState.hand[0][0] == sea_hag)
	{
		result1 = 1; 
	}
		
	assertTrue(result1, expectedResult, testNumber);
	
/****************************************************************/	
	//test that sea hag player has only 4 cards in hand
	expectedResult = 4;
	
	testNumber++;
	result1 = testGameState.handCount[0];

	assertTrue(result1, expectedResult, testNumber);
	
	
/****************************************************************/	
	//test that sea hag player has sea hag in discard pile
	expectedResult = 1;
	result1 = 0;
	
	testNumber++;
	if(testGameState.discard[0][0] == sea_hag)
	{
		result1 = 1; 
	}	

	assertTrue(result1, expectedResult, testNumber);
	
	
	
	
/****************************************************************/	
	//test that sea hag player only has 1 card in discard pile
	expectedResult = 1;
	
	testNumber++;
	result1 = testGameState.discardCount[0];
	assertTrue(result1, expectedResult, testNumber);	
	

	
/****************************************************************/			
	//test that player has no curses in deck
	expectedResult = 0;
	result1 = 0;
	for (i = 0; i < testGameState.deck[0][testGameState.deckCount[0]-1]; i++)
	{
		if(testGameState.deck[0][i] == curse)
			result1 = 1; 
	}

	testNumber++;
	assertTrue(result1, expectedResult, testNumber);
		
		
/****************************************************************/	
	//test that every player besides sea hag player has curse as top card
	expectedResult = 1;
	
	for (i = 1; i < numPlayer; i++)
	{
		result1 = 0;
		testNumber++;
		if(testGameState.deck[i][testGameState.deckCount[i]-1] == curse)
			result1 = 1; 
		
		assertTrue(result1, expectedResult, testNumber);
	}

	

/****************************************************************/	
	//test that every player has deckCount of 1
	expectedResult = 1;
	
	for (i = 1; i < numPlayer; i++)
	{
		result1 = 0;
		testNumber++;
		result1 = testGameState.deckCount[i];
		
		assertTrue(result1, expectedResult, testNumber);
	}

/****************************************************************/	
	//test that every player has unchanged handcount of 5
	expectedResult = 5;
	
	for (i = 1; i < numPlayer; i++)
	{
		result1 = 0;
		testNumber++;
		result1 = testGameState.handCount[i];
		
		assertTrue(result1, expectedResult, testNumber);
	}		
	

/****************************************************************/	
	//test that every player has discard if 1
	expectedResult = 1;
	
	for (i = 1; i < numPlayer; i++)
	{
		result1 = 0;
		testNumber++;
		result1 = testGameState.discardCount[i];
		
		assertTrue(result1, expectedResult, testNumber);
	}	
	

/****************************************************************/	
	//test that every player besides sea hag player has gardens discarded
	expectedResult = 1;
	
	for (i = 1; i < numPlayer; i++)
	{
		result1 = 0;
		testNumber++;
		if(testGameState.discard[i][0] == gardens)
			result1 = 1; 
		
		assertTrue(result1, expectedResult, testNumber);
	}
	
	  
	return 0;
}