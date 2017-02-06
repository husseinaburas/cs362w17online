/*unittest2.c*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define FUNCTION_NAME "buyCard"
/* int buyCard(int supplyPos, struct gameState *state) {
  int who;
  if (DEBUG){
    printf("Entering buyCard...\n");
  }
  who = state->whoseTurn;

  if (state->numBuys < 1){
    if (DEBUG)
      printf("You do not have any buys left\n");
    return -1;
  } else if (supplyCount(supplyPos, state) <1){
    if (DEBUG)
      printf("There are not any of that type of card left\n");
    return -1;
  } else if (state->coins < getCost(supplyPos)){
    if (DEBUG) 
      printf("You do not have enough money to buy that. You have %d coins.\n", state->coins);
    return -1;
  } else {
    state->phase=1;
    //state->supplyCount[supplyPos]--;
    gainCard(supplyPos, state, 0, who); //card goes in discard, this might be wrong.. (2 means goes into hand, 0 goes into discard)
  
    state->coins = (state->coins) - (getCost(supplyPos));
    state->numBuys--;
    if (DEBUG)
      printf("You bought card number %d for %d coins. You now have %d buys and %d coins.\n", supplyPos, getCost(supplyPos), state->numBuys, state->coins);
  }

  //state->discard[who][state->discardCount[who]] = supplyPos;
  //state->discardCount[who]++;
    
  return 0;
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

	preBuys = testG.numBuys;
	preCoins = testG.coins;
	result = buyCard(testCard1, &testG);
	postBuys = testG.numBuys;
	postCoins = testG.coins;
	// verify that buy happened
	if (result == 0){

		// testing only on inputs where buy is successful
		printf("TESTS ON SUCCESSFUL BUY OF SILVER\n");

		// ----------- TEST 1: Test for number of buys for players turn decreases by 1 -----------
	  	printf("%s TEST 1: Number of buys decreases by 1\n", FUNCTION_NAME);
				
		if (preBuys-postBuys == 1){
			asserttrue(1, 1);
		}
		else{
			asserttrue(0, 1);
		}

	//printf("Pre: %d   Post: %d\n", pre, post);

		// ----------- TEST 2: Test that the number of buys does not go negative -----------
		printf("%s TEST 2: Number of buys does not go negative\n", FUNCTION_NAME);
		if (postBuys >= 0){
			asserttrue(1, 2);
		}
		else{
			asserttrue(0, 2);
		}

		// ----------- TEST 3: Test that the number of coins for current player decreased appropriately -----------
		printf("%s TEST 3: Number of coins decreases appropriately\n", FUNCTION_NAME);
		i = getCost(testCard1);
		if (preCoins - postCoins == i){
			asserttrue(1, 3);
		}
		else{
			asserttrue(0, 3);
		}

		// ----------- TEST 4: Test that the current players amount of coins did not go below 0 -----------
		printf("%s TEST 4: Number of coins does not go negative\n", FUNCTION_NAME);
		if (postCoins >= 0){
			asserttrue(1, 4);
		}
		else{
			asserttrue(0, 4);
		}

		// ----------- TEST 5: Test that the total number of cards the player has increases by 1 (sum of all decks) -----------
		printf("%s TEST 5: Total card count for player has increased by 1\n", FUNCTION_NAME);
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
		// ----------- TEST 6: Test that the other player's card count does not change -----------
		printf("%s TEST 6: Other players card count does not change\n", FUNCTION_NAME);
		
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
		
		// ----------- TEST 7: Test that the supply count for bought card decreased by 1 -----------

		printf("%s TEST 7: Supply count for bought card decreases by 1\n", FUNCTION_NAME);
		preCount = G.supplyCount[testCard1];
		postCount = testG.supplyCount[testCard1];
		if (preCount - postCount == 1){
			asserttrue(1, 7);
		}
		else{
			asserttrue(0, 7);
		}

	// ----------- TEST 8: Test that the supply count for bought card did not go below 0 -----------
		printf("%s TEST 8: Supply count for bought card did not go below 0\n", FUNCTION_NAME);
		if (postCount >= 0){
			asserttrue(1, 8);
		}
		else{
			asserttrue(0, 8);
		}
	}
	else{
		printf("Tests 1-8 could not be run due to unsuccessful buy\n");
	}
	// ----------- TEST 9: Test that the function cannot be called if the phase is not 1 -----------

	// ----------- TEST 10: Test that cannot buy a card if number of buys is 0 -----------

	// ----------- TEST 11: Test that cannot buy a card if no cards of that type available -----------

	// ----------- TEST 12: Test that cannot buy a card if player does not have enough money -----------




	return 0;
}
