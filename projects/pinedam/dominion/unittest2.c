/* 
* untittest2.c
*/
/*Unit test for method:
*	buyCard(
*	int supplyPos, 
*	struct gameState *state)
*
*	Requirements of buyCard:
*
*
*
*
*
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//int buyCard(int supplyPos, struct gameState *state) {
//	int who;
//	if (DEBUG) {
//		printf("Entering buyCard...\n");
//	}
//
//	// I don't know what to do about the phase thing.
//
//	who = state->whoseTurn;
//
//	if (state->numBuys < 1) {
//		if (DEBUG)
//			printf("You do not have any buys left\n");
//		return -1;
//	}
//	else if (supplyCount(supplyPos, state) <1) {
//		if (DEBUG)
//			printf("There are not any of that type of card left\n");
//		return -1;
//	}
//	else if (state->coins < getCost(supplyPos)) {
//		if (DEBUG)
//			printf("You do not have enough money to buy that. You have %d coins.\n", state->coins);
//		return -1;
//	}
//	else {
//		state->phase = 1;
//		//state->supplyCount[supplyPos]--;
//		gainCard(supplyPos, state, 0, who); //card goes in discard, this might be wrong.. (2 means goes into hand, 0 goes into discard)
//
//		state->coins = (state->coins) - (getCost(supplyPos));
//		state->numBuys--;
//		if (DEBUG)
//			printf("You bought card number %d for %d coins. You now have %d buys and %d coins.\n", supplyPos, getCost(supplyPos), state->numBuys, state->coins);
//	}
//
//	//state->discard[who][state->discardCount[who]] = supplyPos;
//	//state->discardCount[who]++;
//
//	return 0;
//}


int main()
{
	printf("-------------------------------------------Testing Funtion: buyCard-----------------------------------------\n");
	// Initialize required variables for pre-conditions
	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int numPlayers = 2;
	int seed = 1234;
	int buyCardCheck;
	int initCheck = initializeGame(numPlayers, k, seed, &G);
	assert(initCheck == 0);
	
	//set player 
	int player = 0;
	
	//save the number of card in the discard pile
	int initPlayerDiscard = G.discardCount[player];
	
	// save the initial supply of the card we will try to buy 
	int initsupply = G.supplyCount[smithy];

	//save the number of buys this player has 
	int initNumBuy = G.numBuys;
	
	//set whose turn it is to player 1 
	G.whoseTurn = 0;


	printf("------------------------------------------Test 1: numBuys=0-----------------------------------------\n");
	//set the numbuys to zero
	G.numBuys = 0;
	//check to see if numbuys fails if it is 0
	buyCardCheck= buyCard(village, &G);
	assert(buyCardCheck != 0);
	
	printf("------------------------------------------Test 2: Buying a nonexistent card-----------------------------------------\n");
	//reset the number of buys 
	G.numBuys = 1;	
	// check if you can buy a non existent card
	buyCardCheck = buyCard(remodel, &G);
	assert(buyCardCheck != 0);
	//check that number of buys doesn't go down 
	assert(G.numBuys == initNumBuy);
	
	printf("------------------------------------------Test 3: coins=0-----------------------------------------\n");
	//set coins to 0
	G.coins = 0;
	buyCardCheck = buyCard(adventurer, &G);
	assert(buyCardCheck != 0); 
	//check that number of buys doesn't go down 
	assert(G.numBuys == initNumBuy);
	
	printf("------------------------------------------Test 4: Valid buy-----------------------------------------\n");
	//check for post conditions during a valid buy
	G.coins = 4;
	buyCardCheck = buyCard(smithy, &G);
	assert(buyCardCheck = 0);
	
	printf("------------------------------------------Test 4.1: Discard increases with new card in a Valid buy-----------------------------------------\n");
	//check that the new card was discarded 
	assert(G.discardCount[player] == initPlayerDiscard + 1);

	printf("------------------------------------------Test 4.2: Supply decreases in a Valid buy-----------------------------------------\n");
	//check that the supply of smithy went down
	assert(G.supplyCount[smithy] == initsupply - 1);

	printf("------------------------------------------Test 4.3: numBuys gets decreased in a Valid buy-----------------------------------------\n");
	//check that number of buys goes down after it buys 
	assert(G.numBuys == initNumBuy - 1);
	printf("\n------------------------------------------SUCCESS: TESTING COMPLETE FOR buyCard FUNCTION-----------------------------------------\n\n");
}