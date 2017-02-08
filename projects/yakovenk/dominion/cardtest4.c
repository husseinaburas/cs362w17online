
//Konstantin Yakovenko
//2k17/02/07
//Unit Test for Great Hall Card implementation cardGreatHall()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
//setup the environment
//initialize the game state to where we could test the function under different game states
	int failFlag = 0;

	//input: (int player, struct gameState *state, int bonus)
	int numPlayers = 2;
	int thisPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, great_hall,
				sea_hag, tribute, smithy, council_room};
	int seed = 1000;

	//vars for keeping track of the relevant changes
	int preCardActionCount, preCardCoinCount, preCardHandCount, preCardDiscardCount, preCardSupplyCount, preCardDeckCount;

	struct gameState G, bkpG;	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	int handPos;

	// backup the game to have a fresh copy
	memcpy(&bkpG, &G, sizeof(struct gameState));

	//run unit tests
	//things we can test: do we draw 3 cards? Do they disappear from the deck? Does the deck get reshuffled?
	printf("\n----------------- Test Card: Great Hall ----------------\n");

	// ----------- TEST 1  --------------
	printf("TEST 1: +1 cards, -greatHall\n");

	G.hand[thisPlayer][0] = great_hall;
	handPos = 0;

	//save state for later comparison
	preCardCoinCount =  G.coins;
	preCardHandCount =  G.handCount[thisPlayer];
	preCardActionCount = G.numActions;
	preCardDiscardCount = G.discardCount[thisPlayer];

	cardGreatHall(handPos, thisPlayer, &G);

	printf("Hand, Actions, Discard should have changed:\n");
	printf("\n\tCoins: pre(%d), post(%d) -- ", preCardCoinCount, G.coins); 
	failFlag += assertTrue(preCardCoinCount ==  G.coins); 
	printf("\n\tHand: pre(%d), post(%d) -- ", preCardHandCount,  G.handCount[thisPlayer]);
	failFlag += assertTrue(preCardHandCount ==  G.handCount[thisPlayer] + 1 - 1); //got 1 new cards but lost great hall.
	printf("\n\tActions: pre(%d), post(%d) -- ", preCardActionCount , G.numActions);
	failFlag += assertTrue(preCardActionCount == G.numActions - 1); //g
	printf("\n\tDiscarded Card into discard pile? pre(%d), post(%d) -- ", preCardDiscardCount , G.discardCount[thisPlayer]);
	failFlag += assertTrue(preCardDiscardCount == G.discardCount[thisPlayer] - 1); //discarded outpost.

	


	// ----------- TEST 2  --------------
	printf("\nTEST 2: Drawing cards that force reshuffling\n");

	// restore the game to a fresh copy
	memcpy(&G, &bkpG, sizeof(struct gameState));

	//setup
	//create a custom deck that forces reshuffling.
	G.hand[thisPlayer][0] = great_hall;
	handPos = 1;

	G.deckCount[thisPlayer] = 0;

	G.discard[thisPlayer][0] = embargo;
	G.discardCount[thisPlayer] = 1;


	//save state for later comparison
	preCardCoinCount =  G.coins;
	preCardHandCount =  G.handCount[thisPlayer];
	preCardDeckCount =  G.deckCount[thisPlayer];

	cardGreatHall(handPos, thisPlayer, &G);

	printf("Only Hand should have changed:\n");
	printf("\n\tCoins: pre(%d), post(%d) -- ", preCardCoinCount, G.coins); 
	failFlag += assertTrue(preCardCoinCount ==  G.coins); 
	printf("\n\tHand: pre(%d), post(%d) -- ", preCardHandCount,  G.handCount[thisPlayer]);
	failFlag += assertTrue(preCardHandCount ==  G.handCount[thisPlayer] - 1 + 1); //got 3 new cards. Lost Smithy
	printf("\n\tDeck: pre(%d), post(%d) -- ", preCardDeckCount,  G.deckCount[thisPlayer]);
	failFlag += assertTrue(preCardDeckCount ==  G.deckCount[thisPlayer] + 1 - 1);//3 drawn, 1 shuffled


	printf("\nThe most recent card in hand as expected?  -- ");
	failFlag += assertTrue(G.hand[thisPlayer][G.handCount[thisPlayer] - 1] == embargo);


	printf("\n UNIT TESTS for cardGreatHall(): ");
	assertTrue(failFlag == 0);
	printf("\n");
	

	return 0;
}
