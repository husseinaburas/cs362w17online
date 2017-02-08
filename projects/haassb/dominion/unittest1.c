/**************************************************************************
Test scoreFor()
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
		printf("Unittest1- scoreFor(): test# %d PASS \n", testNumber);
	}

	else
	{
		printf("Unittest1- scoreFor(): test# %d FAIL \n", testNumber);
	}
}
	
int main() 
{
    int i;
	int temp;
    int numPlayer = 2;
    int player;
	int handCount;
    struct gameState testGameState;
    int maxHandCount = 5;
	
	int expectedResult[numPlayer];
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

	
	
	
/*****************************************************************/
	//test 0 score
	
	//set expected results
	for (i = 0; i < numPlayer; i++)
    {
      expectedResult[i] = 0;
	}	
	
    for (i = 0; i < numPlayer; i++)
    {
		testNumber++;
		temp = scoreFor(i, &testGameState);
		assertTrue(temp, expectedResult[i], testNumber);
	}
	
	  //clear hand, deck, and discard
	  memset(testGameState.deck, NULL, sizeof(testGameState.deck));
	  memset(testGameState.hand, NULL, sizeof(testGameState.hand));
	  memset(testGameState.discard, NULL, sizeof(testGameState.discard));	
	  
		
/*****************************************************************/
	//test hand score, leave deck score and discard score at 0
	//fill all players' hands with sample cards
	
	//set expected results
	for (i = 0; i < numPlayer; i++)
    {
      expectedResult[i] = 10;
	}		
	
	
	for (i = 0; i < numPlayer; i++)
    {
		//populate hand with sample cards equal to max handcount, score should 	equal 10
		testGameState.hand[i][0] = curse;
		testGameState.hand[i][1] = estate;
		testGameState.hand[i][2] = duchy;
		testGameState.hand[i][3] = province;
		testGameState.hand[i][4] = great_hall;	
				
		testGameState.handCount[i] = 5;					//set handCount for number of sample cards
	}


	
	//generate score for each player
    for (i = 0; i < numPlayer; i++)
    {
		testNumber++;
		temp = scoreFor(i, &testGameState);
		assertTrue(temp, expectedResult[i], testNumber);
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

	
/*****************************************************************/	
	//test deck score, leave hand score and discard score at 0
	//fill all players' decks with sample cards
	
	//set expected results
	for (i = 0; i < numPlayer; i++)
    {
      expectedResult[i] = 0;
	}	
	
	
	for (i = 0; i < numPlayer; i++)
    {
		//populate hand with sample cards equal to max handcount, score should 	equal 11, include garden card
		testGameState.deck[i][0] = curse;
		testGameState.deck[i][1] = estate;
		testGameState.deck[i][2] = duchy;
		testGameState.deck[i][3] = province;
		testGameState.deck[i][4] = great_hall;	
		testGameState.deck[i][5] = gardens;	
		
		//extraneous non-point cards
		testGameState.deck[i][6] = copper;	
		testGameState.deck[i][7] = silver;	
		testGameState.deck[i][8] = smithy;	
		testGameState.deck[i][9] = minion;	
		testGameState.deck[i][10] = adventurer;	
				
		testGameState.deckCount[i] = 11;					//set handCount for number of sample cards
	}



	
	//generate score for each player
    for (i = 0; i < numPlayer; i++)
    {
		testNumber++;
		temp = scoreFor(i, &testGameState);
		assertTrue(temp, expectedResult[i], testNumber);
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
	
/*****************************************************************/	
	//test discard score, leave hand score and deck score at 0
	//fill all players' discard with sample cards
	
	//set expected results
	for (i = 0; i < numPlayer; i++)
    {
      expectedResult[i] = 11;
	}		
	
	for (i = 0; i < numPlayer; i++)
    {	
		//populate hand with sample cards equal to max handcount, score should 	equal 11, exclude garden card
		testGameState.discard[i][0] = curse;
		testGameState.discard[i][1] = estate;
		testGameState.discard[i][2] = duchy;
		testGameState.discard[i][3] = province;
		testGameState.discard[i][4] = great_hall;	
		testGameState.discard[i][5] = great_hall;	
		
		//extraneous non-point cards
		testGameState.discard[i][6] = copper;	
		testGameState.discard[i][7] = silver;	
		testGameState.discard[i][8] = smithy;	
		testGameState.discard[i][9] = minion;	
		testGameState.discard[i][10] = adventurer;	
	
		testGameState.discardCount[i] = 11;					//set handCount for number of sample cards
	}


	
	//generate score for each player
    for (i = 0; i < numPlayer; i++)
    {
		testNumber++;
		temp = scoreFor(i, &testGameState);
		assertTrue(temp, expectedResult[i], testNumber);
	}	
	
	  //clear hand, deck, and discard
	memset(testGameState.deck, NULL, sizeof(testGameState.deck));
	memset(testGameState.hand, NULL, sizeof(testGameState.hand));
	memset(testGameState.discard, NULL, sizeof(testGameState.discard));	
	

/*****************************************************************/
	//test dseparate player scores
	//fill all players' hands with sample cards
	//set expected results
	expectedResult[0] = 30;
	expectedResult[1] = 9;
	
	//populate player 1 cards - score equals 30
	//populate hand
	testGameState.hand[0][0] = curse;
	testGameState.hand[0][1] = estate;
	testGameState.hand[0][2] = duchy;
	testGameState.hand[0][3] = province;
	testGameState.hand[0][4] = great_hall;	
			
	testGameState.handCount[0] = 5;					//set count for number of sample cards
	
	//populate deck
	testGameState.deck[0][0] = curse;
	testGameState.deck[0][1] = estate;
	testGameState.deck[0][2] = duchy;
	testGameState.deck[0][3] = province;
	testGameState.deck[0][4] = great_hall;	
			
	testGameState.deckCount[0] = 5;					//set count for number of sample cards	
	
	
	//populate discard
	testGameState.discard[0][0] = curse;
	testGameState.discard[0][1] = estate;
	testGameState.discard[0][2] = duchy;
	testGameState.discard[0][3] = province;
	testGameState.discard[0][4] = great_hall;	
			
	testGameState.discardCount[0] = 5;					//set count for number of sample cards
	
	
	//populate player 2 cards - score equals 9
	//populate hand
	testGameState.hand[1][0] = curse;
	testGameState.hand[1][1] = estate;
	testGameState.hand[1][2] = duchy;

			
	testGameState.handCount[1] = 3;					//set count for number of sample cards
	
	//populate deck
	testGameState.deck[1][0] = curse;
	testGameState.deck[1][1] = estate;
	testGameState.deck[1][2] = duchy;
	
			
	testGameState.deckCount[0] = 3;					//set count for number of sample cards	
	
	
	//populate discard
	testGameState.discard[1][0] = curse;
	testGameState.discard[1][1] = estate;
	testGameState.discard[1][2] = duchy;

			
	testGameState.discardCount[1] = 3;					//set count for number of sample cards	
	

	
	//generate score for each player
    for (i = 0; i < numPlayer; i++)
    {
		testNumber++;
		temp = scoreFor(i, &testGameState);
		assertTrue(temp, expectedResult[i], testNumber);
	}	
	
			


	return 0;

}