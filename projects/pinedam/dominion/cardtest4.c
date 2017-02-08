#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "assert.h"

/* Unit test for the Councilroom card:
*
*case council_room:
*     //+4 Cards
*      for (i = 0; i < 4; i++)
*	{
*	  drawCard(currentPlayer, state);
*	}
*      //+1 Buy
*     state->numBuys++;
*      //Each other player draws a card
*     for (i = 0; i < state->numPlayers; i++)
*	{
*	  if ( i != currentPlayer )
*	    {
*	      drawCard(i, state);
*	    }
*	}
*     //put played card in played card pile
*     discardCard(handPos, currentPlayer, state, 0);			
*      return 0;
*
*	Requirements of the Council Room Card:
*	1. Current player should receive exact 4 card.
*	2. 4 cards should come from the players own pile.
*	3. Discard should increase by 1.
*	4. No state change should occur for other players.
*	5. No state change should occur to the victory card piles 
*	6. No state change should occur to the kingdom card piles.
*	7. Current  player should recieve 1 more buy
*
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
	printf("-------------------------------------------Testing Card: Council Room-----------------------------------------\n");
	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		council_room, tribute, smithy };
	int numPlayers = 2;
	int seed = 1234;
	int initCheck = initializeGame(numPlayers, k, seed, &G);
	assert(initCheck == 0);
	int	player = 0;
	G.whoseTurn = player;
	int initHandCount = G.handCount[player];
	int initDeckCount = G.deckCount[player];
	int councilRoomCheck;
	int councilRoomHand[5];
	int inithandCountPlayer2 = G.handCount[1];
	int initdeckCountPlayer2 = G.deckCount[1];
	int initdiscardPlayer2 = G.discardCount[1];
	int kingdomCount[10];
	int initKingdomCount[10];
	int initvictoryCount[3];
	int victoryCount[3];
	int initNumbuys;
	int v[3] = { estate , duchy, province };
	int i;

	//save the discard count 
	int initDiscardCount = G.discardCount;
	//save number of actions 
	initNumbuys = G.numBuys;
	// save the number of each kingdom cards 
	for ( i = 0; i < 10; i++)
	{
		initKingdomCount[i] = G.supplyCount[k[i]];

	}
	// save the number of victory cards
	for (i = 0; i < 3; i++)
	{
		initvictoryCount[i] = G.supplyCount[v[i]];

	}

	// create a hand full of council Room's 
	int inithandcount = G.handCount[player];
	for ( i = 0; i < inithandcount; ++i)
		councilRoomHand[i] = council_room;
	printf("-------------------------------------------Test 1.0: Current player should receive exact 4 card. ----------------------------------------------\n");
	// test that the player recieved exactly 1 cards
	councilRoomCheck = cardEffect(council_room, 0, 0, 0, &G, 1, 0);
	assertTrue(councilRoomCheck, 0, 1);//check that smithy ran ok
	assertTrue(G.handCount[player], initDeckCount +3, 1);//check the player recieved the 3 new cards and discarded the council room

	printf("-------------------------------------------Test 1.1: 4 card should come from the players own pile. ------------------------------------------\n");

	assertTrue(G.deckCount[player], initDeckCount - 4, 1); // check that the 4 cards came from the players deck
	
	printf("-------------------------------------------Test 1.2: Number of discards goes up by 1. ------------\n");
	assertTrue(G.playedCardCount, 1, 1);// played goes up by 1 

	printf("-------------------------------------------Test 1.3: Other players should have exactly 1 more card in hand and 1 less in deck. -----------------------------------------\n");
	assertTrue(inithandCountPlayer2 + 1, G.handCount[1], 1);//checking other players hand 
	assertTrue(initdeckCountPlayer2 - 1, G.deckCount[1], 1);//checking other players deck
	assertTrue(initdiscardPlayer2, G.discardCount[1], 1); //checking other players discard

	printf("-------------------------------------------Test 1.4: No state change should occur to the kingdom card piles. ------------\n");
	for ( i = 0; i < 10; i++)// checking the kingdom cards havent changed 
	{
		kingdomCount[i] = G.supplyCount[k[i]];
		assertTrue(kingdomCount[i], initKingdomCount[i], 1);
	}

	printf("-------------------------------------------Test 1.5: No state change should occur to the Victory card piles. ------------\n");
	for ( i = 0; i < 3; i++)//checking the victory cards havent changed
	{
		victoryCount[i] = G.supplyCount[v[i]];
		assertTrue(victoryCount[i], initvictoryCount[i], 1);
	}
	printf("-------------------------------------------Test 1.6: Number of Actions goes up by 2. ------------\n");
	assertTrue(initNumbuys+1, G.numBuys , 1);//checking that actions go up by 1


	printf("\n------------------------------------------SUCCESS: TESTING COMPLETE FOR Council Room CARD-----------------------------------------\n\n");

	return 0;
}




