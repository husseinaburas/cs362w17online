// Author: Steven Ha
// Date: Feb 2, 2017
// Class: CS362-400
// Assignment 3: Unit Test 4
// File Name: unittest4.c
// Description: This program will run unit tests on the dominion function endTurn()

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

// function prototypes
void assertTrue(int val1, int val2, char* testName, char* functionName, int testCase, int* passFlag);

int main(int argc, char** argv){
    
    //arguments that need to be set to initialize the game
    int numberPlayers = 4;
    struct gameState game;
    int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    
    // initialize the game
    initializeGame(numberPlayers, kingdomCards, 1, &game);
    
    // unit test 4 will check the endTurn() function
	int numTests = 5;
			
	// int used to control loop
	int i;
	
	// int used to record test ID
	int testID;
	
	// int used to determine if program successfully passed (0 - pass)
    int* pass = 0;
	
	// int used to record the return of the function under test
	int ret;
	
	printf("///// ----- STARTING UNIT TEST 4 (endTurn) -----/////\n");
	
    // for loop is used to iterate through each test case
    for( i = 0; i < numTests; i++){  	
    	// set test id
    	testID = i + 1;
    	    	
    	// get the return
    	ret = endTurn(&game);

    	// check results
    	assertTrue(ret, 0, "UNIT TEST 4", "endTurn()", (2*i) + 1, &pass);  
    	
    	// set test id
    	testID = i + 1;
    	
    	// check if player is changed
    	if(i <= 2){
     		assertTrue(game.whoseTurn, i+1, "UNIT TEST 4", "endTurn()", (2*i)+2, &pass); 
    	}
    	else{
    	    assertTrue(game.whoseTurn, i-3, "UNIT TEST 4", "endTurn()", (2*i)+2, &pass); 
    	}

    }
    
    if( pass == 0){
    	printf("**UNIT TEST 4 SUCCESSFULLY PASSED**\n");
    }
    else{
    	printf("**UNIT TEST 4 FAILED**\n");
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
		printf("%s: Test Case %i of 10 for function '%s' FAILED\n", testName, testCase, functionName);
		*passFlag = 1;
	}
	else{
		printf("%s: Test Case %i of 10 for function '%s' PASSED\n", testName, testCase, functionName);
	}
}
