/**************************************************************************
Test playAdventurer
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
		printf("Cardtest2-playAdventurer(): test# %d PASS \n", testNumber);
	}

	else
	{
		printf("Cardtest2- playAdventurer(): test# %d FAIL \n", testNumber);
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
//test when 2 treasures are present, discard is empty


	//populate hand with sample cards 
	testGameState.hand[0][0] = adventurer;
	testGameState.hand[0][1] = estate;
	testGameState.hand[0][2] = duchy;
	testGameState.hand[0][3] = province;
	testGameState.hand[0][4] = great_hall;
	testGameState.handCount[0] = 5;

	//populate deck with 2 curse cards and 2 treasure cards
	testGameState.deck[0][0] = curse;
	testGameState.deck[0][1] = copper;
	testGameState.deck[0][2] = curse;
	testGameState.deck[0][3] = copper;
	testGameState.deckCount[0] = 4;	

	testNumber++;
	expectedHandCount = 6;
	expectedDeckCount = 2;
	expectedDiscardCount = 3;
	
	playAdventurer(&testGameState);	
	
	result1 = testGameState.handCount[0];
	result2 = testGameState.deckCount[0];
	result3 = testGameState.discardCount[0];
	
	assertTrue(expectedHandCount, result1, testNumber);
	
	testNumber++;
	assertTrue(expectedDeckCount, result2, testNumber);	
	
	testNumber++;
	assertTrue(expectedDiscardCount, result3, testNumber);		
	
	
/************************************************************/
//test that treasure cards made it into hand

	//count treasure cards
	result1 = 0;
	
	for(i = 0; i < testGameState.handCount[0]; i++)
	{
		if(testGameState.hand[0][i] == copper)
		{
			//increase counter
			result1++;
		}
	}

	
	expectedResult = 2;
	testNumber++;
	
	assertTrue(result1, expectedResult, testNumber);
	

	//reset cards
	  memset(testGameState.deck, NULL, sizeof(testGameState.deck));
	  memset(testGameState.hand, NULL, sizeof(testGameState.hand));
	  memset(testGameState.discard, NULL, sizeof(testGameState.discard));	
	
/************************************************************/
//test when deck has only has 1 treasure card and discard pile needs to be shuffled


	//populate hand with sample cards and adventurer in position 0
	testGameState.hand[0][0] = adventurer;
	testGameState.hand[0][1] = estate;
	testGameState.hand[0][2] = duchy;
	testGameState.hand[0][3] = province;
	testGameState.hand[0][4] = great_hall;
	testGameState.handCount[0] = 5;

	//populate deck with 1 treasure card
	testGameState.deck[0][0] = curse;
	testGameState.deck[0][1] = curse;
	testGameState.deck[0][2] = curse;
	testGameState.deck[0][3] = silver;
	testGameState.deckCount[0] = 4;

	//populate deck with 1 treasure card
	testGameState.discard[0][0] = silver;	

	testNumber++;
	expectedHandCount = 6;
	expectedDeckCount = 2;
	
	playAdventurer(&testGameState);	
	
	result1 = testGameState.handCount[0];
	result2 = testGameState.deckCount[0];
	result3 = testGameState.discardCount[0];
	
	assertTrue(expectedHandCount, result1, testNumber);
	
	testNumber++;
	assertTrue(expectedDeckCount, result2, testNumber);	
	
	
	//reset cards
	  memset(testGameState.deck, NULL, sizeof(testGameState.deck));
	  memset(testGameState.hand, NULL, sizeof(testGameState.hand));
	  memset(testGameState.discard, NULL, sizeof(testGameState.discard));


/************************************************************/
//test that treasure cards made it into hand

	//count treasure cards
	result1 = 0;
	
	for(i = 0; i < testGameState.handCount[0]; i++)
	{
		if(testGameState.hand[0][i] == silver)
		{
			//increase counter
			result1++;
		}
	}

	
	expectedResult = 1;
	testNumber++;
	
	assertTrue(result1, expectedResult, testNumber);
	

	//reset cards
	  memset(testGameState.deck, NULL, sizeof(testGameState.deck));
	  memset(testGameState.hand, NULL, sizeof(testGameState.hand));
	  memset(testGameState.discard, NULL, sizeof(testGameState.discard));	
	
	
  


/************************************************************/
//test when 1 treasure card is present, discard is empty


	//populate hand with sample cards and adventurer in position 0
	testGameState.hand[0][0] = adventurer;
	testGameState.hand[0][1] = estate;
	testGameState.hand[0][2] = duchy;
	testGameState.hand[0][3] = province;
	testGameState.hand[0][4] = great_hall;
	testGameState.handCount[0] = 5;

	//populate deck with 3 curse cards
	testGameState.deck[0][0] = curse;
	testGameState.deck[0][1] = curse;
	testGameState.deck[0][2] = curse;
	testGameState.deck[0][3] = silver;
	testGameState.deckCount[0] = 4;	

	testNumber++;
	expectedHandCount = 5;
	expectedDeckCount = 3;
	expectedDiscardCount = 4;
	
	playAdventurer(&testGameState);	
	
	result1 = testGameState.handCount[0];
	result2 = testGameState.deckCount[0];
	result3 = testGameState.discardCount[0];
	
	assertTrue(expectedHandCount, result1, testNumber);
	
	testNumber++;
	assertTrue(expectedDeckCount, result2, testNumber);	
	
	testNumber++;
	assertTrue(expectedDiscardCount, result3, testNumber);	


/************************************************************/
//test that treasure cards made it into hand

	//count treasure cards
	result1 = 0;
	
	for(i = 0; i < testGameState.handCount[0]; i++)
	{
		if(testGameState.hand[0][i] == silver)
		{
			//increase counter
			result1++;
		}
	}

	
	expectedResult = 1;
	testNumber++;
	
	assertTrue(result1, expectedResult, testNumber);
	

	//reset cards
	  memset(testGameState.deck, NULL, sizeof(testGameState.deck));
	  memset(testGameState.hand, NULL, sizeof(testGameState.hand));
	  memset(testGameState.discard, NULL, sizeof(testGameState.discard));	
	
	
	return 0;
}












