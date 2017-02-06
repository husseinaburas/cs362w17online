/*
* unittest4.c
*/
/* Unit test for method:
*		int updateCoins( 
*		int player,
*		struct gameState *state
*		int bonus)
*/
//int updateCoins(int player, struct gameState *state, int bonus)
//{
//	int i;
//
//	//reset coin count
//	state->coins = 0;
//
//	//add coins for each Treasure card in player's hand
//	for (i = 0; i < state->handCount[player]; i++)
//	{
//		if (state->hand[player][i] == copper)
//		{
//			state->coins += 1;
//		}
//		else if (state->hand[player][i] == silver)
//		{
//			state->coins += 2;
//		}
//		else if (state->hand[player][i] == gold)
//		{
//			state->coins += 3;
//		}
//	}
//
//	//add bonus
//	state->coins += bonus;
//
//	return 0;
//}


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main()
{

	printf("-------------------------------------------Testing Funtion: updateCoins-----------------------------------------\n");
	// Initialize required variables for pre-conditions
	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int numPlayers = 2;
	int seed = 1234;

	int initCheck = initializeGame(numPlayers, k, seed, &G);
	assert(initCheck == 0);
	int player = 0;
	int adventureCheck;
	int initHand[MAX_HAND];
	int initHandCount;
	// Test hands
	int copperHand[5];
	int silverHand[5];
	int goldHand[5];
	int nonTreasureHand[5];
	int updatecoinsCheck;
	int coinCheck;

	// Initialize the test hands. All single treasure hands
	// 
	int inithandcount = G.handCount[player];
	for (int i = 0; i < inithandcount; ++i)
		copperHand[i] = copper;

	for (int i = 0; i < inithandcount; ++i)
		silverHand[i] = silver;

	for (int i = 0; i < inithandcount; ++i)
		goldHand[i] = gold;

	for (int i = 0; i < inithandcount; ++i)
		nonTreasureHand[i] = estate; // any non-treasure card
	
	printf("------------------------------------------Test 1: Hand full of coppers sets coins to the handCount----------------------------------------\n");
	//test that a card NOT in the game cannot be gained
	//set the current hand to all copper
	for (int i = 0; i < inithandcount; ++i)
		G.hand[player][i] = copperHand[i];
	//check if update coin runs 
	updatecoinsCheck = updateCoins(player, &G, 0);
	assert(updatecoinsCheck == 0);
	
	//check if coin is equal to the whole copper hand 
	coinCheck = G.coins;
	assert(coinCheck == inithandcount*1);
	
	printf("------------------------------------------Test 2: Hand full of silvers sets coins to the handCount*2----------------------------------------\n");
	//set the current hand to all silver
	for (int i = 0; i < inithandcount; ++i)
		G.hand[player][i] = silverHand[i];
	//check if update coin runs 
	updatecoinsCheck = updateCoins(player, &G, 0);
	assert(updatecoinsCheck == 0);

	//check if coin is equal to the whole silver hand 
	coinCheck = G.coins;
	assert(coinCheck == inithandcount * 2);
	
	printf("------------------------------------------Test 3: Hand full of gold sets coins to the handCount*3----------------------------------------\n");
	//set the current hand to all gold
	for (int i = 0; i < inithandcount; ++i)
		G.hand[player][i] = goldHand[i];
	//check if update coin runs 
	updatecoinsCheck = updateCoins(player, &G, 0);
	assert(updatecoinsCheck == 0);

	//check if coin is equal to the whole gold hand 
	coinCheck = G.coins;
	assert(coinCheck == inithandcount * 3);
	
	printf("------------------------------------------Test 1: Hand with no treasure sets coins to 0 ----------------------------------------\n");
	//set the current hand to the no treasure hand 
	for (int i = 0; i < inithandcount; ++i)
		G.hand[player][i] = nonTreasureHand[i];
	//check if update coin runs 
	updatecoinsCheck = updateCoins(player, &G, 0);
	assert(updatecoinsCheck == 0);

	//check if coin is equal to the no treasure hand 
	coinCheck = G.coins;
	assert(coinCheck == inithandcount * 0);
	printf("\n------------------------------------------SUCCESS: TESTING COMPLETE FOR updateCoins FUNCTION-----------------------------------------\n\n");
}