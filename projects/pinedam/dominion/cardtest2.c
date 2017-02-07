#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Unit test for the Smithy card:
*		int smithyCard(
*		struct gameState *state,
*		int handPos,
*		int currentPlayer)
*		
*	Need to test functionality at various game states
*	to test full logic of the card
*
*	Requirements of the Smithy Card:
*	1. Current player should receive exact 3 cards.
*	2. 3 cards should come from his own pile.
*	3. No state change should occur for other players.
*	4. No state change should occur to the victory card piles and kingdom card piles.
*
*/

//int smithyCard(struct gameState *state, int handPos, int currentPlayer)
//{
//	int i = 1;
//	//+3 Cards
//	for (i = 0; i < 3; i++)
//	{
//		drawCard(currentPlayer, state);
//	}
//
//	//discard card from hand
//	discardCard(handPos, currentPlayer, state, 0);
//	return 0;
//
//}

int main()
{
	// Initialize variables for pre-conditions 
	printf("-------------------------------------------Testing Card: Smithy-----------------------------------------\n");

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
	int smithyCheck;
	int smithyHand[5];
	int inithandCountPlayer2 = G.handCount[1];
	int initdeckCountPlayer2 = G.deckCount[1];
	int initdiscardPlayer2 = G.discardCount[1];
	int kingdomCount[10];
	int initKingdomCount[10];
	int initvictoryCount[3];
	int victoryCount[3];
	int v[3] = { estate , duchy, province };

	// save the number of each kingdom cards 
	for (int i=0; i < 10; i++)
	{
		initKingdomCount[i] = G.supplyCount[k[i]];
		
	}
	// save the number of victory cards
	for (int i=0; i < 3; i++)
	{
		initvictoryCount[i] = G.supplyCount[v[i]];

	}

	// create a hand full of smithy's 
	int inithandcount = G.handCount[player];
	for (int i = 0; i < inithandcount; ++i)
		smithyHand[i] = smithy;
	printf("-------------------------------------------Test 1: Current player should receive exact 3 cards. ----------------------------------------------\n");
	// test that the player recieved exactly 3 cards
	smithyCheck = smithyCard(&G, 0, player);
		assert(smithyCheck == 0);//check that smithy ran ok
		assert(G.handCount[player] == initDeckCount + 2);//check the player recieved the 3 new cards and discarded the smithy
		
		printf("-------------------------------------------Test 2: 3 cards should come from the playerws own pile. ------------------------------------------\n");

		assert(G.deckCount[player] == initDeckCount - 3); // check that the 3 cards came from the players deck

		printf("-------------------------------------------Test 3: No state change should occur for other players. -----------------------------------------\n");
		assert(inithandCountPlayer2 == G.handCount[1]);//checking other players hand 
		assert(initdeckCountPlayer2 == G.deckCount[1]);//checking other players deck
		assert(initdiscardPlayer2 == G.discardCount[1]); //checking other players discard

		printf("-------------------------------------------Test 4: No state change should occur to the kingdom card piles. ------------\n");
		
		for (int i=0; i < 10; i++)
		{
			kingdomCount[i] = G.supplyCount[k[i]];
			assert(kingdomCount[i] == initKingdomCount[i]);
		}
		
		printf("-------------------------------------------Test 5: No state change should occur to the Victory card piles. ------------\n");

		
		for (int i=0; i < 10; i++)
		{
			victoryCount[i] = G.supplyCount[v[i]];
			assert(victoryCount[i] == initvictoryCount[i]);
		}

printf("\n------------------------------------------SUCCESS: TESTING COMPLETE FOR Smithy CARD-----------------------------------------\n\n");

}