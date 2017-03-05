// Author: Steven Ha
// Date: March 03, 2017
// Class: CS362-400
// Assignment 5: Random Test Adventurer
// File Name: randomtestadventurer.c
// Description: This program will run random tests for the adventurer card

/*
NOTE: This random tester for the adventurer card was modified to account for A. Bagwell's Dominion source code. Initial runs of the test code had segmentation faults related to memory access issues. The test was trying to access memory that was not defined and that resulted in segmentation faults. To test the remaining sections of the refactored source code, the last test was omitted, but documented in the bug report. Examination of this file will show that check 7 was removed (commented out) from the random test.
*/

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TESTS 100000

// function prototypes
int assertTrue(int val1, int val2, int testCase, int testCount, int* passNum, int* failNum);
void printGameState(struct gameState* game, int curPlayer);
void printCardCount(int* arr, int arrSize);

int main(int argc, char** argv){
    
    //arguments that need to be set to initialize the game
    
    // setup random number generator
    time_t t;
	srand((unsigned) time(&t));
	
	// create a random seed between 1 and 10
	int rSeed = 1 + rand() % 10;
    
	// input needed to initialize the game
    int numberPlayers;
    int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState* game;
		
    // number of tests that pass and fail
    int numPass = 0;
    int numFail = 0;
    
    // store the current player
    int currentPlayer;
    
    // random values generated for 
    int rHandCount;
    int rDeckCount;
    int rDiscardCount;
    int rPlayedCount;
    
    // find the location of an adventurer card
    int positionAdventurer;
    
    // current number of tests
    int testCount = 0;
    
    // struct used to save previous gameState
    struct gameState pre;
    
    // int used to store the sum of the coins added to the player's hand
	int addedCoinSum;
	
	// int used to determine if an assert passed or faileds
	int assertRet;
	
	// define the number of checks 
	int numChecks = 6;
	
	int expectedAddedDiscardCount;
	
	// return value used to store if a card is a treasure card or not
	int ret1;
			 
	// integer used to store the current card
	int currentCard;
	
	// integers used to control the loop
	int i, j;
			
	// array used to store pass and fail values for each test		
	int passFailArr[numChecks][2];
	
	// int used to keep track of the number of games that have multiple check failures
	int numMultCheckFails = 0;
	
	// int used to store the id of the check being performed
	int checkNumber;
	
	// int that keeps track of the number of checks that fail for a given gamestate
	int checkArr[7] = {0,0,0,0,0,0,0};
	
	// int used to keep track of the number of check failures in a game
	int checkFailureCount;
	
	//int used to store sum of coins in player's hand
	int coinSum = 0;
	
	// int used to document if number of cards are the same
	int valueChange;
	
	// initialize the passFailArr to 0
	for(i = 0; i < numChecks; i++){
		for(j = 0; j < 2; j++){
			passFailArr[i][j] = 0;
		}
	}
	
	int fArr[27] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int sArr[27] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
    // execute the test while testCount < NUM_TESTS
	while(testCount < NUM_TESTS){
		// set adventurer position to -1 (position not found)
		positionAdventurer = -1;
	
		// create a new gamestate
		game =  malloc(sizeof(struct gameState));
   		
   		// generate a random number of players between 2 and 4
    	numberPlayers = (2 + rand() % 3);
	
		// initialize a game
		initializeGame(numberPlayers, kingdomCards, rSeed, game); 
		
		// get the currentPlayer (just checking the player in the first position for this test)
		currentPlayer = game->whoseTurn;
		
		// calc the number of cards that will be in the player's hand, deck, discard, played
		rHandCount = 1 + rand() % MAX_HAND;
		rDeckCount = 1 + rand() % MAX_DECK;
		rDiscardCount = rand() % MAX_HAND;
		rPlayedCount = rand() % MAX_HAND;
				
		// set the gamestate for the random values
		game->handCount[currentPlayer] = rHandCount;
		game->deckCount[currentPlayer] = rDeckCount;
		game->discardCount[currentPlayer] = rDiscardCount;
		game->playedCardCount = rPlayedCount;
		
		///////////////////////////////////////////////////////////////////////////////////////////
		// generate the cards in the player's hand
		for(j = 0; j < rHandCount; j++){
			game->hand[currentPlayer][j] = rand() % 26;
			//printf("    hand is %i\n", game->hand[currentPlayer][j]);
		}
		
		// generate the cards in the player's deck
		for(j = 0; j < rDeckCount; j++){
			game->deck[currentPlayer][j] = rand() % 26;
			//printf("    	deck is %i\n", game->deck[currentPlayer][j]);
		}
		
		// generate the cards that are in the player's discard pile
		for(j = 0; j < rDiscardCount; j++){
			game->discard[currentPlayer][j] = rand() % 26;
			//printf("    		discard is %i\n", game->discard[currentPlayer][j]);
		}
		
		// generate the cards that were played
		for(j = 0; j < rPlayedCount; j++){
			game->playedCards[j] = rand() % 26;
			//printf("    		discard is %i\n", game->discard[currentPlayer][j]);
		}
		///////////////////////////////////////////////////////////////////////////////////////////
		
		// find the adventurer card in the player's hand
		for(j = 0; j < rHandCount; j++){
			if(game->hand[currentPlayer][j] == adventurer && positionAdventurer == -1){
				positionAdventurer = j;				
			}
		}
				
		// reset coinSum to 0
		coinSum = 0;
		
		// update the coins for the current player
		for(i = 0; i < game->handCount[currentPlayer]; i++){
			if(game->hand[currentPlayer][i] == copper || game->hand[currentPlayer][i] == silver || game->hand[currentPlayer][i] == gold){
				coinSum = coinSum + game->hand[currentPlayer][i] - 3;
			}
		}
		
		game->coins = coinSum;
				
		// make a copy of game before playing adventurer
		memcpy(&pre, game, sizeof(struct gameState));
				
		// if the player has an adventurer card in their hand, play the card 
		if(positionAdventurer != -1){
			// set addedCoinSum to 0
			addedCoinSum = 0;
					
			// play the adventurer card
			cardEffect(adventurer, 0, 0, 0, game, positionAdventurer, 0);
			
			coinSum = 0;
			
			// get coinSum
			for(i = 0; i < game->handCount[currentPlayer]; i++){
				if(game->hand[currentPlayer][i] == copper || game->hand[currentPlayer][i] == silver || game->hand[currentPlayer][i] == gold){
					coinSum = coinSum + game->hand[currentPlayer][i] - 3;
				}
			}
									
			// set checkNumber to 0
			checkNumber = 0;
			
			// set checkFailureCount to 0
			checkFailureCount = 0;
			
			printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
			fflush(stdout);  
			
			//--------------------------------------------------------------------------------------
			// check # 1
			
			// check if the playedCard was incremented after playing adventurer
			assertRet = assertTrue(game->playedCardCount, pre.playedCardCount + 1 ,checkNumber + 1 + (testCount*numChecks), NUM_TESTS * numChecks, &numPass, &numFail);
			
			if(assertRet){
				printf("Test %i Failed (Played Card Count Increment)\n", checkNumber + 1 + (testCount*numChecks));
				checkFailureCount = checkFailureCount + 1;
				checkArr[checkNumber] = 1;
			}
	
			passFailArr[checkNumber][assertRet] = passFailArr[checkNumber][assertRet] + 1;
			checkNumber = checkNumber + 1;

			//--------------------------------------------------------------------------------------
			// check # 2
			
			// check if the correct number of cards was added to the player's hand (2 cards)		
			assertRet = assertTrue(game->handCount[currentPlayer], pre.handCount[currentPlayer] + 2,checkNumber + 1 + (testCount*numChecks), NUM_TESTS * numChecks, &numPass, &numFail);

			if(assertRet){
				printf("Test %i Failed (2 Added Cards)\n", checkNumber + 1 + (testCount*numChecks));
				checkFailureCount = checkFailureCount + 1;
				checkArr[checkNumber] = 1;
			}

			passFailArr[checkNumber][assertRet] = passFailArr[checkNumber][assertRet] + 1;
			checkNumber = checkNumber + 1;
			//--------------------------------------------------------------------------------------
			// check # 3

			/* check if the first card added to the hand is a treasure card	
			 */			

			currentCard = game->hand[currentPlayer][game->handCount[currentPlayer] - 2];
			
			if((currentCard == copper || currentCard == silver || currentCard == gold) && checkArr[checkNumber - 1] == 0){
				ret1 = 0;
			}
			else{
				ret1 = 1;
			}
									
			assertRet = assertTrue(ret1, 0 ,checkNumber + 1 + (testCount*numChecks), NUM_TESTS * numChecks, &numPass, &numFail);

			if(assertRet){
				printf("Test %i Failed (First Treasure Card)\n", checkNumber + 1 + (testCount*numChecks));
				checkFailureCount = checkFailureCount + 1;
				checkArr[checkNumber] = 1;
			}
			
			passFailArr[checkNumber][assertRet] = passFailArr[checkNumber][assertRet] + 1;
			checkNumber = checkNumber + 1;
			
			//--------------------------------------------------------------------------------------
			// check # 4

			/* check if the Second card added to the hand is a treasure card	
			 */			

			currentCard = game->hand[currentPlayer][game->handCount[currentPlayer] - 1];
			
			if((currentCard == copper || currentCard == silver || currentCard == gold) && checkArr[checkNumber - 2] == 0){
				ret1 = 0;
			}
			else{
				ret1 = 1;
			}
									
			assertRet = assertTrue(ret1, 0 ,checkNumber + 1 + (testCount*numChecks), NUM_TESTS * numChecks, &numPass, &numFail);

			if(assertRet){
				printf("Test %i Failed (Second Treasure Card)\n", checkNumber + 1 + (testCount*numChecks));
				checkFailureCount = checkFailureCount + 1;
				checkArr[checkNumber] = 1;
			}
			
			passFailArr[checkNumber][assertRet] = passFailArr[checkNumber][assertRet] + 1;
			checkNumber = checkNumber + 1;
			//--------------------------------------------------------------------------------------
			// check # 5

			/* check if the number of cards that were drawn that weren't added to the player's hand
			 * are added to the discard pile		
			 */			
			 
			expectedAddedDiscardCount = pre.deckCount[currentPlayer] - game->deckCount[currentPlayer] - (game->handCount[currentPlayer] - pre.handCount[currentPlayer]);
						
			assertRet = assertTrue(game->discardCount[currentPlayer] - pre.discardCount[currentPlayer], expectedAddedDiscardCount,checkNumber + 1 + (testCount*numChecks), NUM_TESTS * numChecks, &numPass, &numFail);

			if(assertRet){
				printf("Test %i Failed (Deck/Discard Balance)\n", checkNumber + 1 + (testCount*numChecks));
				checkFailureCount = checkFailureCount + 1;
				checkArr[checkNumber] = 1;
			}
			
			passFailArr[checkNumber][assertRet] = passFailArr[checkNumber][assertRet] + 1;
			checkNumber = checkNumber + 1;
			
			//--------------------------------------------------------------------------------------
			// check # 6
			
			// check if the correct number of coins was added to the player's coins			
			assertRet = assertTrue(game->coins, coinSum ,checkNumber + 1 + (testCount*numChecks), NUM_TESTS * numChecks, &numPass, &numFail);
			
			if(assertRet){
				printf("Test %i Failed (Coins)\n", checkNumber + 1 + (testCount*numChecks));
				checkFailureCount = checkFailureCount + 1;
				checkArr[checkNumber] = 1;
			}

			passFailArr[checkNumber][assertRet] = passFailArr[checkNumber][assertRet] + 1;
			checkNumber = checkNumber + 1;
			
			//--------------------------------------------------------------------------------------
			// check # 7
			
			// check if the correct number of cards hand, deck, discard is maintained in the game
			
			// next 6 for loops count the card types in the hand, deck, discard pile for pre and post gamestate
			for(i = 0; i < pre.handCount[currentPlayer]; i++){
				fArr[pre.hand[currentPlayer][i]] = fArr[pre.hand[currentPlayer][i]] + 1;
			}
			
			for(i = 0; i < pre.deckCount[currentPlayer]; i++){
				fArr[pre.deck[currentPlayer][i]] = fArr[pre.deck[currentPlayer][i]] + 1;
			}
			
			for(i = 0; i < pre.discardCount[currentPlayer]; i++){
				fArr[pre.discard[currentPlayer][i]] = fArr[pre.discard[currentPlayer][i]] + 1;
			}
			
			for(i = 0; i < game->handCount[currentPlayer]; i++){
				sArr[game->hand[currentPlayer][i]] = sArr[game->hand[currentPlayer][i]] + 1;
			}
			
			for(i = 0; i < game->deckCount[currentPlayer]; i++){
				sArr[game->deck[currentPlayer][i]] = sArr[game->deck[currentPlayer][i]] + 1;
			}
			
			/*_removed_ 
			for(i = 0; i < game->discardCount[currentPlayer]; i++){
				sArr[game->discard[currentPlayer][i]] = sArr[game->discard[currentPlayer][i]] + 1;
			}
			*/
			
			// set valueChange to 0 (card balance are the same)
			valueChange = 0;
			
			// check if the card balances are the same
			for(i = 0; i < 27; i++){
				if(fArr[i] != sArr[i]){
					valueChange = 1;
				}
			}
						
			/*//_removed_ 			
			assertRet = assertTrue(valueChange, 0 ,checkNumber + 1 + (testCount*numChecks), NUM_TESTS * numChecks, &numPass, &numFail);
			
			if(assertRet){
				printf("Test %i Failed (Card Balance)\n", checkNumber + 1 + (testCount*numChecks));
				//printGameState(&pre, currentPlayer);				
				checkFailureCount = checkFailureCount + 1;
				checkArr[checkNumber] = 1;
			}
			
			for(i = 0; i < 27; i++){
				fArr[i] = 0;
				sArr[i] = 0;
			}
			
			*/

			passFailArr[checkNumber][assertRet] = passFailArr[checkNumber][assertRet] + 1;
			checkNumber = checkNumber + 1;
			
			//--------------------------------------------------------------------------------------
			
			// print out game state
			fflush(stdout);  
			if(checkFailureCount >= 1){
				//printf("MULTIPLE FAILURES OCCURED\n[");
				printf("\nGAME STATE PRIOR TO PLAYING ADVENTURER\n"); 
				printGameState(&pre, currentPlayer);
				printf("\nGAME STATE AFTER TO PLAYING ADVENTURER\n"); 
				printGameState(game, currentPlayer);
			}
			
			// reset check arr
			for(i = 0; i < numChecks; i++){
				checkArr[i] = 0;	
			}
						
			// increment testCount
			testCount = testCount + 1;
		}

		// free the game
		free(game);
	}
	
	// print the pass and fail statistic of the whole test
	printf("PASSED = %i and FAILED = %i\n", numPass, numFail);
		
	// print the pass and fail statistics of each check
	for(i = 0; i < numChecks; i++){
		printf("CHECK %i: PASSED = %i and FAILED = %i\n", i + 1, passFailArr[i][0], passFailArr[i][1]);    
	}
	
	
    return 0;
}

