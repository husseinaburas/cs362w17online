#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Unit test for the adventurer card:
*		int adventurerCard(
*		struct gameState *state,
*		int currentPlayer)
*
*	Need to test functionality at various game states
*	to test full logic of the card
*
*
*
*
*/

//int adventurerCard(struct gameState *state, int currentPlayer)
//{
//	int drawntreasure = 0;
//	int cardDrawn;
//	int z = 0;
//	int temphand[MAX_HAND];
//	while (drawntreasure<4) {
//		if (state->deckCount[currentPlayer] <1) {//if the deck is empty we need to shuffle discard and add to deck
//			shuffle(currentPlayer, state);
//		}
//		drawCard(currentPlayer, state);
//		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];//top card of hand is most recently drawn card.
//		if (cardDrawn == silver || cardDrawn == gold)
//			drawntreasure++;
//		else {
//			temphand[z] = cardDrawn;
//			state->handCount[currentPlayer]++; //this should just remove the top card (the most recently drawn one).
//			z++;
//		}
//	}
//	while (z - 1 >= 0) {
//		state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z - 1]; // discard all cards in play that have been drawn
//		z = z - 1;
//	}
//	return 0;
//}

int main()
{

	printf("-------------------------------------------Testing Card: Adventurer-------------------------------------------------------------------------\n");
	// Initialize variables for pre-conditions 
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
	// Test decks
	int copperDeck[5];
	int silverDeck[5];
	int goldDeck[5];
	int noneDeck[5];
	int emptyDeck[5];

	// Initialize the test decks. All single treasure decks
	// are designed to check that the particualr treasure is flagged 
	// in the adventurerCard routine
	int initDeckCount = G.deckCount[player];
	for (int i = 0; i < initDeckCount; ++i)
		copperDeck[i] = copper;

	for (int i = 0; i < initDeckCount; ++i)
		silverDeck[i] = silver;

	for (int i = 0; i < initDeckCount; ++i)
		goldDeck[i] = gold;

	for (int i = 0; i < initDeckCount; ++i)
		noneDeck[i] = estate; // any non-treasure card

	for (int i = 0; i < initDeckCount; ++i)
		emptyDeck[i] = -1; // no cards left in deck
	
	// First, test all copper deck****
	initHandCount = G.handCount[player];
	for (int i = 0; i < initHandCount; ++i)
		initHand[i] = G.hand[player][i];

	for (int i = 0; i < initDeckCount; ++i)
		G.deck[player][i] = copperDeck[i];

	adventureCheck = adventurerCard(&G, player);
	assert(adventureCheck == 0);
	// Check post-conditions
	printf("-------------------------------------------Test 1: Current Player should have two new coppers from a full copper deck ----------------------------------------------\n");
	// Hand should have 2 new coppers
	assert(G.handCount[player] == initHandCount + 2); // only 2 new cards should be added
	printf("-------------------------------------------Test 2: Last two cards in hand should be copper--------------------------------------------------------------------------\n");
	asssert((G.hand[player][G.handCount[player] - 1] == copper) && (G.hand[player][G.handCount[player] - 2] == copper)); // last two cards in hand should be coppers
	printf("-------------------------------------------Test 3: No cards should be discarded-------------------------------------------------------------------------------------\n");
	assert(G.discard[player] == 0); //no cards should have been discarded

	// Next, re-init and test all silver deck****
	initCheck = initializeGame(numPlayers, k, seed, &G);
	assert(initCheck == 0);

	initHandCount = G.handCount[player];
	for (int i = 0; i < initHandCount; ++i)
		initHand[i] = G.hand[player][i];

	for (int i = 0; i < initDeckCount; ++i)
		G.deck[player][i] = silverDeck[i];

	adventureCheck = adventurerCard(&G, player);
	assert(adventureCheck == 0);
	// Check post-conditions

	printf("-------------------------------------------Test 4: Current Player should have two new silvers from a full silver deck ----------------------------------------------\n");
	// Hand should have 2 new silvers
	assert(G.handCount[player] == initHandCount + 2); // only 2 new cards should be added

	printf("-------------------------------------------Test 5: Last two cards in hand should be silver--------------------------------------------------------------------------\n");
	asssert((G.hand[player][G.handCount[player] - 1] == silver) && (G.hand[player][G.handCount[player] - 2] == silver)); // last two cards in hand should be silvers

	printf("-------------------------------------------Test 6: No cards should be discarded-------------------------------------------------------------------------------------\n");
	assert(G.discard[player] == 0); //no cards should have been discarded


	// Next, re-init and test all gold deck****
	initCheck = initializeGame(numPlayers, k, seed, &G);
	assert(initCheck == 0);

	initHandCount = G.handCount[player];
	for (int i = 0; i < initHandCount; ++i)
		initHand[i] = G.hand[player][i];

	for (int i = 0; i < initDeckCount; ++i)
		G.deck[player][i] = goldDeck[i];

	adventureCheck = adventurerCard(&G, player);
	assert(adventureCheck == 0);
	// Check post-conditions
	
	printf("-------------------------------------------Test 7: Current Player should have two new gold from a full gold deck---------------------------------------------------\n");
	// Hand should have 2 new golds
	assert(G.handCount[player] == initHandCount + 2); // only 2 new cards should be added

	printf("-------------------------------------------Test 8: Last two cards in hand should be gold--------------------------------------------------------------------------\n");
	asssert((G.hand[player][G.handCount[player] - 1] == gold) && (G.hand[player][G.handCount[player] - 2] == gold)); // last two cards in hand should be golds
	
	printf("-------------------------------------------Test 9: No cards should be discarded-----------------------------------------------------------------------------------\n");
	assert(G.discard[player] == 0); //no cards should have been discarded

	// Next, re-init and test no tresaure deck****
	initCheck = initializeGame(numPlayers, k, seed, &G);
	assert(initCheck == 0);

	initHandCount = G.handCount[player];
	for (int i = 0; i < initHandCount; ++i)
		initHand[i] = G.hand[player][i];

	for (int i = 0; i < initDeckCount; ++i)
		G.deck[player][i] = noneDeck[i];

	adventureCheck = adventurerCard(&G, player);
	assert(adventureCheck == 0);
	// Check post-conditions
	
	printf("-------------------------------------------Test 10: Current Player should have no new cards since there are no treasure cards in the deck----------------------------\n");

	// Hand should have no new cards
	assert(G.handCount[player] == initHandCount); // no new cards should be added
	printf("-------------------------------------------Test 11: All cards in the deck should be discarded------------------------------------------------------------------------\n");

	assert(G.discard[player] == initDeckCount); //all cards in deck should have been discarded


	// Check when deck is empty
	initCheck = initializeGame(numPlayers, k, seed, &G);
	assert(initCheck == 0);

	initHandCount = G.handCount[player];
	for (int i = 0; i < initHandCount; ++i)
		initHand[i] = G.hand[player][i];

	for (int i = 0; i < initDeckCount; ++i)
		G.deck[player][i] = emptyDeck[i];

	adventureCheck = adventurerCard(&G, player);
	assert(adventureCheck == 0);
	// Check post-conditions

	printf("-------------------------------------------Test 12: Current Player should have no new cards since there are no cards in the deck----------------------------\n");
	// Hand should have no new cards
	assert(G.handCount[player] == initHandCount); // no new cards should be added


	printf("\n------------------------------------------SUCCESS: TESTING COMPLETE FOR Adventurer CARD-----------------------------------------\n\n");
}