
//Konstantin Yakovenko
//2k17/02/07
//Unit Test for gainCard()

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
	int toDiscard = 0;
	int toDeck = 1;
	int toHand = 2;


	//input: (int player, struct gameState *state, int bonus)
	int numPlayers = 2;
	int thisPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
				sea_hag, tribute, smithy, council_room};
	int seed = 1000;

	//vars for keeping track of the relevant changes
	int preGainDiscardCount, preGainDeckCount, preGainHandCount, preGainSupplyCount;

	struct gameState G;	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);


	//run unit tests
	//things we can test: card not being in the game, discard goes to discard, 
	//deck goes to deck, hand goes to hand, supply changes if gained.
	//
	printf("\n----------------- Test Function: gainCard() ----------------\n");

	// ----------- TEST 1  --------------
	printf("TEST 1: card running out\n");

	//empty supply for testing
	G.supplyCount[1] = 0;

	//same 1 as right above 
	preGainDiscardCount =  G.discardCount[thisPlayer];
	preGainDeckCount =  G.deckCount[thisPlayer];
	preGainHandCount =  G.handCount[thisPlayer];
	preGainSupplyCount =  G.supplyCount[1];

	gainCard(1 , &G, toHand, thisPlayer);

	printf("Player cards shouldn't have changed:\n");
	printf("\tDiscard: pre(%d), post(%d) -- ", preGainDiscardCount , G.discardCount[thisPlayer]); 
	failFlag += assertTrue(preGainDiscardCount == G.discardCount[thisPlayer]);
	printf("\n\tHand: pre(%d), post(%d) -- ", preGainHandCount , G.handCount[thisPlayer]); 
	failFlag += assertTrue(preGainHandCount == G.handCount[thisPlayer]);
	printf("\n\tDeck: pre(%d), post(%d) -- ", preGainDeckCount , G.deckCount[thisPlayer]);
	failFlag += assertTrue(preGainDeckCount == G.deckCount[thisPlayer]);
	printf("\n\tSupply: pre(%d), post(%d) -- ", preGainSupplyCount , G.supplyCount[1]);
	failFlag += assertTrue(preGainSupplyCount == G.supplyCount[1]);   


	// ----------- TEST 2  --------------
	printf("\nTEST 2: Gaining to Discard adds to Discard\n");

	//empty supply for testing
	G.supplyCount[embargo] = 8;

	//same 1 as right above 
	preGainDiscardCount =  G.discardCount[thisPlayer];
	preGainDeckCount =  G.deckCount[thisPlayer];
	preGainHandCount =  G.handCount[thisPlayer];
	preGainSupplyCount =  G.supplyCount[embargo];

	gainCard(embargo , &G, toDiscard, thisPlayer);

	printf("Only Discard and Supply should have changed:\n");
	printf("\tDiscard: pre(%d), post(%d) -- ", preGainDiscardCount , G.discardCount[thisPlayer]); 
	failFlag += assertTrue(preGainDiscardCount == G.discardCount[thisPlayer] - 1);
	printf("\n\tHand: pre(%d), post(%d) -- ", preGainHandCount , G.handCount[thisPlayer]); 
	failFlag += assertTrue(preGainHandCount == G.handCount[thisPlayer]);
	printf("\n\tDeck: pre(%d), post(%d) -- ", preGainDeckCount , G.deckCount[thisPlayer]);
	failFlag += assertTrue(preGainDeckCount == G.deckCount[thisPlayer]);
	printf("\n\tSupply: pre(%d), post(%d) -- ", preGainSupplyCount , G.supplyCount[embargo]);
	failFlag += assertTrue(preGainSupplyCount == G.supplyCount[embargo] + 1); 

	printf("\nMake sure that we are actually getting the card that we were expecting -- ");
	failFlag += assertTrue(G.discard[thisPlayer][G.discardCount[thisPlayer] - 1] == embargo); 


	// ----------- TEST 3  --------------
	printf("\nTEST 3: Gaining to Deck adds to Deck\n");

	//empty supply for testing
	G.supplyCount[embargo] = 8;

	//same 1 as right above 
	preGainDiscardCount =  G.discardCount[thisPlayer];
	preGainDeckCount =  G.deckCount[thisPlayer];
	preGainHandCount =  G.handCount[thisPlayer];
	preGainSupplyCount =  G.supplyCount[embargo];

	gainCard(embargo , &G, toDeck, thisPlayer);

	printf("Only Deck and Supply should have changed:\n");
	printf("\tDiscard: pre(%d), post(%d) -- ", preGainDiscardCount , G.discardCount[thisPlayer]); 
	failFlag += assertTrue(preGainDiscardCount == G.discardCount[thisPlayer]);
	printf("\n\tHand: pre(%d), post(%d) -- ", preGainHandCount , G.handCount[thisPlayer]); 
	failFlag += assertTrue(preGainHandCount == G.handCount[thisPlayer]);
	printf("\n\tDeck: pre(%d), post(%d) -- ", preGainDeckCount , G.deckCount[thisPlayer]);
	failFlag += assertTrue(preGainDeckCount == G.deckCount[thisPlayer] - 1);
	printf("\n\tSupply: pre(%d), post(%d) -- ", preGainSupplyCount , G.supplyCount[embargo]);
	failFlag += assertTrue(preGainSupplyCount == G.supplyCount[embargo] + 1); 

	printf("\nMake sure that we are actually getting the card that we were expecting -- ");
	failFlag += assertTrue(G.deck[thisPlayer][G.deckCount[thisPlayer] - 1] == embargo);


	// ----------- TEST 4  --------------
	printf("\nTEST 4: Gaining to Hand adds to Hand\n");

	//empty supply for testing
	G.supplyCount[embargo] = 8;

	//same 1 as right above 
	preGainDiscardCount =  G.discardCount[thisPlayer];
	preGainDeckCount =  G.deckCount[thisPlayer];
	preGainHandCount =  G.handCount[thisPlayer];
	preGainSupplyCount =  G.supplyCount[embargo];

	gainCard(embargo , &G, toHand, thisPlayer);

	printf("Only Hand and Supply should have changed:\n");
	printf("\tDiscard: pre(%d), post(%d) -- ", preGainDiscardCount , G.discardCount[thisPlayer]); 
	failFlag += assertTrue(preGainDiscardCount == G.discardCount[thisPlayer]);
	printf("\n\tHand: pre(%d), post(%d) -- ", preGainHandCount , G.handCount[thisPlayer]); 
	failFlag += assertTrue(preGainHandCount == G.handCount[thisPlayer] - 1);
	printf("\n\tDeck: pre(%d), post(%d) -- ", preGainDeckCount , G.deckCount[thisPlayer]);
	failFlag += assertTrue(preGainDeckCount == G.deckCount[thisPlayer]);
	printf("\n\tSupply: pre(%d), post(%d) -- ", preGainSupplyCount , G.supplyCount[1]);
	failFlag += assertTrue(preGainSupplyCount == G.supplyCount[embargo] + 1); 

	printf("\nMake sure that we are actually getting the card that we were expecting -- ");
	failFlag += assertTrue(G.hand[thisPlayer][G.handCount[thisPlayer] - 1] == embargo); 
	 

	// ----------- TEST 5  --------------
	printf("\nTEST 5: Adding card that isn't in the deck, outpost\n");

	//same 1 as right above 
	preGainDiscardCount =  G.discardCount[thisPlayer];
	preGainDeckCount =  G.deckCount[thisPlayer];
	preGainHandCount =  G.handCount[thisPlayer];
	preGainSupplyCount =  G.supplyCount[outpost];

	gainCard(outpost , &G, toHand, thisPlayer);

	printf("Nothing should have changed:\n");
	printf("\tDiscard: pre(%d), post(%d) -- ", preGainDiscardCount , G.discardCount[thisPlayer]); 
	failFlag += assertTrue(preGainDiscardCount == G.discardCount[thisPlayer]);
	printf("\n\tHand: pre(%d), post(%d) -- ", preGainHandCount , G.handCount[thisPlayer]); 
	failFlag += assertTrue(preGainHandCount == G.handCount[thisPlayer]);
	printf("\n\tDeck: pre(%d), post(%d) -- ", preGainDeckCount , G.deckCount[thisPlayer]);
	failFlag += assertTrue(preGainDeckCount == G.deckCount[thisPlayer]);
	printf("\n\tSupply: pre(%d), post(%d) -- ", preGainSupplyCount , G.supplyCount[1]);
	failFlag += assertTrue(preGainSupplyCount == G.supplyCount[outpost] + 1); 

	printf("\nMake sure that we are actually getting the card that we were expecting -- ");
	failFlag += assertTrue(G.hand[thisPlayer][G.handCount[thisPlayer] - 1] == outpost); 

	printf("\n UNIT TESTS for gainCard(): ");
	assertTrue(failFlag == 0);
	printf("\n");
	

	return 0;
}

