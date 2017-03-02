// Author: Steven Ha
// Date: Feb 2, 2017
// Class: CS362-400
// Assignment 3: Unit Test 2
// File Name: unittest2.c
// Description: This program will run unit tests on the dominion function getCost()

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

// function prototypes
void assertTrue(int val1, int val2, char* testName, char* functionName, int testCase, char* cardName, int* passFlag);

int main(int argc, char** argv){
    
    // int array stores getCost return values
    int ret[27];
    
    // string array stores the names of the cards
    char *cardNames[27] = {"curse", "estate", "duchy", "provinence", "copper", "silver", "gold", "adventurer", "council room", "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great hall", "minion", "steward", "tribute", "ambassador", "curpurse", "embargo", "outpost", "salvager", "sea hag", "treasure map"};
    
    // int array that contains the cost of each card in dominion
    int expectedCost[27] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
    
    // int used to control for loops
    int i, j;
    
    // int used to keep track of the test ID
    int testID;
    
    // int used to determine if program successfully passed (0 - pass)
    int* pass = 0;
    
    // get the cost of each card
    for(i = 0; i < 27; i++){
        ret[i] = getCost(i);
    }
    
	printf("///// ----- STARTING UNIT TEST 2 (getCost) -----/////\n");
    
    // check if the card values match
    for(j = 0; j < 27; j++){
    	// set test ID
    	testID = j + 1;
    	
    	// check results
        assertTrue(ret[j], expectedCost[j], "UNIT TEST 2", "getCost()", testID, cardNames[j], &pass);    
    }
    
    if(pass == 0){
        printf("**UNIT TEST 2 SUCCESSFULLY PASSED**\n");
    }
    else{
    	printf("**UNIT TEST 2 FAILED**\n");
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
 *             char* cardName - name of the card being tested
 *             int* passFlag - pointer to int storing pass/fail
 * Pre-Conditions: game should be initialized
 * Post-Conditions: if the val1 and val2 are not the same an error message will print and the passFlag will be set to 1
 */
void assertTrue(int val1, int val2, char* testName, char* functionName, int testCase, char* cardName, int* passFlag){
	if(val1 != val2){
		printf("%s: Test Case %i of 27 for function '%s' for card '%s' FAILED\n", testName, testCase, functionName, cardName);
		*passFlag = 1;
	}
	else{
		printf("%s: Test Case %i of 27 for function '%s' for card '%s' PASSED\n", testName, testCase, functionName, cardName);
	}
}
