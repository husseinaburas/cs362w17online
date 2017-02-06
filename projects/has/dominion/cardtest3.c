// Author: Steven Ha
// Date: Feb 3, 2017
// Class: CS362-400
// Assignment 3: Card Test 3
// File Name: cardtest3.c
// Description: This program will run tests on the dominion card great hall

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

// function prototypes
void assertTrue(int val1, int val2, char* testName, char* cardName, int testCase, int testCount, int* passFlag);

int main(int argc, char** argv){
    
    //arguments that need to be set to initialize the game
    int numberPlayers = 2;
    struct gameState game;
    int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    
    // initialize the game
    initializeGame(numberPlayers, kingdomCards, 1, &game);    
    
    // int used to determine if program successfully passed (0 - pass)
    int* pass = 0;

	// int defining number of tests
	int numTests = 4;
	
	// int store the current player
    int currentPlayer;
    
    // int storing the number of played cards
    int playedCardCount;
    
    // int storing the card that was played
    int playedCard;
    
    // int stores the number of actions a player has
    int numActions;
    
    // int stores number of cards in players hand
    int numCards;
    
    currentPlayer = game.whoseTurn;
	
	// set the first card in the current player's hand to great_hall
	game.hand[currentPlayer][0] = great_hall;
			
	// call the function to test
	playGreatHall(&game, 0, 0);
	
	//======================================================================================
	
	/* Test Case 1
	 * Description: playedCardCount should be 1 after calling playgreathall()
	 * This test should PASS.
	 */
	 
	playedCardCount = game.playedCardCount;
	
	assertTrue(playedCardCount, 1, "CARD TEST 1", "great hall", 1, numTests, &pass);
	
	//======================================================================================
	
	/* Test Case 2
	 * Description: the first played card should be greathall after calling playgreathall()
	 * This test should PASS.
	 */
	 
	playedCard = game.playedCards[0];
	
	assertTrue(playedCard, great_hall, "CARD TEST 1", "great hall", 2, numTests, &pass);

	//======================================================================================
	
	/* Test Case 3
	 * Description: number of actions should be 1 after calling playgreathall()
	 * This test should FAIL.
	 */
	 
	numActions = game.numActions;
	
	assertTrue(numActions, 1, "CARD TEST 1", "great hall", 3, numTests, &pass);
	
	//======================================================================================
	
	/* Test Case 4
	 * Description: player's handcount should be 5 after calling playgreathall()
	 * This test should PASS.
	 */
	 
	numCards = game.handCount[currentPlayer];
	
	assertTrue(numCards, 5, "CARD TEST 1", "great hall", 4, numTests, &pass);
		
	//======================================================================================
		
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
 *             char* cardName - name of the card
 *             int testCase - test case id
 *             int* passFlag - pointer to int storing pass/fail
 * Pre-Conditions: game should be initialized
 * Post-Conditions: if the val1 and val2 are not the same an error message will print and the passFlag will be set to 1
 */
void assertTrue(int val1, int val2, char* testName, char* cardName, int testCase, int testCount, int* passFlag){
	if(val1 != val2){
		printf("%s: Test Case %i of %i of card '%s' FAILED\n", testName, testCase, testCount, cardName);
		*passFlag = 1;
	}
}
