#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "assert.h"

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

int assertTrue(int actual, int expected, int isEqual)
{
	if (isEqual)
	{
		if (actual == expected)
			return 0;
		else
		{
			printf("****Error in current test******\n");
			return -1;
		}
	}
	else
	{
		if (actual != expected)
			return 0;
		else
		{
			printf("****Error in current test******\n");
			return -1;
		}
	}

}

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
	G.whoseTurn = player;
	int v[3] = { estate , duchy, province };
	int i;

	//save the discard count 
	int initDiscardCount = G.discardCount[player];
	//save number of actions 
	initNumActions = G.numActions;
	// save the number of each kingdom cards 
	for ( i = 0; i < 10; i++)
	{
		initKingdomCount[i] = G.supplyCount[k[i]];
	}
	// save the number of victory cards
	for ( i = 0; i < 3; i++)
	{
		initvictoryCount[i] = G.supplyCount[v[i]];
	}

	// create a hand full of village's 
	int inithandcount = G.handCount[player];
	for ( i = 0; i < inithandcount; ++i)
		villageHand[i] = village;


	printf("-------------------------------------------Test 1.0: Current player should receive exact 1 card. ----------------------------------------------\n");
	// test that the player recieved exactly 1 cards
	villageCheck = cardEffect(village, 0, 0, 0, &G, 1, 0);
	assertTrue(villageCheck, 0, 1);//check that smithy ran ok
	assertTrue(G.handCount[player], initDeckCount, 1);//check the player recieved the 1 new cards and discarded the village

	printf("-------------------------------------------Test 1.1: 1 card should come from the playerws own pile. ------------------------------------------\n");

	assertTrue(G.deckCount[player], initDeckCount - 1, 1); // check that the 1 cards came from the players deck

	printf("-------------------------------------------Test 1.2: No state change should occur for other players. -----------------------------------------\n");
	assertTrue(inithandCountPlayer2, G.handCount[1], 1);//checking other players hand 
	assertTrue(initdeckCountPlayer2, G.deckCount[1], 1);//checking other players deck
	assertTrue(initdiscardPlayer2, G.discardCount[1], 1); //checking other players discard

	printf("-------------------------------------------Test 1.3: No state change should occur to the kingdom card piles. ------------\n");
	for (i = 0; i < 10; i++)// checking the kingdom cards havent changed 
	{
		kingdomCount[i] = G.supplyCount[k[i]];
		assertTrue(kingdomCount[i], initKingdomCount[i], 1);
	}

	printf("-------------------------------------------Test 1.4: No state change should occur to the Victory card piles. ------------\n");
	for ( i = 0; i < 3; i++)//checking the victory cards havent changed
	{
		victoryCount[i] = G.supplyCount[v[i]];
		assertTrue(victoryCount[i], initvictoryCount[i], 1);
	}
	printf("-------------------------------------------Test 1.5: Number of Actions goes up by 2. ------------\n");
	assertTrue(initNumActions + 2, G.numActions, 1);//checking that actions go up by 2

	printf("-------------------------------------------Test 1.6: Number of played cards goes up by 1. ------------\n");
	assertTrue(G.playedCardCount, 1, 1);// discard goes up by 1 

	printf("\n------------------------------------------SUCCESS: TESTING COMPLETE FOR Village CARD-----------------------------------------\n\n");

	return 0;
}