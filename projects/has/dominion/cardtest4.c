// Author: Steven Ha
// Date: Feb 3, 2017
// Class: CS362-400
// Assignment 3: Card Test 4
// File Name: cardtest4.c
// Description: This program will run tests on the dominion card adventurer

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
	int numTests = 7;
	
	// int store the current player
    int currentPlayer;
    
    // int storing the number of played cards
    int playedCardCount;
    
    // int storing the number of cards in players hand
    int playerHandCount;
    
    // int storing the card that was played
    int playedCard;
    
    // int stores the number of actions a player has
    int numActions;
    
    // int stores number of cards in players hand
    int numCards;
    
    // int stores number of cards discarded
    int discardCount;
    
    int drawnTreasure = 0;
    int cardDrawn;
    int tempHand[MAX_HAND];
    int z = 0;
    
	int deckCounter;
	int discards;
	int i;
        
    currentPlayer = game.whoseTurn;
    
    game.deck[currentPlayer][0] = copper;
    game.deck[currentPlayer][1] = copper;
    game.deck[currentPlayer][2] = sea_hag;
    game.deck[currentPlayer][3] = sea_hag;
    game.deck[currentPlayer][4] = sea_hag;
    
	// set the first card in the current player's hand to smithy
	game.hand[currentPlayer][0] = adventurer;
			
	// call the function to test
	playAdventurer(&game, 0, currentPlayer, cardDrawn, tempHand, z);
	
	//======================================================================================
	
	/* Test Case 1
	 * Description: playedCardCount should be 1 after calling playadventurer()
	 * This test should FAIL.
	 */
	
	playedCardCount = game.playedCardCount;
	
	assertTrue(playedCardCount, 1, "CARD TEST 4", "adventurer", 1, numTests, &pass);
	
	//======================================================================================
	
	/* Test Case 2
	 * Description: the first played card should be adventurer after calling playadventurer()
	 * This test should FAIL.
	 */
	 
	playedCard = game.playedCards[0];
			
	assertTrue(playedCard, adventurer, "CARD TEST 4", "adventurer", 2, numTests, &pass);
	
	//======================================================================================
	
	/* Test Case 3
	 * Description: the player's handcount should be 6 after calling playadventurer()
	 * This test should FAIL.
	 */
	
	numCards = game.handCount[currentPlayer];
			
	assertTrue(numCards, 6, "CARD TEST 4", "adventurer", 3, numTests, &pass);
	
	//======================================================================================
	
	/* Test Case 4
	 * Description: the player's discard count should be 3 after calling playadventurer()
	 * This test should PASS.
	 */
	
	discardCount = game.discardCount[currentPlayer];
		
	assertTrue(discardCount, 3, "CARD TEST 4", "adventurer", 4, numTests, &pass);
	
	//======================================================================================
	
	/* Test Case 5-7
	 * Description: the discard pile should contain 3 sea_hags after calling playadventurer()
	 * Test 5 and 6 should PASS. Test 7 should fail.
	 */

	for( i = 0; i < discardCount; i++){
		discards = game.discard[0][i];
		assertTrue(discards, 25, "CARD TEST 4", "adventurer", (5+i), numTests, &pass);
	}
	
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
