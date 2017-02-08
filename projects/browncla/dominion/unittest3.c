/*unittest3.c*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define FUNCTION_NAME "endTurn"

//int endTurn(struct gameState *state);
/*
int endTurn(struct gameState *state) {
  int k;
  int i;
  int currentPlayer = whoseTurn(state);
  
  //Discard hand
  for (i = 0; i < state->handCount[currentPlayer]; i++){
    state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
    state->hand[currentPlayer][i] = -1;//Set card to -1
  }
  state->handCount[currentPlayer] = 0;//Reset hand count
    
  //Code for determining the player
  if (currentPlayer < (state->numPlayers - 1)){ 
    state->whoseTurn = currentPlayer + 1;//Still safe to increment
  }
  else{
    state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
  }

  state->outpostPlayed = 0;
  state->phase = 0;
  state->numActions = 1;
  state->coins = 0;
  state->numBuys = 1;
  state->playedCardCount = 0;
  state->handCount[state->whoseTurn] = 0;

  //int k; move to top
  //Next player draws hand
  for (k = 0; k < 5; k++){
    drawCard(state->whoseTurn, state);//Draw a card
  }

  //Update money
  updateCoins(state->whoseTurn, state , 0);

  return 0;
}
*/

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

	int i, priorHandCount, priorDiscard, currentDiscard, tester;
    int seed = 1000;
    int numPlayers = 2;
    int priorPlayer = 0;
    int currentPlayer, success;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// Changing values for future tests
	G.outpostPlayed = 2;
	G.phase = 2;
	G.numActions = 3;
	G.numBuys = 5;
	G.playedCardCount = 2;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	priorHandCount = testG.handCount[priorPlayer];
	priorDiscard = testG.discardCount[priorPlayer];
	i = endTurn(&testG);
	printf("----------------- Function: %s ----------------\n", FUNCTION_NAME);
	// ----------- TEST 1: Test that prior player discard pile increased by handCount  -----------
	printf("%s TEST 1: Prior player discard pile has increased by handCount\n", FUNCTION_NAME);
	
	currentDiscard = testG.discardCount[priorPlayer];
	if (currentDiscard == priorDiscard + priorHandCount){
		asserttrue (1, 1);
	}
	else{
		asserttrue	(0, 1);
	}
	

	// ----------- TEST 2: Test that prior player hand is all set to -1 -----------
	printf("%s TEST 2: Prior player hand set to -1\n", FUNCTION_NAME);
	for (i = 0; i < priorHandCount; i++){
		if (testG.hand[priorPlayer][i] != -1){
			asserttrue	(0, 2);
			success = 0;
			break;
		}
		else{
			success = 1;
		}
	}
	if (success == 1){
		asserttrue	(1, 2);
	}
	// ----------- TEST 3: Test that prior player handCount is 0 -----------
	printf("%s TEST 3: Prior player handCount is 0\n", FUNCTION_NAME);
	if (testG.handCount[priorPlayer] == 0){
		asserttrue	(1, 3);
	}
	else{
		asserttrue	(0, 3);
	}
	// ----------- TEST 4: Test that current player is next number -----------
	printf("%s TEST 4: Current player is next after prior player\n", FUNCTION_NAME);
	currentPlayer = whoseTurn(&testG);
	if (currentPlayer == 1){
		asserttrue(1, 4);
	}
	else{
		asserttrue(0, 4);
	}
	// ----------- TEST 5: Test that outpostPlayed is 0 -----------
	printf("%s TEST 5: Number of outpostPlayed is 0\n", FUNCTION_NAME);
	if (testG.outpostPlayed == 0){
		asserttrue(1, 5);
	}
	else{
		asserttrue(0, 5);
	}
	// ----------- TEST 6: Test that phase is 0 -----------
	printf("%s TEST 6: Phase is 0\n", FUNCTION_NAME);
	if (testG.phase == 0){
		asserttrue(1, 6);
	}
	else{
		asserttrue(0, 6);
	}
	// ----------- TEST 7: Test that current player has 1 action -----------
	printf("%s TEST 7: Current player has 1 action\n", FUNCTION_NAME);
	if (testG.numActions == 1){
		asserttrue(1, 7);
	}
	else{
		asserttrue(0, 7);
	}

	// ----------- TEST 8: Test that current player has 1 buy -----------
	printf("%s TEST 8: Current player has 1 buy\n", FUNCTION_NAME);
	if (testG.numBuys == 1){
		asserttrue(1, 8);
	}
	else{
		asserttrue(0, 8);
	}
	// ----------- TEST 9: Test that current player has 0 played cards ----------- 
	printf("%s TEST 9: Current player has played 0 cards\n", FUNCTION_NAME);
	if (testG.playedCardCount == 0){
		asserttrue(1, 9);
	}
	else{
		asserttrue(0, 9);
	}
	// ----------- TEST 10: Test that current player handCount is 5 -----------
	printf("%s TEST 10: Current player has 5 cards in hand\n", FUNCTION_NAME);
	if (testG.handCount[currentPlayer] == 5){
		asserttrue(1, 10);
	}
	else{
		asserttrue(0, 10);
	}
	// ----------- TEST 11: Test that current player's hand is not all -1 -----------
	printf("%s TEST 11: Current player has values that are not -1 for hand\n", FUNCTION_NAME);
	for (i = 0; i < testG.handCount[currentPlayer]; i++){
		if (testG.hand[currentPlayer][i] == -1){
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
	// ----------- TEST 12: Test that currentPlayer has the correct number of coins -----------
	printf("%s TEST 12: Current player has appropriate number of coins\n", FUNCTION_NAME);
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
		asserttrue(1, 12);
	}
	else{
		asserttrue(0, 12);
	}
	// ----------- TEST 13: Test that next player goes back to first player -----------
	printf("%s TEST 13: Next player goes back to first player\n", FUNCTION_NAME);
	i = endTurn(&testG);
	if (whoseTurn(&testG) == 0){
		asserttrue(1, 13);
	}
	else{
		asserttrue(0, 13);
	}
	return 0;
}