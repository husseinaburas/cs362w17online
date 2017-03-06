/**************************************************************************
Test playSmithy()
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
		printf("Cardtest1- playSmithy(): test# %d PASS \n", testNumber);
	}

	else
	{
		printf("Cardtest1- playSmithy(): test# %d FAIL \n", testNumber);
	}
}
	
int main() 
{
    int i;
	int result1;
	int result2;
	int result3;
    int numPlayer = 2;
    struct gameState testGameState;
	int expectedResult;
	int expectedHandCount;
	int expectedDeckCount;
	int expectedDiscardCount;
	int testNumber = 0;
	int smithyPosition = 0;
	
	//set number of players
	testGameState.numPlayers = numPlayer;
  


	//set player 1 starting counts
	 testGameState.deckCount[0] = 0;
	 testGameState.handCount[0] = 0;
	 testGameState.discardCount[0] = 0;
	
	
	//set whoseTurn
	testGameState.whoseTurn = 0;
	
	//set playedCardCount
	testGameState.playedCardCount = 0;	


/************************************************************/
//test that proper numbeer of cards are drawn and discarded
	
	//populate hand with sample cards and smithy in position 0
	testGameState.hand[0][0] = smithy;
	testGameState.hand[0][1] = estate;
	testGameState.hand[0][2] = duchy;
	testGameState.hand[0][3] = province;
	testGameState.hand[0][4] = great_hall;
	testGameState.handCount[0] = 5;

	//populate deck with 3 curse cards
	testGameState.deck[0][0] = curse;
	testGameState.deck[0][1] = curse;
	testGameState.deck[0][2] = curse;
	testGameState.deck[0][3] = curse;
	testGameState.deckCount[0] = 4;	

	testNumber++;
	expectedHandCount = 7;
	expectedDeckCount = 1;
	expectedDiscardCount = 1;
	
	playSmithy(&testGameState, smithyPosition);
	
	result1 = testGameState.handCount[0];
	result2 = testGameState.deckCount[0];
	result3 = testGameState.discardCount[0];
	assertTrue(expectedHandCount, result1, testNumber);
	
	testNumber++;
	assertTrue(expectedDeckCount, result2, testNumber);	
	
	testNumber++;
	assertTrue(expectedDiscardCount, result3, testNumber);		
	
	
		
		
/************************************************************/
//test that smithy card is removed from hand
	
	//if smithy still remains in hand 
	
	result1 = 0;
	
	for(i = 0; i < testGameState.handCount[0]; i++)
	{
		if(testGameState.hand[0][i] == smithy)
		{
			//set flag
			result1 = 1;
		}
	}

	
	expectedResult = 0;
	testNumber++;
	
	assertTrue(result1, expectedResult, testNumber);
	
	
/************************************************************/
//test that 3 curse cards from deck made it into hand	
		
		
	//count curse cards 
	result1 = 0;
	
	for(i = 0; i < testGameState.handCount[0]; i++)
	{
		if(testGameState.hand[0][i] == curse)
		{
			//increase counter
			result1++;
		}
	}

	
	expectedResult = 3;
	testNumber++;
	
	assertTrue(result1, expectedResult, testNumber);		
		
	return 0;
}		
		
			
		
		
		
		
		
		
		
		
		
		
		
		