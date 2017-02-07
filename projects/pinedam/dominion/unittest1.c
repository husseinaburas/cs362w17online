/*
* unittest1.c
*/
/* Unit test for method: 
 *		int gainCard(
 *		int supplyPos, 
 *		struct gameState *state, 
 *		int toFlag, 
 *		int player)
 *
 *	Requirements of gainCard:
 *	1. non exitent card can not be gained to the players deck
 *	2. The discard pile should gain a card 
 *	3. The players Deck should gain a card
 *	4. The Players hand should gain a card
 *	5. The supply of the choosen card should decrease
 *
 */

 // Reference for toFlag values
 // toFlag = 0 : add to discard
 // toFlag = 1 : add to deck
 // toFlag = 2 : add to hand

//int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
//{
//	//Note: supplyPos is enum of choosen card
//
//	//check if supply pile is empty (0) or card is not used in game (-1)
//	if (supplyCount(supplyPos, state) < 1)
//	{
//		return -1;
//	}
//
//	//added card for [whoseTurn] current player:
//	// toFlag = 0 : add to discard
//	// toFlag = 1 : add to deck
//	// toFlag = 2 : add to hand
//
//	if (toFlag == 1)
//	{
//		state->deck[player][state->deckCount[player]] = supplyPos;
//		state->deckCount[player]++;
//	}
//	else if (toFlag == 2)
//	{
//		state->hand[player][state->handCount[player]] = supplyPos;
//		state->handCount[player]++;
//	}
//	else
//	{
//		state->discard[player][state->discardCount[player]] = supplyPos;
//		state->discardCount[player]++;
//	}
//
//	//decrease number in supply pile
//	state->supplyCount[supplyPos]--;
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
	printf("-------------------------------------------Testing Funtion: gainCard-----------------------------------------\n");
	// Initialize required variables for pre-conditions
	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy };
	int numPlayers = 2;
	int seed = 1234;

	int initCheck = initializeGame(numPlayers, k, seed, &G);
	assert(initCheck == 0);

	int* toFlag[3];
	for (int i = 0; i < 3; i++)
		toFlag[i] = i;
	int player = 0;
	int initPlayerDeckCount = G.deckCount[player];
	int initPlayerHandCount = G.handCount[player];
	int initVillageSupply = G.supplyCount[village];

	// begin running various tests and checking post-conditions
	int gainCardCheck;

	printf("------------------------------------------Test 1: That a card NOT in the game cannot be gained----------------------------------------\n");
	//test that a card NOT in the game cannot be gained
	gainCardCheck = gainCard(steward, &G, toFlag[0], player);
	assert(gainCardCheck != 0);
	printf("------------------------------------------Test 2: That the players discard pile gained a card----------------------------------------\n");
	//test the player discard pile gaining a card
	int gainCardCheck = gainCard(village, &G, toFlag[0], player);
	assert(gainCardCheck == 0);

	assert(G.discard[player][G.discardCount[player] - 1] == village);
	assert(G.discardCount[player] == 1);

	printf("------------------------------------------Test 3: That the players deck gained a card----------------------------------------\n");
	//test the player deck gaining a card
	int gainCardCheck = gainCard(village, &G, toFlag[1], player);
	assert(gainCardCheck == 0);

	assert(G.deck[player][G.deckCount[player] - 1] == village);
	assert(G.deckCount[player] == initPlayerDeckCount + 1);

	printf("------------------------------------------Test 4: That the players hand gained a card----------------------------------------\n");
	//test the player hand gaining a card
	int gainCardCheck = gainCard(village, &G, toFlag[2], player);
	assert(gainCardCheck == 0);

	assert(G.hand[player][G.handCount[player] - 1] == village);
	assert(G.handCount[player] == initPlayerHandCount + 1);

	printf("------------------------------------------Test 5: That the supply count is correct----------------------------------------\n");
	//Three village cards were taken from supply
	//so check to make sure correct number have been taken
	assert(G.supplyCount[village] == initVillageSupply - 3);
	printf("\n------------------------------------------SUCCESS: TESTING COMPLETE FOR gainCard FUNCTION-----------------------------------------\n\n");
}