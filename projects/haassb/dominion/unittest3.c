/**************************************************************************
Test fullDeckCount()
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
		printf("Unittest3- fullDeckCount(): test# %d PASS \n", testNumber);
	}

	else
	{
		printf("Unittest3- fullDeckCount(): test# %d FAIL \n", testNumber);
	}
}
	
int main() 
{
    int i;
	int temp;
    int numPlayer = 2;
    struct gameState testGameState;
	int expectedResult;
	int testNumber = 0;

	
	//set number of players
	testGameState.numPlayers = numPlayer;
  
	//set player card counts to 0
	for (i = 0; i < numPlayer; i++)
    {
      testGameState.deckCount[i] = 0;
      testGameState.handCount[i] = 0;
      testGameState.discardCount[i] = 0;
	}	
	
/************************************************/
//test isolated hand count
	for (i = 0; i < numPlayer; i++)
    {
		//populate hand with sample cards 
		testGameState.hand[i][0] = curse;
		testGameState.hand[i][1] = estate;
		testGameState.hand[i][2] = duchy;
		testGameState.hand[i][3] = province;
		testGameState.hand[i][4] = great_hall;	
				
		testGameState.handCount[i] = 5;					//set handCount for number of sample cards
	}
	
	for(i=0; i < numPlayer; i++)
	{
		testNumber++;
		temp = fullDeckCount(i, curse, &testGameState);
		expectedResult = 1;
		assertTrue(temp, expectedResult, testNumber);
	}
	
	//reset player card counts to 0
	for (i = 0; i < numPlayer; i++)
    {
      testGameState.deckCount[i] = 0;
      testGameState.handCount[i] = 0;
      testGameState.discardCount[i] = 0;
	}
	
	 //clear hand, deck, and discard
	memset(testGameState.deck, NULL, sizeof(testGameState.deck));
	memset(testGameState.hand, NULL, sizeof(testGameState.hand));
	memset(testGameState.discard, NULL, sizeof(testGameState.discard));
	
/***********************************************/	
//test isolated deck count
	for (i = 0; i < numPlayer; i++)
    {
		//populate deck with sample cards 
		testGameState.deck[i][0] = curse;
		testGameState.deck[i][1] = estate;
		testGameState.deck[i][2] = duchy;
		testGameState.deck[i][3] = province;
		testGameState.deck[i][4] = great_hall;	
				
		testGameState.deckCount[i] = 5;					//set handCount for number of sample cards
	}
	
	for(i=0; i < numPlayer; i++)
	{
		testNumber++;
		temp = fullDeckCount(i, estate, &testGameState);
		expectedResult = 1;
		assertTrue(temp, expectedResult, testNumber);
	}
	
	//reset player card counts to 0
	for (i = 0; i < numPlayer; i++)
    {
      testGameState.deckCount[i] = 0;
      testGameState.handCount[i] = 0;
      testGameState.discardCount[i] = 0;
	}
	
	 //clear hand, deck, and discard
	memset(testGameState.deck, NULL, sizeof(testGameState.deck));
	memset(testGameState.hand, NULL, sizeof(testGameState.hand));
	memset(testGameState.discard, NULL, sizeof(testGameState.discard));
	
/***********************************************/
//test isolated discard count
	for (i = 0; i < numPlayer; i++)
    {
		//populate discard with sample cards 
		testGameState.discard[i][0] = curse;
		testGameState.discard[i][1] = estate;
		testGameState.discard[i][2] = duchy;
		testGameState.discard[i][3] = province;
		testGameState.discard[i][4] = great_hall;	
				
		testGameState.discardCount[i] = 5;					//set handCount for number of sample cards
	}
	
	for(i=0; i < numPlayer; i++)
	{
		testNumber++;
		temp = fullDeckCount(i, duchy, &testGameState);
		expectedResult = 1;
		assertTrue(temp, expectedResult, testNumber);
	}	
	
	 //clear hand, deck, and discard
	memset(testGameState.deck, NULL, sizeof(testGameState.deck));
	memset(testGameState.hand, NULL, sizeof(testGameState.hand));
	memset(testGameState.discard, NULL, sizeof(testGameState.discard));
	

/***********************************************/
//test repeat cards
	for (i = 0; i < numPlayer; i++)
    {
		//populate discard with sample cards 
		testGameState.discard[i][0] = province;
		testGameState.discard[i][1] = province;
		testGameState.discard[i][2] = province;
		testGameState.discard[i][3] = province;
		testGameState.discard[i][4] = province;	
				
		testGameState.discardCount[i] = 5;					//set handCount for number of sample cards
	}
	
	for(i=0; i < numPlayer; i++)
	{
		testNumber++;
		temp = fullDeckCount(i, province, &testGameState);
		expectedResult = 5;
		assertTrue(temp, expectedResult, testNumber);
	}	
	
	 //clear hand, deck, and discard
	memset(testGameState.deck, NULL, sizeof(testGameState.deck));
	memset(testGameState.hand, NULL, sizeof(testGameState.hand));
	memset(testGameState.discard, NULL, sizeof(testGameState.discard));
	

/***********************************************/
//test distribution of cards between 3 card sources
	for (i = 0; i < numPlayer; i++)
    {
		//populate deck with sample cards 
		testGameState.deck[i][0] = copper;
		testGameState.deck[i][1] = silver;
		testGameState.deck[i][2] = duchy;
		testGameState.deck[i][3] = province;
		testGameState.deck[i][4] = great_hall;	
				
		testGameState.deckCount[i] = 5;					//set handCount for number of sample cards
		
		//populate hand with sample cards 
		testGameState.hand[i][0] = copper;
		testGameState.hand[i][1] = silver;
		testGameState.hand[i][2] = duchy;
		testGameState.hand[i][3] = province;
		testGameState.hand[i][4] = great_hall;	
				
		testGameState.handCount[i] = 5;					//set handCount for number of sample cards
		
		//populate discard with sample cards 
		testGameState.discard[i][0] = copper;
		testGameState.discard[i][1] = silver;
		testGameState.discard[i][2] = duchy;
		testGameState.discard[i][3] = province;
		testGameState.discard[i][4] = great_hall;	
				
		testGameState.discardCount[i] = 5;					//set handCount for number of sample cards
	}
	
	for(i=0; i < numPlayer; i++)
	{
		testNumber++;
		temp = fullDeckCount(i, copper, &testGameState);
		expectedResult = 3;
		assertTrue(temp, expectedResult, testNumber);
		
		testNumber++;
		temp = fullDeckCount(i, silver, &testGameState);
		expectedResult = 3;
		assertTrue(temp, expectedResult, testNumber);
		
		testNumber++;
		temp = fullDeckCount(i, duchy, &testGameState);
		expectedResult = 3;
		assertTrue(temp, expectedResult, testNumber);
		
		testNumber++;
		temp = fullDeckCount(i, province, &testGameState);
		expectedResult = 3;
		assertTrue(temp, expectedResult, testNumber);
		
		testNumber++;
		temp = fullDeckCount(i, great_hall, &testGameState);
		expectedResult = 3;
		assertTrue(temp, expectedResult, testNumber);
	}	
	
	 //clear hand, deck, and discard
	memset(testGameState.deck, NULL, sizeof(testGameState.deck));
	memset(testGameState.hand, NULL, sizeof(testGameState.hand));
	memset(testGameState.discard, NULL, sizeof(testGameState.discard));	
  
  return 0;
}