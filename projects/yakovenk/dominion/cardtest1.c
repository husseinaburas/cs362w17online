
//Konstantin Yakovenko
//2k17/02/07
//Unit Test for Adventurer Card implementation cardAdventurer()

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
	int preCardNumBuys, preCardCoinCount, preCardHandCount, preCardDiscardCount, preCardSupplyCount;

	struct gameState G, bkpG;	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// backup the game to have a fresh copy
	memcpy(&bkpG, &G, sizeof(struct gameState));

	//run unit tests
	//things we can test: do we draw 2 cards?
	//what if only 1 trasure card is in the deck, do we reshuffle the discard?
	//did the size of the hand change and are the 2 most recent cards treasures?
	//how can we test discard?
	//Official FAQ:
	// -If you have to shuffle in the middle, shuffle. Don't shuffle in the revealed cards as these cards 
	//	do not go to the Discard pile until you have finished revealing cards.
    // -If you run out of cards after shuffling and still only have one Treasure, you get just that one Treasure. 
	printf("\n----------------- Test Card: Adventurer ----------------\n");

	// ----------- TEST 1  --------------
	printf("TEST 1: Drawing the cards normally\n");


	//save state for later comparison
	preCardNumBuys =  G.numBuys;
	preCardCoinCount =  G.coins;
	preCardHandCount =  G.handCount[thisPlayer];

	cardAdventurer(thisPlayer, &G);

	printf("Only Coins and Hand should have changed:\n");
	printf("\n\tCoins: pre(%d), post(%d) -- ", preCardCoinCount, G.coins); 
	failFlag += assertTrue(preCardCoinCount ==  G.coins); 
	printf("\n\tHand: pre(%d), post(%d) -- ", preCardHandCount,  G.handCount[thisPlayer]);
	failFlag += assertTrue(preCardHandCount ==  G.handCount[thisPlayer] - 2); //got 2 new cards.


	printf("\nMake sure that we got a treasure  -- ");
	if(preCardHandCount <=  G.handCount[thisPlayer] - 2){
		printf("\nFirst treasure is treasure  -- ");
		failFlag += assertTrue(G.hand[thisPlayer][G.handCount[thisPlayer] - 1] == gold ||
								G.hand[thisPlayer][G.handCount[thisPlayer] - 1] == silver ||
								G.hand[thisPlayer][G.handCount[thisPlayer] - 1] == copper); 
		

		if(preCardHandCount ==  G.handCount[thisPlayer] - 2){
		printf("\nSecond treasure is treasure  -- ");
			failFlag += assertTrue(G.hand[thisPlayer][G.handCount[thisPlayer] - 2] == gold ||
								G.hand[thisPlayer][G.handCount[thisPlayer] - 2] == silver ||
								G.hand[thisPlayer][G.handCount[thisPlayer] - 2] == copper); 
		}


	}
	


	// ----------- TEST 2  --------------
	printf("\nTEST 2: Drawing cards that force reshuffling\n");

	// restore the game to a fresh copy
	memcpy(&G, &bkpG, sizeof(struct gameState));

	//setup
	//create a custom deck that forces reshuffling.
	G.deck[thisPlayer][0] = steward;
	G.deck[thisPlayer][1] = copper;
	G.deck[thisPlayer][2] = duchy;
	G.deck[thisPlayer][3] = estate;
	G.deck[thisPlayer][4] = feast;
	G.deckCount[thisPlayer] = 5;

	G.discard[thisPlayer][0] = steward;
	G.discard[thisPlayer][1] = copper;
	G.discardCount[thisPlayer] = 2;


	//save state for later comparison
	preCardNumBuys =  G.numBuys;
	preCardCoinCount =  G.coins;
	preCardHandCount =  G.handCount[thisPlayer];

	cardAdventurer(thisPlayer, &G);

	printf("Only Coins and Hand should have changed:\n");
	printf("\n\tCoins: pre(%d), post(%d) -- ", preCardCoinCount, G.coins); 
	failFlag += assertTrue(preCardCoinCount ==  G.coins);
	printf("\n\tHand: pre(%d), post(%d) -- ", preCardHandCount,  G.handCount[thisPlayer]);
	failFlag += assertTrue(preCardHandCount ==  G.handCount[thisPlayer] - 2); //got 2 new cards.

	printf("\nFirst treasure is copper as planned from deck  -- ");
	failFlag += assertTrue(G.hand[thisPlayer][G.handCount[thisPlayer] - 1] == copper);
	printf("\nSecond treasure is copper as planned from reshuffle  -- ");
	failFlag += assertTrue(G.hand[thisPlayer][G.handCount[thisPlayer] - 2] == copper);


	printf("\n UNIT TESTS for cardAdventurer(): ");
	assertTrue(failFlag == 0);
	printf("\n");
	

	return 0;
}

