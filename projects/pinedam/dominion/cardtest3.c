#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Unit test for the village card:
*		    case village:
      //+1 Card
      drawCard(currentPlayer, state);
			
      //+2 Actions
      state->numActions = state->numActions + 2;
			
      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;

*	Requirements of the Village Card:
*	1. Current player should receive exact 1 card.
*	2. 1 cards should come from the players own pile.
*	3. No state change should occur for other players.
*	4. No state change should occur to the victory card piles and kingdom card piles.
*	5. Current  player should recieve 2 more actions 
*	6. discard should increase
*
*
*/

int main()
{
	// Initialize variables for pre-conditions 
	printf("-------------------------------------------Testing Card: Village-----------------------------------------\n");
	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int numPlayers = 2;
	int seed = 1234;
	int initCheck = initializeGame(numPlayers, k, seed, &G);
	assert(initCheck == 0);
	int	player = 0;
	int initHandCount = G.handCount[player];
	int initDeckCount = G.deckCount[player];
	int villageCheck;
	int villageHand[5];
	int inithandCountPlayer2 = G.handCount[1];
	int initdeckCountPlayer2 = G.deckCount[1];
	int initdiscardPlayer2 = G.discardCount[1];
	int kingdomCount[10];
	int initKingdomCount[10];
	int initvictoryCount[3];
	int victoryCount[3];
	int initNumActions;
	int v[3] = { estate , duchy, province };
	

	//save the discard count 
	int initDiscardCount = G.discardCount;
	//save number of actions 
	initNumActions = G.numActions;
	// save the number of each kingdom cards 
	for (int i = 0; i < 10; i++)
	{
		initKingdomCount[i] = G.supplyCount[k[i]];

	}
	// save the number of victory cards
	for (int i = 0; i < 3; i++)
	{
		initvictoryCount[i] = G.supplyCount[v[i]];

	}

	// create a hand full of village's 
	int inithandcount = G.handCount[player];
	for (int i = 0; i < inithandcount; ++i)
		villageHand[i] = village;
	printf("-------------------------------------------Test 1: Current player should receive exact 1 card. ----------------------------------------------\n");
	// test that the player recieved exactly 1 cards
	villageCheck = cardEffect(village, 0, 0, 0, &G, 1, 0);
	assert(villageCheck == 0);//check that smithy ran ok
	assert(G.handCount[player] == initDeckCount);//check the player recieved the 1 new cards and discarded the village

	printf("-------------------------------------------Test 2: 1 card should come from the playerws own pile. ------------------------------------------\n");

	assert(G.deckCount[player] == initDeckCount - 1); // check that the 1 cards came from the players deck

	printf("-------------------------------------------Test 3: No state change should occur for other players. -----------------------------------------\n");
	assert(inithandCountPlayer2 == G.handCount[1]);//checking other players hand 
	assert(initdeckCountPlayer2 == G.deckCount[1]);//checking other players deck
	assert(initdiscardPlayer2 == G.discardCount[1]); //checking other players discard

	printf("-------------------------------------------Test 4: No state change should occur to the kingdom card piles. ------------\n");
	for (int i = 0; i < 10; i++)// checking the kingdom cards havent changed 
	{
		kingdomCount[i] = G.supplyCount[k[i]];
		assert(kingdomCount[i] == initKingdomCount[i]);
	}

	printf("-------------------------------------------Test 5: No state change should occur to the Victory card piles. ------------\n");
	for (int i = 0; i < 10; i++)//checking the victory cards havent changed
	{
		victoryCount[i] = G.supplyCount[v[i]];
		assert(victoryCount[i] == initvictoryCount[i]);
	}
	printf("-------------------------------------------Test 6: Number of Actions goes up by 2. ------------\n");
	assert(initNumActions + 1 == G.numActions);//checking that actions go up by 2

	printf("-------------------------------------------Test 7: Number of discards goes up by 1. ------------\n");
	assert( initDiscardCount + 1== G.discardCount);// discard goes up by 1 

	printf("\n------------------------------------------SUCCESS: TESTING COMPLETE FOR Village CARD-----------------------------------------\n\n");


}