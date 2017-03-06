/*unittest2.c*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define FUNCTION_NAME "buyCard"

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
    int i;
    int preBuys, postBuys, preCoins, postCoins, preCards, postCards, preCount, postCount, result;
    int seed = 1000;
    int numPlayers = 2;
    int player = 0;
    int otherPlayer = 1;
    int testCard1 = silver;
    int testCard2 = gold;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	G.phase = 1; // setting phase to 1 for buying phase
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	printf("----------------- Function: %s ----------------\n", FUNCTION_NAME);
	preBuys = testG.numBuys;
	preCoins = testG.coins;
	result = buyCard(testCard1, &testG);
	postBuys = testG.numBuys;
	postCoins = testG.coins;
	
	// testing only on inputs where buy is successful
	printf("TESTS ON SUCCESSFUL BUY OF SILVER\n");

	// ----------- TEST 1: Test for number of buys for players turn decreases by 1 -----------
  	printf("%s TEST 1: Number of buys decreases by 1\n", FUNCTION_NAME);
	if (result == 0){			
		if (preBuys-postBuys == 1){
			asserttrue(1, 1);
		}
		else{
			asserttrue(0, 1);
		}
	}
	else{
		printf("TEST 1 could not be run due to invalid input\n");
	}


	// ----------- TEST 2: Test that the number of buys does not go negative -----------
	printf("%s TEST 2: Number of buys does not go negative\n", FUNCTION_NAME);
	if (result == 0){
		if (postBuys >= 0){
			asserttrue(1, 2);
		}
		else{
			asserttrue(0, 2);
		}
	}
	else{
		printf("TEST 2 could not be run due to invalid input\n");
	}

	// ----------- TEST 3: Test that the number of coins for current player decreased appropriately -----------
	printf("%s TEST 3: Number of coins decreases appropriately\n", FUNCTION_NAME);
	if (result == 0){
		i = getCost(testCard1);
		if (preCoins - postCoins == i){
			asserttrue(1, 3);
		}
		else{
			asserttrue(0, 3);
		}
	}
	else{
		printf("TEST 3 could not be run due to invalid input\n");
	}

	// ----------- TEST 4: Test that the current players amount of coins did not go below 0 -----------
	printf("%s TEST 4: Number of coins does not go negative\n", FUNCTION_NAME);
	if (result == 0){
		if (postCoins >= 0){
			asserttrue(1, 4);
		}
		else{
			asserttrue(0, 4);
		}
	}
	else{
		printf("TEST 4 could not be run due to invalid input\n");
	}
	// ----------- TEST 5: Test that the total number of cards the player has increases by 1 (sum of all decks) -----------
	printf("%s TEST 5: Total card count for player has increased by 1\n", FUNCTION_NAME);
	if (result == 0){
		// count pre number of cards
		preCards = G.handCount[player] + G.deckCount[player] + G.discardCount[player] + G.playedCardCount;

		// count post number of cards
		postCards = testG.handCount[player] + testG.deckCount[player] + testG.discardCount[player] + testG.playedCardCount;

		if (postCards - preCards == 1){
			asserttrue(1, 5);
		}
		else{
			asserttrue(0, 5);
		}	
	}
	else{
		printf("TEST 5 could not be run due to invalid input\n");
	}
	// ----------- TEST 6: Test that the other player's card count does not change -----------
	printf("%s TEST 6: Other players card count does not change\n", FUNCTION_NAME);
	if (result == 0){
		// count pre number of cards
		preCards = G.handCount[otherPlayer] + G.deckCount[otherPlayer] + G.discardCount[otherPlayer];

		// count post number of cards
		postCards = testG.handCount[otherPlayer] + testG.deckCount[otherPlayer] + testG.discardCount[otherPlayer] ;

		if (postCards - preCards == 0){
			asserttrue(1, 6);
		}
		else{
			asserttrue(0, 6);
		}
	}
	else{
		printf("TEST 6 could not be run due to invalid input\n");
	}	
	// ----------- TEST 7: Test that the supply count for silver decreased by 1 -----------

	printf("%s TEST 7: Supply count for silver decreases by 1\n", FUNCTION_NAME);
	if (result == 0){
		preCount = G.supplyCount[testCard1];
		postCount = testG.supplyCount[testCard1];
		if (preCount - postCount == 1){
			asserttrue(1, 7);
		}
		else{
			asserttrue(0, 7);
		}
	}
	else{
		printf("TEST 7 could not be run due to invalid input\n");
	}

	// ----------- TEST 8: Test that the supply count for silver did not go below 0 -----------
	printf("%s TEST 8: Supply count for silver did not go below 0\n", FUNCTION_NAME);
	if (result == 0){
		if (postCount >= 0){
			asserttrue(1, 8);
		}
		else{
			asserttrue(0, 8);
		}
	}
	else{
		printf("TEST 8 could not be run due to invalid input\n");
	}

	printf("\nTESTS ON EXPECTED FAILURES\n");
	// ----------- TEST 9: Test that the function cannot be called if the phase is not 1 -----------
	printf("%s TEST 9: Function returns error when phase is not buy (1)\n", FUNCTION_NAME);
	memcpy(&testG, &G, sizeof(struct gameState)); // resetting game state
	testG.phase = 0; // setting phase to other than 1
	result = buyCard(testCard1, &testG);
	if (result == -1){
		asserttrue(1, 9);
	} 
	else{
		asserttrue(0, 9);
	}

	// ----------- TEST 10: Test state did not change after unsuccessful buy -----------
	printf("%s TEST 10: State does not change after unsuccessful buy(wrong phase)\n", FUNCTION_NAME);
	if (result == -1){
		if (testG.coins != G.coins){
			asserttrue(0, 10);
		}
		else if (testG.numBuys != G.numBuys){
			asserttrue(0, 10);

		} 
		else if ((G.handCount[player] + G.deckCount[player] + G.discardCount[player] + G.playedCardCount) != (
		testG.handCount[player] + testG.deckCount[player] + testG.discardCount[player] + testG.playedCardCount))	{
			asserttrue(0, 10);
		}
		else if ((G.handCount[otherPlayer] + G.deckCount[otherPlayer] + G.discardCount[otherPlayer]) != (
		testG.handCount[otherPlayer] + testG.deckCount[otherPlayer] + testG.discardCount[otherPlayer])){
			asserttrue(0, 10);
		}
		else{
			asserttrue(1, 10);
		}
	}
	else{
		printf("TEST 10 could not be run due to unplanned input\n");
	}

	// ----------- TEST 11: Test that cannot buy a card if number of buys is 0 -----------
	printf("%s TEST 11: Function returns error when number of buys is 0\n", FUNCTION_NAME);
	memcpy(&testG, &G, sizeof(struct gameState)); // resetting game state
	
	testG.numBuys = 0; //settin number of buys to 0
	preBuys = testG.numBuys;
	result = buyCard(testCard1, &testG);
	if (result == -1){
		asserttrue(1, 11);
	} 
	else{
		asserttrue(0, 11);
	}

	// ----------- TEST 12: Test state did not change after unsuccessful buy -----------
	printf("%s TEST 12: State does not change after unsuccessful buy (no buys left)\n", FUNCTION_NAME);
	if (result == -1){
		if (testG.coins != G.coins){
			asserttrue(0, 12);
		}
		else if (testG.numBuys != preBuys){
			asserttrue(0, 12);

		} 
		else if ((G.handCount[player] + G.deckCount[player] + G.discardCount[player] + G.playedCardCount) != (
		testG.handCount[player] + testG.deckCount[player] + testG.discardCount[player] + testG.playedCardCount))	{
			asserttrue(0, 12);
		}
		else if ((G.handCount[otherPlayer] + G.deckCount[otherPlayer] + G.discardCount[otherPlayer]) != (
		testG.handCount[otherPlayer] + testG.deckCount[otherPlayer] + testG.discardCount[otherPlayer] )){
			asserttrue(0, 12);
		}
		else{
			asserttrue(1, 12);
		}
	}
	else{
		printf("TEST 12 could not be run due to unplanned input\n");
	}

	// ----------- TEST 13: Test that cannot buy a card if no cards of that type available -----------
	printf("%s TEST 13: Function returns error if no cards of that type available\n", FUNCTION_NAME);
	memcpy(&testG, &G, sizeof(struct gameState)); // resetting game state
	testG.supplyCount[testCard1] = 0; // setting test card count to 0
	result = buyCard(testCard1, &testG);
	if (result == -1){
		asserttrue(1, 13);
	} 
	else{
		asserttrue(0, 13);
	}

	// ----------- TEST 14: Test state did not change after unsuccessful buy -----------
	printf("%s TEST 14: State does not change after unsuccessful buy (no cards available)\n", FUNCTION_NAME);
	if (result == -1){
		if (testG.coins != G.coins){
			asserttrue(0, 14);
		}
		else if (testG.numBuys != G.numBuys){
			asserttrue(0, 14);

		} 
		else if ((G.handCount[player] + G.deckCount[player] + G.discardCount[player] + G.playedCardCount) != (
		testG.handCount[player] + testG.deckCount[player] + testG.discardCount[player] + testG.playedCardCount))	{
			asserttrue(0, 14);
		}
		else if ((G.handCount[otherPlayer] + G.deckCount[otherPlayer] + G.discardCount[otherPlayer] ) != (
		testG.handCount[otherPlayer] + testG.deckCount[otherPlayer] + testG.discardCount[otherPlayer] )){
			asserttrue(0, 14);
		}
		else{
			asserttrue(1, 14);
		}
	}
	else{
		printf("TEST 14 could not be run due to unplanned input\n");
	}
	// ----------- TEST 15: Test that cannot buy a card if player does not have enough money -----------
	printf("%s TEST 15: Function returns error if player does not have enough money\n", FUNCTION_NAME);
	memcpy(&testG, &G, sizeof(struct gameState)); // resetting game state
	result = buyCard(testCard2, &testG);
	if (result == -1){
		asserttrue(1, 15);
	} 
	else{
		asserttrue(0, 15);
	}

	// ----------- TEST 16: Test state did not change after unsuccessful buy -----------
	printf("%s TEST 16: State does not change after unsuccessful buy (not enough money)\n", FUNCTION_NAME);
	if (result == -1){
		if (testG.coins != G.coins){
			asserttrue(0, 16);
		}
		else if (testG.numBuys != G.numBuys){
			asserttrue(0, 16);

		} 
		else if ((G.handCount[player] + G.deckCount[player] + G.discardCount[player] + G.playedCardCount) != (
		testG.handCount[player] + testG.deckCount[player] + testG.discardCount[player] + testG.playedCardCount))	{
			asserttrue(0, 16);
		}
		else if ((G.handCount[otherPlayer] + G.deckCount[otherPlayer] + G.discardCount[otherPlayer] ) != (
		testG.handCount[otherPlayer] + testG.deckCount[otherPlayer] + testG.discardCount[otherPlayer] )){
			asserttrue(0, 16);
		}
		else{
			asserttrue(1, 16);
		}
	}
	else{
		printf("TEST 16 could not be run due to unplanned input\n");
	}

	

	return 0;
}
