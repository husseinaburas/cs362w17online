/*cardtest2.c*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"


//Own assert function
int asserttrue(int input, int number){
	if (input){
		printf("\tTEST %d SUCCESSFUL\n", number);
	}
	else
		printf("\tTEST %d FAILED\n", number);
	return 0;
}
    
int main(){

	int i, success, result, tester;
	int seed = 1000;
	int numPlayers = 2;
	int currentPlayer = 0;
	int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, salvager, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// placing the card in the players hand
	G.hand[currentPlayer][3] = smithy; 
	updateCoins(currentPlayer, &G, 0);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	printf("----------------- Card: %s ----------------\n", TESTCARD);
	printf("\nTESTS FOR VALID INPUT\n");
	// ----------- TEST 1: Test correct return statements for valid input -----------
	printf("%s TEST 1: Correct return statements for valid input\n", TESTCARD);
	//result = playSmithy(&testG, currentPlayer, 3);
	result = cardEffect(smithy, 0, 0, 0, &testG, 3, NULL);
	if (result == 0){
		asserttrue(1, 1);
	}
	else{
		asserttrue(0, 1);
	}

	// ----------- TEST 2: Test phase before and after is 0 -----------
	printf("%s TEST 2: Phase stays as phase 0\n", TESTCARD);
	if (result == 0){
		if (testG.phase == G.phase){
			asserttrue(1, 2);
		}
		else{
			asserttrue(0, 2);
		}
	}
	else{
		printf("TEST 2 could not be run due to invalid input\n");
	}

	// ----------- TEST 3: Test number of buys after is the same -----------
	printf("%s TEST 3: Number of buys after is greater than 0\n", TESTCARD);
	if (result == 0){
		if (testG.numBuys == G.numBuys){
			asserttrue(1, 3);
		}
		else{
			asserttrue(0, 3);
		}
	}
	else{
		printf("TEST 3 could not be run due to invalid input\n");
	}
	// ----------- TEST 4: Test number of actions is the same -----------
	printf("%s TEST 4: Number of actions after is the same\n", TESTCARD);
	if (result == 0){
		if (testG.numActions == G.numActions ){
			asserttrue(1, 4);
		}
		else{
			asserttrue(0, 4);
		}
	}
	else{
		printf("TEST 4 could not be run due to invalid input\n");
	}

	

	// ----------- TEST 5: Test number of actions after is greater than 0 -----------
	printf("%s TEST 5: Number of actions after is greater than 0\n", TESTCARD);
	if (result == 0){
		if (testG.numActions > 0){
			asserttrue(1, 5);
		}
		else{
			asserttrue(0, 5);
		}
	}
	else{
		printf("TEST 5 could not be run due to invalid input\n");
	}

	// ----------- TEST 6: Test handCount of player increased by 2 (+ 3 - smithy) -----------
	printf("%s TEST 6: handCount for current player has increased by 2\n", TESTCARD);
	if (result == 0){
		if (testG.handCount[currentPlayer] == G.handCount[currentPlayer] + 2){
			asserttrue(1, 6);
		}
		else{
			asserttrue(0, 6);
		}
	}
	else{
		printf("TEST 6 could not be run due to invalid input\n");
	}
	// ----------- TEST 7: Test that the smithy card is in the discard pile -----------
	printf("%s TEST 7: Smithy card is in the discard pile\n", TESTCARD);
	if (result == 0){
		if (testG.discard[currentPlayer][testG.discardCount[currentPlayer]] == smithy){
			asserttrue(1, 7);
		}
		else{
			asserttrue(0, 7);
		}
	}
	else{
		printf("TEST 7 could not be run due to invalid input\n");
	}
	// ----------- TEST 8: Test that the number of coins has been updated -----------
	printf("%s TEST 8: Number of coins has been updated\n", TESTCARD);
	if (result == 0){
		tester = 0;
		for (i = 0; i < testG.handCount[currentPlayer]; i++){
			if (testG.hand[currentPlayer][i] == copper)
				tester += 1;
			else if (testG.hand[currentPlayer][i] == silver){
				tester += 2;
			}
			else if (testG.hand[currentPlayer][i] == gold){
				tester += 3;
			}
		}
		if (tester == testG.coins){
			asserttrue(1, 8);
		}
		else{
			asserttrue(0, 8);
		}
	}
	else{
		printf("TEST 8 could not be run due to invalid input\n");
	}
	// ----------- TEST 9: Test that the players total number of cards has not changed -----------
	printf("%s TEST 9: Other players have not gained cards\n", TESTCARD);
	if (result == 0){
		if (testG.handCount[otherPlayer] + testG.deckCount[otherPlayer] + testG.discardCount[otherPlayer] !=
			G.handCount[otherPlayer] + G.deckCount[otherPlayer] + G.discardCount[otherPlayer]){
			asserttrue(0, 9);
		}
		else{
			asserttrue(1, 9);
		}
	}
	else{
		printf("TEST 9 could not be run due to invalid input\n");
	}
	// ----------- TEST 10: Test that the number of victory (province, estate, duchy) cards has not changed -----------
	printf("%s TEST 10: Victory cards have not been affected\n", TESTCARD);
	if (result == 0){
		for (i = estate; i <= province; i++){
			if (testG.supplyCount[i] != G.supplyCount[i]){
				asserttrue(0, 10);
				success = 0;
				break;
			}
			else{
				success = 1;
			}
		}
		if (success == 1){
			asserttrue(1, 10);
		}
	}
	else{
		printf("TEST 10 could not be run due to invalid input\n");
	}
	// ----------- TEST 11: Test that number of kingdom cards (supply...) has not changed -----------
	printf("%s TEST 11: Supply cards have not been changed\n", TESTCARD);
	if (result == 0){
		for (i = copper; i <= treasure_map; i++){
			if (testG.supplyCount[i] != G.supplyCount[i]){
				asserttrue(0, 11);
				success = 0;
				break;
			}
			else{
				success = 1;
			}
		}
		if (success == 1){
			asserttrue(1, 11);
		}
	}
	else{
		printf("TEST 11 could not be run due to invalid input\n");
	}



	// reset a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// placing the card in the players hand
	G.hand[currentPlayer][3] = smithy;
	updateCoins(currentPlayer, &G, 0);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

		printf("\nTESTS FOR INVALID INPUT\n");

	// ----------- TEST 12 : Test correct return statements for wrong card name -----------
	printf("%s TEST 12: Correct return statements for wrong card name\n", TESTCARD);
	//result = playSmithy(&testG, currentPlayer, 4);
	result = cardEffect(smithy, 0, 0, 0, &testG, 4, NULL);
	if (result == -1){
		asserttrue(1, 12);
	}
	else{
		asserttrue(0, 12);
	}

	// ----------- TEST 13: Test state stays same invalid input -----------
	printf("%s TEST 13: State says the same with invalid input\n", TESTCARD);
	
	if (result == -1){

		for (i = 0; i <= treasure_map; i++){
			if (testG.supplyCount[i] != G.supplyCount[i]){
				asserttrue(0, 13);
				success = 0;
				break;
			}
			else{
				success = 1;
			}
		}
		if (success == 1){ // supplies staying the same
			asserttrue(1, 13);
		}
		else if (testG.coins != G.coins){
		asserttrue(0, 13);
		}
		else if (testG.numBuys != G.numBuys){
			asserttrue(0, 13);

		}
		else if (testG.numActions != G.numActions){
			asserttrue(0, 13);
		} 
		else if ((G.handCount[currentPlayer] + G.deckCount[currentPlayer] + G.discardCount[currentPlayer] + G.playedCardCount) != (
		testG.handCount[currentPlayer] + testG.deckCount[currentPlayer] + testG.discardCount[currentPlayer] + testG.playedCardCount))	{
			asserttrue(0, 13);
		}
		else if ((G.handCount[otherPlayer] + G.deckCount[otherPlayer] + G.discardCount[otherPlayer]) != (
		testG.handCount[otherPlayer] + testG.deckCount[otherPlayer] + testG.discardCount[otherPlayer])){
			asserttrue(0, 13);
		}
		else{
			asserttrue(1, 13);
		}
	}
	else{
		printf("TEST 13 could not be run due to failing test 12\n");
	}

	// reset a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// placing the card in the players hand
	G.hand[currentPlayer][3] = smithy;
	G.phase = 1;
	updateCoins(currentPlayer, &G, 0);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// ----------- TEST 14 : Test correct return statements for wrong phase -----------
	printf("%s TEST 14: Correct return statements for wrong phase\n", TESTCARD);
	//result = playSmithy(&testG, currentPlayer, 3);
	result = cardEffect(smithy, 0, 0, 0, &testG, 3, NULL);
	if (result == -1){
		asserttrue(1, 14);
	}
	else{
		asserttrue(0, 14);
	}

	// ----------- TEST 15: Test state stays same invalid input -----------
	printf("%s TEST 15: State says the same with invalid input\n", TESTCARD);
	
	if (result == -1){

		for (i = 0; i <= treasure_map; i++){
			if (testG.supplyCount[i] != G.supplyCount[i]){
				asserttrue(0, 15);
				success = 0;
				break;
			}
			else{
				success = 1;
			}
		}
		if (success == 1){ // supplies staying the same
			asserttrue(1, 15);
		}
		else if (testG.coins != G.coins){
		asserttrue(0, 15);
		}
		else if (testG.numBuys != G.numBuys){
			asserttrue(0, 15);

		}
		else if (testG.numActions != G.numActions){
			asserttrue(0, 15);
		} 
		else if ((G.handCount[currentPlayer] + G.deckCount[currentPlayer] + G.discardCount[currentPlayer] + G.playedCardCount) != (
		testG.handCount[currentPlayer] + testG.deckCount[currentPlayer] + testG.discardCount[currentPlayer] + testG.playedCardCount))	{
			asserttrue(0, 15);
		}
		else if ((G.handCount[otherPlayer] + G.deckCount[otherPlayer] + G.discardCount[otherPlayer]) != (
		testG.handCount[otherPlayer] + testG.deckCount[otherPlayer] + testG.discardCount[otherPlayer])){
			asserttrue(0, 15);
		}
		else{
			asserttrue(1, 15);
		}
	}
	else{
		printf("TEST 15 could not be run due to failing test 14\n");
	}

	// reset a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// placing the card in the players hand
	G.hand[currentPlayer][3] = smithy;
	G.numActions = 0;
	updateCoins(currentPlayer, &G, 0);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// ----------- TEST 16 : Test correct return statements for wrong number of actions-----------
	printf("%s TEST 16: Correct return statements for wrong number of actions\n", TESTCARD);
	//result = playSmithy(&testG, currentPlayer, 3);
	result = cardEffect(smithy, 0, 0, 0, &testG, 3, NULL);
	if (result == -1){
		asserttrue(1, 16);
	}
	else{
		asserttrue(0, 16);
	}

	// ----------- TEST 17: Test state stays same invalid input -----------
	printf("%s TEST 17: State says the same with invalid input\n", TESTCARD);
	
	if (result == -1){

		for (i = 0; i <= treasure_map; i++){
			if (testG.supplyCount[i] != G.supplyCount[i]){
				asserttrue(0, 17);
				success = 0;
				break;
			}
			else{
				success = 1;
			}
		}
		if (success == 1){ // supplies staying the same 
			asserttrue(1, 17);
		}
		else if (testG.coins != G.coins){
		asserttrue(0, 17);
		}
		else if (testG.numBuys != G.numBuys){
			asserttrue(0, 17);

		}
		else if (testG.numActions != G.numActions){
			asserttrue(0, 17);
		} 
		else if ((G.handCount[currentPlayer] + G.deckCount[currentPlayer] + G.discardCount[currentPlayer] + G.playedCardCount) != (
		testG.handCount[currentPlayer] + testG.deckCount[currentPlayer] + testG.discardCount[currentPlayer] + testG.playedCardCount))	{
			asserttrue(0, 17);
		}
		else if ((G.handCount[otherPlayer] + G.deckCount[otherPlayer] + G.discardCount[otherPlayer]) != (
		testG.handCount[otherPlayer] + testG.deckCount[otherPlayer] + testG.discardCount[otherPlayer])){
			asserttrue(0, 17);
		}
		else{
			asserttrue(1, 17);
		}
	}
	else{
		printf("TEST 17 could not be run due to failing test 16\n");
	}
	return 0;
}
