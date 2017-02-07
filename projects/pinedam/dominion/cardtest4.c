#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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


	//save the discard count 
	int initDiscardCount = G.discardCount;
	//save number of actions 
	initNumbuys = G.numBuys;
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

	// create a hand full of council Room's 
	int inithandcount = G.handCount[player];
	for (int i = 0; i < inithandcount; ++i)
		councilRoomHand[i] = council_room;
	printf("-------------------------------------------Test 1: Current player should receive exact 4 card. ----------------------------------------------\n");
	// test that the player recieved exactly 1 cards
	councilRoomCheck = cardEffect(council_room, 0, 0, 0, &G, 1, 0);
	assert(councilRoomCheck == 0);//check that smithy ran ok
	assert(G.handCount[player] == initDeckCount +3 );//check the player recieved the 3 new cards and discarded the council room

	printf("-------------------------------------------Test 2: 4 card should come from the players own pile. ------------------------------------------\n");

	assert(G.deckCount[player] == initDeckCount - 4); // check that the 4 cards came from the players deck
	
	printf("-------------------------------------------Test 3: Number of discards goes up by 1. ------------\n");
	assert(initDiscardCount + 1 == G.discardCount);// discard goes up by 1 

	printf("-------------------------------------------Test 4: No state change should occur for other players. -----------------------------------------\n");
	assert(inithandCountPlayer2 == G.handCount[1]);//checking other players hand 
	assert(initdeckCountPlayer2 == G.deckCount[1]);//checking other players deck
	assert(initdiscardPlayer2 == G.discardCount[1]); //checking other players discard

	printf("-------------------------------------------Test 5: No state change should occur to the kingdom card piles. ------------\n");
	for (int i = 0; i < 10; i++)// checking the kingdom cards havent changed 
	{
		kingdomCount[i] = G.supplyCount[k[i]];
		assert(kingdomCount[i] == initKingdomCount[i]);
	}

	printf("-------------------------------------------Test 6: No state change should occur to the Victory card piles. ------------\n");
	for (int i = 0; i < 10; i++)//checking the victory cards havent changed
	{
		victoryCount[i] = G.supplyCount[v[i]];
		assert(victoryCount[i] == initvictoryCount[i]);
	}
	printf("-------------------------------------------Test 7: Number of Actions goes up by 2. ------------\n");
	assert(initNumbuys+1 == G.numBuys);//checking that actions go up by 1


	printf("\n------------------------------------------SUCCESS: TESTING COMPLETE FOR Council Room CARD-----------------------------------------\n\n");

	
}