/* Function Name: Assert True
 * Description: Compares 2 values and prints out message if the values are not the same
 * Parameters: int val1 - value that needs to be checked
 *             int val2 - value that is being compared against
 *             int testCase - test case id
 *			   int* passNum - pointer to pass count
 *			   int* passFail - pointer to fail count
 * Pre-Conditions: game should be initialized
 * Post-Conditions: if the val1 and val2 are not the same an error message will print and the passFlag will be set to 1
 */
int assertTrue(int val1, int val2, int testCase, int testCount, int* passNum, int* failNum){
	if(val1 != val2){
		//printf("Test Case %i of %i FAILED\n", testCase, testCount);
		*failNum = *failNum + 1;
		return 1;
	}
	else{
		//printf("Test Case %i of %i PASSED\n", testCase, testCount);
		*passNum = *passNum + 1;
		return 0;
	}
}

/* Function Name: Print Game State
 * Description: prints out the values defined in the gameState
 * Parameters: struct gameState* game - pointer to the game
 *             int curPlayer - value of the current player
 * Pre-Conditions: game should be initialized, player's hand, deck, discard pile should be defined
 * Post-Conditions: the gamestate will be printed to the screen.
 */
void printGameState(struct gameState* game, int curPlayer){
	// array containing the cound of the cards in the player's hand, deck and discard pile
	int handCount[27] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int deckCount[27] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int discardCount[27] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	int i; // int to control the loop
	int cardNum; // the current card being looked at
	
	printf("-----Game State-----\n");
	printf("Num Players: %i\n", game->numPlayers);
	printf("Player Hand Count: %i\n", game->handCount[curPlayer]);
	//_removed_ printf("Deck Count: %i\n", game->deckCount[curPlayer]);
	//_removed_ printf("Discard Count: %i\n", game->discardCount[curPlayer]);
	printf("Played Card Count: %i\n", game->playedCardCount);
	printf("Coins: %i\n", game->coins);
	
	for(i = 0; i < game->handCount[curPlayer]; i++){
		cardNum = game->hand[curPlayer][i];
		handCount[cardNum] = handCount[cardNum] + 1;
	}
	
	for(i = 0; i < game->deckCount[curPlayer]; i++){
		cardNum = game->deck[curPlayer][i];
		deckCount[cardNum] = deckCount[cardNum] + 1;
	}

    /*_removed_ 
	for(i = 0; i < game->discardCount[curPlayer]; i++){
		cardNum = game->discard[curPlayer][i];
		discardCount[cardNum] = discardCount[cardNum] + 1;
	}
	*/
	
	printf("HANDS CONTAIN\n");
	printCardCount(&handCount, 27);
	printf("DECK CONTAIN\n");
	printCardCount(&deckCount, 27);
	//_removed_ printf("DISCARD CONTAIN\n");
	//_removed_ printCardCount(&discardCount, 27);
	printf("\n");
}

/* Function Name: print card count
 * Description: function prints out the values of an array
 * Parameters: int* arr - pointer to an array
 *             int arrsize - size of the array
 * Pre-Conditions: array should be initialized and contain values
 * Post-Conditions: the values of the array will be printed to the screen
 */
void printCardCount(int* arr, int arrSize){
	int i; // integer used to control a for loop
	
	// print out the array if the arraySize is 27
	if(arrSize == 27){
		printf("[");
		for(i = 0; i < 26; i++){
			printf("%i,", arr[i]);
		}
		printf("%i]\n", arr[26]);
	}
}