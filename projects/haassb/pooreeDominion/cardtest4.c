/**************************************************************************
Test playMine()
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
		printf("Cardtest4- playMine(): test# %d PASS \n", testNumber);
	}

	else
	{
		printf("Cardtest4- playMine(): test# %d FAIL \n", testNumber);
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
	int testNumber = 0;
	int choice1, choice2, choice3;
	int currentPlayer;
	
	//set number of players
	testGameState.numPlayers = numPlayer;	
  
	//set whoseTurn
	testGameState.whoseTurn = 0;
	
	//set playedCardCount
	testGameState.playedCardCount = 0;


  	for (i = 0; i < numPlayer; i++)
    {
		//populate hand with sample cards equal to max handcount, score should 	equal 10
		testGameState.hand[i][0] = mine;
		testGameState.hand[i][1] = copper;
		testGameState.hand[i][2] = silver;
		testGameState.hand[i][3] = gold;
		testGameState.hand[i][4] = estate;	
				
		testGameState.handCount[i] = 5;					//set handCount for number of sample cards
		
		testGameState.deckCount[i] = 0;
		testGameState.discardCount[i] = 0;
	}

/*********************************************************/
//test that if you try to trash a non treasure card an error is returned

	//try to trash estate and get silver
	int cardTrashedPos = 4;	
	int cardRequested = silver;
	int mineHandPos = 0; 
	
	expectedResult = -1;
	
	testNumber++;

	result1 = playMine(mineHandPos, currentPlayer, cardTrashedPos, cardRequested, &testGameState);

	assertTrue(result1, expectedResult, testNumber);



/*********************************************************/
//test that if bad hand position # is passed it returns error

	//try to trash handPos with no card stored in array
	cardTrashedPos = 4;	
	cardRequested = silver;
	mineHandPos = 0; 
	testGameState.hand[i][4] = -1;	
	expectedResult = -1;
	
	testNumber++;
	result1 = playMine(mineHandPos, currentPlayer, cardTrashedPos, cardRequested, &testGameState);


	assertTrue(result1, expectedResult, testNumber);
	testGameState.hand[i][4] = estate;			//reset card back to hand post test

/*********************************************************/
//test that it returns error if you try to mine card that costs >3 more than trashed card

	//try to trash copper to get gold
	cardTrashedPos = 1;	
	cardRequested = gold;
	mineHandPos = 0; 
	expectedResult = -1;
	
	testNumber++;
	result1 = playMine(mineHandPos, currentPlayer, cardTrashedPos, cardRequested, &testGameState);


	assertTrue(result1, expectedResult, testNumber);
	

/*********************************************************/
//test that after valid mine is played, treasure was successfully upgraded

	//try to trash copper to get gold
	cardTrashedPos = 1;	
	cardRequested = silver;
	mineHandPos = 0; 
	expectedResult = 0;
	
	//test that function returns 0
	testNumber++;
	result1 = playMine(mineHandPos, currentPlayer, cardTrashedPos, cardRequested, &testGameState);
	assertTrue(result1, expectedResult, testNumber);
	
/*********************************************************/
//test that hand now has 2 golds
	
	result1 = 0;
	expectedResult = 2;
	
	for(i = 0; i < testGameState.handCount[0]; i++)
	{
		if(testGameState.hand[0][i] == gold)
		{
			result1++;
		}
	}
	
	testNumber++;
	assertTrue(result1, expectedResult, testNumber);
	
/*********************************************************/
//test that hand now has 0 coppers
	
	result1 = 0;
	expectedResult = 0;
	
	for(i = 0; i < testGameState.handCount[0]; i++)
	{
		if(testGameState.hand[0][i] == copper)
		{
			result1++;
		}
	}
	
	testNumber++;
	assertTrue(result1, expectedResult, testNumber);
	
/*********************************************************/
//test that deck counts of all players remains unchanged
	
	expectedResult = 0;
	
	for(i = 0; i < numPlayer; i++)
	{		
		result1 = -1;
		testNumber++;
		result1 = testGameState.deckCount[i];
		assertTrue(result1, expectedResult, testNumber);	
	}
	

	
/*********************************************************/
//test that hand counts of  mine player is updated
	
	expectedResult = 4;
	
	testNumber++;
	result1 = testGameState.handCount[i];
	assertTrue(result1, expectedResult, testNumber);	
	
/*********************************************************/
//test that hand counts of  other player is unchanged
	
	expectedResult = 5;
	
	for(i = 1; i < numPlayer; i++)
	{		
		result1 = -1;
		testNumber++;
		result1 = testGameState.handCount[i];
		assertTrue(result1, expectedResult, testNumber);	
	}
	
/*********************************************************/
//test that discard count of  mine player is updated
	
	expectedResult = 1;
	
	testNumber++;
	result1 = testGameState.discardCount[i];
	assertTrue(result1, expectedResult, testNumber);
	
	
/*********************************************************/
//test that discard counts of all players remains unchanged
	
	expectedResult = 0;
	
	for(i = 1; i < numPlayer; i++)
	{		
		result1 = -1;
		testNumber++;
		result1 = testGameState.discardCount[i];
		assertTrue(result1, expectedResult, testNumber);	
	}
	
/*********************************************************/
//test that mine was discarded
	
	expectedResult = mine;
	
	testNumber++;
	result1 = testGameState.discard[0][0];
	assertTrue(result1, expectedResult, testNumber);
	


	return 0;
}