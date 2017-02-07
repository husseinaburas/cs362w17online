// Author: Steven Ha
// Date: Feb 2, 2017
// Class: CS362-400
// Assignment 3: Unit Test 1
// File Name: unittest1.c
// Description: This program will run unit tests on the dominion function updateCoins()

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

// function prototypes
void assertTrue(int val1, int val2, char* testName, char* functionName, int testCase, int* passFlag);

int main(int argc, char** argv){
    
    //arguments that need to be set to initialize the game
    int numberPlayers = 2;
    struct gameState game;
    int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    
    // initialize the game
    initializeGame(numberPlayers, kingdomCards, 1, &game);
    
    // unit test2 will check the updateCoins() function using 4 test cases
	int numTests = 4;

    // array is used to store the coins used for each test case
    int testCoins[4][5] = {{copper, silver, gold, copper, copper}, {silver, silver, estate, silver, silver}, {gold, gold, copper, silver, silver}, {copper, copper, copper, copper, copper}};
    
    // array is used to store the bonus values for each test case
    int testBonus[4] = {0, 1, 2, 3};
    
    // array is used to store the expected coin values (calculated using the testCoins and bonus values)
    int expectedCoins[4] = {8, 9, 13, 8};
    
    // ints used to control the for loop
    int i, j;
    
    // int used to record the current player
    int player;
    
    // int used to record the current player's hand count
    int playerHandCount;
    
    // int used to determine if program successfully passed (0 - pass)
    int* pass = 0;
    
    // int used to keep track of the test case id
    int testID;
    
    // get the current player
    player = game.whoseTurn;
    
    // get the current player's hand count
    playerHandCount = game.handCount[player];
    
    // for loop is used to iterate through each test case
    for( i = 0; i < numTests; i++){
    	// for loop used to assign the coin values for each test case
    	for ( j = 0; j <  playerHandCount; j++){
    		game.hand[player][j] = testCoins[i][j];
    	}
    	
    	// call the updateCoins function
    	updateCoins(player, &game, testBonus[i]);
    	
		// set test ID    	
    	testID = i + 1;
    	
    	// check results
    	assertTrue(game.coins, expectedCoins[i], "UNIT TEST 1", "updateCoins()", testID, &pass);
    }
    
    if( pass == 0){
    	printf("UNIT TEST 1 SUCCESSFULLY PASSED\n");
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
