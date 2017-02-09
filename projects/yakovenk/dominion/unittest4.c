
//Konstantin Yakovenko
//2k17/02/07
//Unit Test for buyCard()

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
	int preBuyNumBuys, 	preBuyCoinCount, preBuyHandCount, preBuyDiscardCount, preBuySupplyCount;

	struct gameState G;	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);


	//run unit tests
	//things we can test: buying card w not enough money, with enough money
	//with enough buys, without buys, 
	//with cards left, with no cards left
	//buy during wrong phases
	//
	printf("\n----------------- Test Function: gainCard() ----------------\n");

	// ----------- TEST 1  --------------
	printf("TEST 1: Verify simple buying works with enough money\n");

	//empty supply for testing
	G.supplyCount[embargo] = 1;
	G.coins = 5;
	G.numBuys = 1;

	//same 1 as right above 
	preBuyNumBuys =  G.numBuys;
	preBuyCoinCount =  G.coins;
	preBuyHandCount =  G.handCount[thisPlayer];
	preBuyDiscardCount = G.discardCount[thisPlayer];
	preBuySupplyCount =  G.supplyCount[embargo];

	int buyResult = buyCard(embargo, &G);

	printf("Only Discard and Supply should have changed:\n");
	printf("\tNumBuys: pre(%d), post(%d) -- ", preBuyNumBuys , G.numBuys); 
	failFlag += assertTrue(preBuyNumBuys ==  G.numBuys + 1);
	printf("\n\tCoins: pre(%d), post(%d) -- ", preBuyCoinCount, G.coins); 
	failFlag += assertTrue(preBuyCoinCount ==  G.coins + 2); //enbargo costs 2.
	printf("\n\tHand: pre(%d), post(%d) -- ", preBuyHandCount,  G.handCount[thisPlayer]);
	failFlag += assertTrue(preBuyHandCount ==  G.handCount[thisPlayer]); //card shouldn't have gone into the hand.
	printf("\n\tSupply: pre(%d), post(%d) -- ", preBuySupplyCount , G.supplyCount[embargo]);
	failFlag += assertTrue(preBuySupplyCount == G.supplyCount[embargo] + 1); 

	printf("\nMake sure that we are actually getting the card that we were expecting -- ");
	failFlag += assertTrue(G.discard[thisPlayer][G.discardCount[thisPlayer] - 1] == embargo); 

	

	// ----------- TEST 2  --------------
	printf("\nTEST 2:Buying with not enough coins\n");

	//empty supply for testing
	G.supplyCount[embargo] = 1;
	G.coins = 1; //embargo takes 2

	//same 1 as right above 
	preBuyNumBuys =  G.numBuys;
	preBuyCoinCount =  G.coins;
	preBuyHandCount =  G.handCount[thisPlayer];
	preBuyDiscardCount = G.discardCount[thisPlayer];
	preBuySupplyCount =  G.supplyCount[embargo];

	buyResult = buyCard(embargo, &G);

	printf("Nothing should change because we shouldn't be able to buy:\n");
	printf("\tNumBuys: pre(%d), post(%d) -- ", preBuyNumBuys , G.numBuys); 
	failFlag += assertTrue(preBuyNumBuys ==  G.numBuys);
	printf("\n\tCoins: pre(%d), post(%d) -- ", preBuyCoinCount, G.coins); 
	failFlag += assertTrue(preBuyCoinCount ==  G.coins); //enbargo costs 2.
	printf("\n\tHand: pre(%d), post(%d) -- ", preBuyHandCount,  G.handCount[thisPlayer]);
	failFlag += assertTrue(preBuyHandCount ==  G.handCount[thisPlayer]); //card shouldn't have gone into the hand.
	printf("\n\tSupply: pre(%d), post(%d) -- ", preBuySupplyCount , G.supplyCount[embargo]);
	failFlag += assertTrue(preBuySupplyCount == G.supplyCount[embargo]); 


	// ----------- TEST 3  --------------
	printf("\nTEST 3:Buying with no cards remaining\n");

	//empty supply for testing
	G.supplyCount[embargo] = 0;
	G.coins = 2; //embargo takes 2
	G.numBuys = 2; //because 1 causes it to fail.

	//save important state
	preBuyNumBuys =  G.numBuys;
	preBuyCoinCount =  G.coins;
	preBuyHandCount =  G.handCount[thisPlayer];
	preBuyDiscardCount = G.discardCount[thisPlayer];
	preBuySupplyCount =  G.supplyCount[embargo];

	 buyResult = buyCard(embargo, &G);

	printf("Nothing should change because we shouldn't be able to buy:\n");
	printf("\tNumBuys: pre(%d), post(%d) -- ", preBuyNumBuys , G.numBuys); 
	failFlag += assertTrue(preBuyNumBuys ==  G.numBuys);
	printf("\n\tCoins: pre(%d), post(%d) -- ", preBuyCoinCount, G.coins); 
	failFlag += assertTrue(preBuyCoinCount ==  G.coins); //enbargo costs 2.
	printf("\n\tHand: pre(%d), post(%d) -- ", preBuyHandCount,  G.handCount[thisPlayer]);
	failFlag += assertTrue(preBuyHandCount ==  G.handCount[thisPlayer]); //card shouldn't have gone into the hand.
	printf("\n\tSupply: pre(%d), post(%d) -- ", preBuySupplyCount , G.supplyCount[embargo]);
	failFlag += assertTrue(preBuySupplyCount == G.supplyCount[embargo]); 
	

	// ----------- TEST 4  --------------
	printf("\nTEST 4:Buying with no buys remaining\n");

	//empty supply for testing
	G.supplyCount[embargo] = 1;
	G.coins = 2; //embargo takes 2
	G.numBuys = 0;

	//save important state
	preBuyNumBuys =  G.numBuys;
	preBuyCoinCount =  G.coins;
	preBuyHandCount =  G.handCount[thisPlayer];
	preBuyDiscardCount = G.discardCount[thisPlayer];
	preBuySupplyCount =  G.supplyCount[embargo];

	 buyResult = buyCard(embargo, &G);

	printf("Nothing should change because we shouldn't be able to buy:\n");
	printf("\tNumBuys: pre(%d), post(%d) -- ", preBuyNumBuys , G.numBuys); 
	failFlag += assertTrue(preBuyNumBuys ==  G.numBuys);
	printf("\n\tCoins: pre(%d), post(%d) -- ", preBuyCoinCount, G.coins); 
	failFlag += assertTrue(preBuyCoinCount ==  G.coins); //enbargo costs 2.
	printf("\n\tHand: pre(%d), post(%d) -- ", preBuyHandCount,  G.handCount[thisPlayer]);
	failFlag += assertTrue(preBuyHandCount ==  G.handCount[thisPlayer]); //card shouldn't have gone into the hand.
	printf("\n\tSupply: pre(%d), post(%d) -- ", preBuySupplyCount , G.supplyCount[embargo]);
	failFlag += assertTrue(preBuySupplyCount == G.supplyCount[embargo]); 


	// ----------- TEST 5  --------------
	printf("\nTEST 5:Buying during wrong phase\n");

	//empty supply for testing
	G.supplyCount[embargo] = 1;
	G.coins = 2; //embargo takes 2
	G.numBuys = 1;
	G.phase = 3; //nonsensical phase

	//save important state
	preBuyNumBuys =  G.numBuys;
	preBuyCoinCount =  G.coins;
	preBuyHandCount =  G.handCount[thisPlayer];
	preBuyDiscardCount = G.discardCount[thisPlayer];
	preBuySupplyCount =  G.supplyCount[embargo];

	buyResult = buyCard(embargo, &G);

	printf("Nothing should change because we shouldn't be able to buy:\n");
	printf("\tNumBuys: pre(%d), post(%d) -- ", preBuyNumBuys , G.numBuys); 
	failFlag += assertTrue(preBuyNumBuys ==  G.numBuys);
	printf("\n\tCoins: pre(%d), post(%d) -- ", preBuyCoinCount, G.coins); 
	failFlag += assertTrue(preBuyCoinCount ==  G.coins); //enbargo costs 2.
	printf("\n\tHand: pre(%d), post(%d) -- ", preBuyHandCount,  G.handCount[thisPlayer]);
	failFlag += assertTrue(preBuyHandCount ==  G.handCount[thisPlayer]); //card shouldn't have gone into the hand.
	printf("\n\tSupply: pre(%d), post(%d) -- ", preBuySupplyCount , G.supplyCount[embargo]);
	failFlag += assertTrue(preBuySupplyCount == G.supplyCount[embargo]); 


	printf("\n UNIT TESTS for gainCard(): ");
	assertTrue(failFlag == 0);
	printf("\n");
	

	return 0;
}

