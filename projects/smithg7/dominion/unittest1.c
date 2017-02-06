/***************************************
 CS362 - Assignment 3
 Gary Smith
 Unit Test for isGameOver() from dominion.c

 int isGameOver(struct gameState *state) {
  int i;
  int j;
	
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
    {
      return 1;
    }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)
    {
      if (state->supplyCount[i] == 0)
	{
	  j++;
	}
    }
  if ( j >= 3)
    {
      return 1;
    }

  return 0;
}
***************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void assertTrue(int firstValue, int secondValue, char* message);
void testProvince(struct gameState *myState, int provinceValue, char* message, int expectedResult);
void testSupply(struct gameState *myState, int setValue, int maxChange, char* message, int expectedResult);

int main()
{
	//Setup a game state
	//Perform test
	//return/print result
	//Repeat as needed for each test

	struct gameState *myState = newGame();
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
	initializeGame(2, k, 1, myState);

	//Call is Game Over right when the game begins
	int result = isGameOver(myState);
	assertTrue(result, 0, "Game just started. No Changes."); //Game should not be over.
	initializeGame(2, k, 1, myState);


	/***************************************
	* Testing the Province cards (first check in isGameOver)
	***************************************/
	//Set the stack of province cards to 0
	testProvince(myState, 0, "Province card count set to 0.", 1);
	initializeGame(2, k, 1, myState);

	//Set the stack of province cards to -1
	testProvince(myState, -1, "Province card count set to -1.", 1);
	initializeGame(2, k, 1, myState);


	/***************************************
	* Testing if 3 or more piles in the supply pile are 0
	***************************************/	
	//if zero piles are empty
	result = isGameOver(myState);
	assertTrue(result, 0, "No modifications to the supplyCount array."); //Game should not be over.
	initializeGame(2, k, 1, myState);

	//If one pile is empty
	testSupply(myState, 0, 1, "Set 1 non -1 pile to 0", 0);  //Game should not be over
	initializeGame(2, k, 1, myState);

	//If two piles are empty
	testSupply(myState, 0, 2, "Set 2 non -1 piles to 0", 0);  //Game should not be over
	initializeGame(2, k, 1, myState);

	//If three piles are empty
	testSupply(myState, 0, 3, "Set 3 non -1 piles to 0", 1);  //Game should be over
	initializeGame(2, k, 1, myState);

	//If all piles are 0 
	testSupply(myState, 0, 25, "Set all non -1 piles to 0", 1);  //Game should be over
	initializeGame(2, k, 1, myState);

	//If all piles are -1 (never initialized)
	testSupply(myState, -1, 25, "Set all non -1 piles to -1", 1);  //Game should be over
	initializeGame(2, k, 1, myState);

	return 0;
}

/***************************************
Custom AssertTrue function to provide more info and prevent
the whole program from crashing
***************************************/
void assertTrue(int firstValue, int secondValue, char* message)
{
	if(firstValue == secondValue)
	{
		printf("TEST PASSED SUCCESSFULLY: %s\n", message);
	}
	else
	{
		printf("TEST FAILED: %s\n", message);
	}

}

/***************************************
Repeatable test to check the supplyCount[province] value
***************************************/
void testProvince(struct gameState *myState, int provinceValue, char* message, int expectedResult)
{
	myState->supplyCount[province] = provinceValue;
	int result = isGameOver(myState);
	assertTrue(result, expectedResult, message); //Game should be over.	
}

/***************************************
Repeatable test to check the supplyCount[0..24] values
***************************************/
void testSupply(struct gameState *myState, int setValue, int maxChange, char* message, int expectedResult)
{
	int i=0;
	int changeCounter=0;
	for (i = 0; i < 25; i++)
	{
		if(myState->supplyCount[i] > 0)
		{
			myState->supplyCount[i] = setValue;
			changeCounter++;
		}
		if(changeCounter >= maxChange)
			break;
	}
	int result = isGameOver(myState);
	assertTrue(result, expectedResult, message); 
}
