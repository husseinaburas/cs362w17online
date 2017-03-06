/**************************************************************************
Test isGameOver()
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
		printf("Unittest4- isGameOver(): test# %d PASS \n", testNumber);
	}

	else
	{
		printf("Unittest4- isGameOver(): test# %d FAIL \n", testNumber);
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


/**********************************************/	
//test empty supply

	testNumber++;
	temp = isGameOver(&testGameState);
	expectedResult = 1;
	assertTrue(temp, expectedResult, testNumber);


	
/**********************************************/	
//test full supply

//set all card counts to 5
  for (i = 0; i < 25; i++)
    {
      testGameState.supplyCount[i] = 5;
	}

	testNumber++;
	temp = isGameOver(&testGameState);
	expectedResult = 0;
	assertTrue(temp, expectedResult, testNumber);
	
	
	
/**********************************************/	
//test province = 0
     
	 //set province to 0
	testGameState.supplyCount[province] = 0;
	
	testNumber++;
	temp = isGameOver(&testGameState);
	expectedResult = 1;
	
	assertTrue(temp, expectedResult, testNumber);
	

/**********************************************/	
//test province > 0
     
	 //set province to 0
	testGameState.supplyCount[province] = 4;
	
	testNumber++;
	temp = isGameOver(&testGameState);
	expectedResult = 0;
	
	assertTrue(temp, expectedResult, testNumber);

/**********************************************/	
//test 2 supply decks empty

	 //set 2 piles to 0
	testGameState.supplyCount[curse] = 0;
	testGameState.supplyCount[estate] = 0;
	
	testNumber++;
	temp = isGameOver(&testGameState);
	expectedResult = 0;
	
	assertTrue(temp, expectedResult, testNumber);

/**********************************************/	
//test 3 supply decks empty
	 //set 3 piles to 0
	testGameState.supplyCount[curse] = 0;
	testGameState.supplyCount[estate] = 0;
	testGameState.supplyCount[duchy] = 0;
	
	testNumber++;
	temp = isGameOver(&testGameState);
	expectedResult = 1;
	
	assertTrue(temp, expectedResult, testNumber);

/**********************************************/	
//test 3 supply decks empty including no province card
	 //set curse pile back to 1
	testGameState.supplyCount[curse] = 1;
	testGameState.supplyCount[estate] = 0;
	testGameState.supplyCount[duchy] = 0;
	testGameState.supplyCount[province] = 0;
	
	testNumber++;
	temp = isGameOver(&testGameState);
	expectedResult = 1;
	
	assertTrue(temp, expectedResult, testNumber);	
	
/**********************************************/	
//test 3 supply decks empty plus no province card
	 //set curse pile back to 1
	testGameState.supplyCount[curse] = 0;
	testGameState.supplyCount[estate] = 0;
	testGameState.supplyCount[duchy] = 0;
	testGameState.supplyCount[province] = 0;
	
	testNumber++;
	temp = isGameOver(&testGameState);
	expectedResult = 1;
	
	assertTrue(temp, expectedResult, testNumber);
	

  return 0;
}