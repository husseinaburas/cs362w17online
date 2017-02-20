
//Konstantin Yakovenko
//2k17/02/07
//Unit Test for Smithy Card implementation cardSmithy()

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
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
				sea_hag, tribute, smithy, council_room};
	int seed = 1000;

	//vars for keeping track of the relevant changes
	int preCardNumBuys, preCardCoinCount, preCardHandCount, preCardDiscardCount, preCardSupplyCount, preCardDeckCount;

	struct gameState G, bkpG;	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	int handPos;

	// backup the game to have a fresh copy
	memcpy(&bkpG, &G, sizeof(struct gameState));

	//run unit tests
	//things we can test: do we draw 3 cards? Do they disappear from the deck? Does the deck get reshuffled?
	printf("\n----------------- Test Card: Smithy ----------------\n");

	// ----------- TEST 1  --------------
	printf("TEST 1: +3 cards - Smithy\n");

	G.hand[thisPlayer][0] = smithy;
	handPos = 0;

	//save state for later comparison
	preCardCoinCount =  G.coins;
	preCardHandCount =  G.handCount[thisPlayer];

	cardSmithy(handPos, thisPlayer, &G);

	printf("Only Hand should have changed:\n");
	printf("\n\tCoins: pre(%d), post(%d) -- ", preCardCoinCount, G.coins); 
	failFlag += assertTrue(preCardCoinCount ==  G.coins); 
	printf("\n\tHand: pre(%d), post(%d) -- ", preCardHandCount,  G.handCount[thisPlayer]);
	failFlag += assertTrue(preCardHandCount ==  G.handCount[thisPlayer] + 3 - 1); //got 3 new cards but lost smithy.
	


	// ----------- TEST 2  --------------
	printf("\nTEST 2: Drawing cards that force reshuffling\n");

	// restore the game to a fresh copy
	memcpy(&G, &bkpG, sizeof(struct gameState));

	//setup
	//create a custom deck that forces reshuffling.
	G.hand[thisPlayer][0] = smithy;
	handPos = 0;

	G.deck[thisPlayer][0] = steward;
	G.deck[thisPlayer][1] = copper;
	G.deckCount[thisPlayer] = 2;

	G.discard[thisPlayer][0] = embargo;
	G.discardCount[thisPlayer] = 1;


	//save state for later comparison
	preCardCoinCount =  G.coins;
	preCardHandCount =  G.handCount[thisPlayer];
	preCardDeckCount =  G.deckCount[thisPlayer];

	cardSmithy(handPos, thisPlayer, &G);

	printf("Only Hand should have changed:\n");
	printf("\n\tCoins: pre(%d), post(%d) -- ", preCardCoinCount, G.coins); 
	failFlag += assertTrue(preCardCoinCount ==  G.coins); 
	printf("\n\tHand: pre(%d), post(%d) -- ", preCardHandCount,  G.handCount[thisPlayer]);
	failFlag += assertTrue(preCardHandCount ==  G.handCount[thisPlayer] - 3 + 1); //got 3 new cards. Lost Smithy
	printf("\n\tDeck: pre(%d), post(%d) -- ", preCardDeckCount,  G.deckCount[thisPlayer]);
	failFlag += assertTrue(preCardDeckCount ==  G.deckCount[thisPlayer] + 3 - 1);//3 drawn, 1 shuffled


	printf("\nFirst card is copper as planned from deck  -- ");
	failFlag += assertTrue(G.hand[thisPlayer][G.handCount[thisPlayer] - 3] == copper);
	printf("\nSecond card is steward as planned from deck  -- ");
	failFlag += assertTrue(G.hand[thisPlayer][G.handCount[thisPlayer] - 2] == steward);
	printf("\nThird card is embargo as planned from reshuffle  -- ");
	failFlag += assertTrue(G.hand[thisPlayer][G.handCount[thisPlayer] - 1] == embargo);


	printf("\n UNIT TESTS for cardSmithy(): ");
	assertTrue(failFlag == 0);
	printf("\n");
	

	return 0;
}
