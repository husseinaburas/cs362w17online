/**************************************************************************
Test getCost()
**************************************************************************/#include "dominion.h"
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
		printf("Unittest2- getCost(): test# %d PASS \n", testNumber);
	}

	else
	{
		printf("Unittest2- getCost(): test# %d FAIL \n", testNumber);
	}
}
	
int main() 
{
	int temp;
	int expectedResult;
	int testNumber = 0;
	
	//test curse card
	temp = getCost(curse);
	expectedResult = 0;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);
	
	//test estate card
	temp = getCost(estate);
	expectedResult = 2;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);
	
	//test duchy card
	temp = getCost(duchy);
	expectedResult = 5;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);
	
	//test province card
	temp = getCost(province);
	expectedResult = 8;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);	
	
	//test copper card
	temp = getCost(copper);
	expectedResult = 0;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);

	//test silver card
	temp = getCost(silver);
	expectedResult = 3;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);	
	
	//test gold card
	temp = getCost(gold);
	expectedResult = 6;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);	
	
	//test adventurer card
	temp = getCost(adventurer);
	expectedResult = 6;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);

	//test council_room card
	temp = getCost(council_room);
	expectedResult = 5;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);

	//test feast card
	temp = getCost(feast);
	expectedResult = 4;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);	
	
	//test gardens card
	temp = getCost(gardens);
	expectedResult = 4;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);

	//test mine card
	temp = getCost(mine);
	expectedResult = 5;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);
	
	//test remodel card
	temp = getCost(remodel);
	expectedResult = 4;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);	
	
	//test smithy card
	temp = getCost(smithy);
	expectedResult = 4;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);

	//test village card
	temp = getCost(village);
	expectedResult = 3;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);

	//test baron card
	temp = getCost(baron);
	expectedResult = 4;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);	
	
	//test great_hall card
	temp = getCost(great_hall);
	expectedResult = 3;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);

	//test minion card
	temp = getCost(minion);
	expectedResult = 5;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);
	
	//test steward card
	temp = getCost(steward);
	expectedResult = 3;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);	
	
	//test tribue card
	temp = getCost(tribute);
	expectedResult = 5;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);

	//test ambassador card
	temp = getCost(ambassador);
	expectedResult = 3;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);

 	//test cutpurse card
	temp = getCost(cutpurse);
	expectedResult = 4;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);	
	
	//test embargo card
	temp = getCost(embargo);
	expectedResult = 3;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);

	//test outpost card
	temp = getCost(outpost);
	expectedResult = 5;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);   
	
	//test salvager card
	temp = getCost(salvager);
	expectedResult = 4;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);	
	
	//test sea_hag card
	temp = getCost(sea_hag);
	expectedResult = 4;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);

	//test treasure_map card
	temp = getCost(treasure_map);
	expectedResult = 4;
	testNumber++;
	assertTrue(temp, expectedResult, testNumber);

	
	return 0;
}