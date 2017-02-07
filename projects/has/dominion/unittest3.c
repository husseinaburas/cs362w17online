// Author: Steven Ha
// Date: Feb 2, 2017
// Class: CS362-400
// Assignment 3: Unit Test 3
// File Name: unittest3.c
// Description: This program will run unit tests on the dominion function supplyCount()

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

// function prototypes
void assertTrue(int val1, int val2, char* testName, char* functionName, int testCase, int* passFlag);

int main(int argc, char** argv){
    
    //arguments that need to be set to initialize the game
    int numberPlayers = 2; // dictates # of cards
    int numberPlayersTwo = 4; // dictates # of cards
    struct gameState game;
    struct gameState gameTwo;
    int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    
    // initialize the game
    initializeGame(numberPlayers, kingdomCards, 1, &game);
    initializeGame(numberPlayersTwo, kingdomCards, 1, &gameTwo);
    
    // unit test3 will check the supplyFor() function using 12 test cases
	int numTests = 12;
	
	// int used to store return of function under test
	int numSupplies;    
	
	// int array storing cards being used for the test
	int cards[6] = {copper, silver, gold, estate, village, tribute};
	
	// int array containing the expected supply count for the chose cards (values when games starts)
	int expectedCardCount[6] = {46, 40, 30, 8, 10, 10};
	int expectedCardCountTwo[6] = {32, 40, 30, 12, 10, 10};
	
	// int used to control loop
	int i;
	
	// int used to record test ID
	int testID;
	
	// int used to determine if program successfully passed (0 - pass)
    int* pass = 0;
	
    // for loop is used to iterate through each test case for 2 players
    for( i = 0; i < (numTests/2); i++){
		// get the supply card for the chosen card
    	numSupplies = supplyCount(cards[i], &game);
    	
    	// set test id
    	testID = i + 1;
    	
    	// check results
    	assertTrue(numSupplies, expectedCardCount[i], "UNIT TEST 3", "supplyCount()", testID, &pass);
    }
    
    // for loop is used to iterate through each test case for 4 players
    for( i = 0; i < (numTests/2); i++){
		// get the supply card for the chosen card
    	numSupplies = supplyCount(cards[i], &gameTwo);
    	
    	// set test ids
    	testID = i + 6;
    	
    	// check results
    	assertTrue(numSupplies, expectedCardCountTwo[i], "UNIT TEST 3", "supplyCount()", testID, &pass);
    }
    
    if( pass == 0){
    	printf("UNIT TEST 3 SUCCESSFULLY PASSED\n");
    }
	
    return 0;
}

/* Function Name: Assert True
 * Description: Compares 2 values and prints out message if the values are not the same
 * Parameters: int val1 - value that needs to be checked
 *             int val2 - value that is being compared against
 *             char* testName - name of the test
 *             char* functionName - name of the function
 *             int testCase - test case id
 *             int* passFlag - pointer to int storing pass/fail
 * Pre-Conditions: game should be initialized
 * Post-Conditions: if the val1 and val2 are not the same an error message will print and the passFlag will be set to 1
 */
void assertTrue(int val1, int val2, char* testName, char* functionName, int testCase, int* passFlag){
	if(val1 != val2){
		printf("%s: Test Case %i of function '%s' FAILED\n", testName, testCase, functionName);
		*passFlag = 1;
	}
}
