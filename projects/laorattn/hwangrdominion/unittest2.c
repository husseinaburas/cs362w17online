//Unit test for getCost() method in dominion.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int customAssert(int condition, char *errorMsg, int cardNum, int expected, int actual)
{
	if (condition)
	{
		return 0;
	}
	else
	{
		printf("Error: %s\n", errorMsg);
		printf("\tCard Num: %d\n", cardNum);
		printf("\tExpected Value: %d\n", expected);
		printf("\tReturned Value: %d\n", actual);
		return 1;	
	}
}


int main()
{
	int numBugs = 0;	//Stores total number of bugs encountered by unit test
	int returnValue;
	int expectedValue;

	//Array that stores the correct cost of each card 
	int correctCost[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

	
	printf ("\n----------Starting Unit Test 2----------\n");

	//Test all cards for correct cost
	int i;
	for (i = curse; i <= treasure_map; i++)
	{
		expectedValue = correctCost[i];
		returnValue = getCost(i);
		numBugs += customAssert( (returnValue == expectedValue), "Card cost incorrect.", i, expectedValue, returnValue );
	}

	//Test one out of bounds card number - expected return value is -1
	i = treasure_map + 1;
	expectedValue = -1;
	returnValue = getCost(i);
	numBugs += customAssert( (returnValue == expectedValue), "Returned nonzero value for out of bounds card number.", i, expectedValue, returnValue );


	if(numBugs)
	{
		printf("\nUnit Test 2 - Total bugs: %d\n", numBugs);
	}	
	else
	{
		printf("\nUnit Test 2 - All tests for getCost() successful\n");
	}

	printf("\n----------End of Unit Test 2----------\n");

	return 0;
}
