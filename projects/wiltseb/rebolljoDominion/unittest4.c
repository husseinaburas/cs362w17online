#include "dominion.h"
#include "dominion_helpers.h"
#include "domtests.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
TESTS isGameOver()
*/

int main(){
	struct gameState TestGame1;
	int numPlayers = 2;
	int seed = 10;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int testFlag = 0;
	int i;
	int numEmpty;
	
	
	initializeGame(numPlayers, cards, seed, &TestGame1);

	//Get initial count of hand, discard, deck
	printf("UNITTEST 4 -----------------------------------------------------------------\n");

	printf("INITIALIZING TEST 0....\n");
	/*
	TEST 0: PRECONDITIONS
	*/
	testFlag = 0;
	numEmpty = 0;
	for (i = 0; i < treasure_map; i++){
		if (TestGame1.supplyCount[i] == 0){
			numEmpty += 1;
		}
	}
	assertTrue(numEmpty == 0, "no empty supply piles", numEmpty, 0, &testFlag);
	assertTrue(TestGame1.supplyCount[province] == 8, "initial provinces pile", TestGame1.supplyCount[province], 8, &testFlag);

	checkTest(testFlag, 0);
	
	printf("INITIALIZING TEST 1....\n");
	/*
	TEST 1: GAME IS NOT OVER WHEN SUPPLY PILES FULL AND 8 PROVINCES LEFT 
	*/
	testFlag = 0;
	assertTrue(isGameOver(&TestGame1) == 0, "beginning of game", 0, isGameOver(&TestGame1), &testFlag); 
	checkTest(testFlag, 1);
	
	printf("INITIALIZING TEST 2....\n");
	/*
	TEST 2: GAME IS OVER WHEN SUPPLIES ARE FULL, AND NO PROVINCES LEFT 
	*/
	testFlag = 0;
	TestGame1.supplyCount[province] = 0;
	assertTrue(isGameOver(&TestGame1) == 1, "no provinces", 1, isGameOver(&TestGame1), &testFlag);
	
	checkTest(testFlag, 2);
	
	//Add provinces back in
	TestGame1.supplyCount[province] = 8;

	printf("INITIALIZING TEST 3....\n");
	/*
	TEST 3: GAME IS NOT OVER WHEN 2 SUPPLY PILES EMPTY AND 8 PROVINCES LEFT 
	*/
	testFlag = 0;
	TestGame1.supplyCount[smithy] = 0;
	TestGame1.supplyCount[adventurer] = 0;
	assertTrue(isGameOver(&TestGame1) == 0, "2 supply piles empty", 0, isGameOver(&TestGame1), &testFlag); 

	checkTest(testFlag, 3);
	

	
	
	printf("INITIALIZING TEST 4....\n");
	/*
	TEST 4: GAME IS OVER WHEN 3 SUPPLY PILES EMPTY AND 8 PROVINCES LEFT 
	*/
	testFlag = 0;

	assertTrue(isGameOver(&TestGame1) == 0, "provinces resupplied", 0, isGameOver(&TestGame1), &testFlag);

	//empty gold supply
	TestGame1.supplyCount[gold] = 0;
	assertTrue(isGameOver(&TestGame1) == 1, "3 supply piles empty", 1, isGameOver(&TestGame1), &testFlag);
	
	checkTest(testFlag, 4);
	


	return 0;
}

