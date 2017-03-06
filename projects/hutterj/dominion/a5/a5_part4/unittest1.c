/*
Author: hutterj
Date: 2017.02.07
File: unittest1.c
Purpose: Perform unit tests of function buyCard in dominion.c

Rules of buyCard:
	supplyPos must be valid (be within game spec)
	cannot buy if less than one buy available
	cannot buy if no cards in specified supply pile left
	cannot buy is card's price is more than coins available
	after a successful buy:
		that card is present on top of discard
		all players' decks same as before
		player's discard is +1 from before
		supply count is descremented 1 for bought card, same for other cards
		all players' hand same as before
		card cost subtracted from coins
		available buys decremented by 1
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


/*
Name: asserttrue
Purpose:  use something like assert to check conditions
but still be able to collect coverage
*/
void asserttrue(int condition, char* condName){
	if (condition){
		printf("Test: %-33s success.\n", condName);
	}
	else {
		printf("Test: %-33s FAIL.\n", condName);
	}
	return;
}

int main(void){
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int funcStatus;
	int i;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing Function: buyCard ----------------\n");
	
	// ----------- TEST 1: attempt to buy with negative supplyPos  --------------
	printf("TEST 1: out of bounds supplyPos\n");
	
	
	
	// card is -100
	// set coins and buys to make sure we're testing the supplyPos
	G.coins = 10;
	G.numBuys = 1;
	funcStatus = buyCard(-100, &G);
	asserttrue((funcStatus == -1), "out of bounds supplyPos -100");
	
	// card is -28
	// set coins and buys to make sure we're testing the supplyPos
	G.coins = 10;
	G.numBuys = 1;
	funcStatus = buyCard(-28, &G);
	asserttrue((funcStatus == -1), "out of bounds supplyPos  -28");
	
	// card is 999
	// set coins and buys to make sure we're testing the supplyPos
	G.coins = 10;
	G.numBuys = 1;
	funcStatus = buyCard(999, &G);
	asserttrue((funcStatus == -1), "out of bounds supplyPos  999");
	
	// card is 27
	// set coins and buys to make sure we're testing the supplyPos
	G.coins = 10;
	G.numBuys = 1;
	funcStatus = buyCard(27, &G);
	asserttrue((funcStatus == -1), "out of bounds supplyPos   27");
	
	
	// ----------- TEST 2: attempt to buy with 0 buys  --------------
	printf("\n\nTEST 2: numBuys 0 or less\n");
	initializeGame(numPlayers, k, seed, &G);
	G.numBuys = 0;
	funcStatus = buyCard(0, &G);
	asserttrue((funcStatus == -1), "numBuys     0");
	
	// negative numBuys
	G.numBuys = -1;
	funcStatus = buyCard(curse, &G);
	asserttrue((funcStatus == -1), "numBuys    -1");
	
	G.numBuys = -1000;
	funcStatus = buyCard(curse, &G);
	asserttrue((funcStatus == -1), "numBuys -1000");
	
	
	// ----------- TEST 3: supply pile empty  --------------
	printf("\n\nTEST 3: supply pile 0 or less\n");
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 10;
	G.numBuys = 1;
	// no more curses left
	G.supplyCount[curse] = 0;
	funcStatus = buyCard(curse, &G);
	asserttrue((funcStatus == -1), " 0 curses left");
	
	// no more curses left
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 10;
	G.numBuys = 1;
	G.supplyCount[curse] = -1;
	funcStatus = buyCard(curse, &G);
	asserttrue((funcStatus == -1), "-1 curses left");
	
	// no more minions left
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 10;
	G.numBuys = 1;
	G.supplyCount[minion] = 0;
	funcStatus = buyCard(minion, &G);
	asserttrue((funcStatus == -1), " 0 minion left");

	// -1 more minions left
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 10;
	G.numBuys = 1;
	G.supplyCount[minion] = -1;
	funcStatus = buyCard(minion, &G);
	asserttrue((funcStatus == -1), "-1 minion left");
	
	// no more province left
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 10;
	G.numBuys = 1;
	G.supplyCount[province] = 0;
	funcStatus = buyCard(province, &G);
	asserttrue((funcStatus == -1), " 0 province left");

	// -1 more province left
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 10;
	G.numBuys = 1;
	G.supplyCount[province] = -1;
	funcStatus = buyCard(province, &G);
	asserttrue((funcStatus == -1), "-1 province left");
	
	// no more silver left
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 10;
	G.numBuys = 1;
	G.supplyCount[silver] = 0;
	funcStatus = buyCard(silver, &G);
	asserttrue((funcStatus == -1), " 0 silver left");

	// -1 more silver left
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 10;
	G.numBuys = 1;
	G.supplyCount[silver] = -1;
	funcStatus = buyCard(silver, &G);
	asserttrue((funcStatus == -1), "-1 silver left");
	
	
	
	// ----------- TEST 4: cost too high  --------------
	printf("\n\nTEST 4: insufficient coins\n");
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 1;
	G.numBuys = 1;
	// buy estate: cost is 2, we have 1
	funcStatus = buyCard(estate, &G);
	asserttrue((funcStatus == -1), "insufficient funds (1 coin buy estate)");
	
	// negative coins
	G.coins = -1;
	G.numBuys = 1;
	// buy curse: cost is 0, we have -1
	funcStatus = buyCard(curse, &G);
	asserttrue((funcStatus == -1), "insufficient funds (-1 coin buy curse)");
	
	
	// ----------- TEST 5: successful buy: card in discard?  --------------
	printf("\n\nTEST 5: bought card in discard after buy\n");
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 10;
	G.numBuys = 1;
	thisPlayer = whoseTurn(&G);
	//discard should be empty to start
	asserttrue((G.discardCount[thisPlayer] == 0), "discard pile empty before buy");
	funcStatus = buyCard(province, &G);
	asserttrue((funcStatus == 0), "buy province                 ");
	asserttrue((G.discardCount[thisPlayer] == 1), "discard pile 1 after buy");
	asserttrue((G.discard[thisPlayer][0] == province), "discard pile top is province");
	
	// ----------- TEST 6: successful buy: decremented supply count?  --------------
	printf("\n\nTEST 6: supply count decremented\n");
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 10;
	G.numBuys = 1;
	thisPlayer = whoseTurn(&G);
	// copy game state to testG to compare supply count afterward
	memcpy(&testG, &G, sizeof(struct gameState));
	
	// do the buy, iterate to check each supply but province is same
	funcStatus = buyCard(province, &G);
	asserttrue((funcStatus == 0), "buy province");
	
	for (i = 0; i < treasure_map+1; i++){
		if (i == province){
			asserttrue((supplyCount(province, &G) == (supplyCount(province, &testG)-1)), "province decremented");
		}
		else {
			asserttrue((supplyCount(i, &G) == (supplyCount(i, &testG))), "not decremented");
		}
	}
	
	// ----------- TEST 7: successful buy: hands of players same?  --------------
	printf("\n\nTEST 7: hands unchanged\n");
	asserttrue((memcmp(&(G.hand),&(testG.hand), sizeof(G.hand)) == 0), "all hands same after buy");
	asserttrue((memcmp(&(G.handCount),&(testG.handCount), sizeof(G.handCount)) == 0), "all hand counts same after buy");
	
	// ----------- TEST 8: successful buy: decks of players same?  --------------
	printf("\n\nTEST 8: decks unchanged\n");
	asserttrue((memcmp(&(G.deck),&(testG.deck), sizeof(G.deck)) == 0), "all decks same after buy");
	asserttrue((memcmp(&(G.deckCount),&(testG.deckCount), sizeof(G.deckCount)) == 0), "all deck counts same after buy");
	
	// ----------- TEST 9: successful buy: coins subtracted appropriately?  --------------
	printf("\n\nTEST 9: coins subtracted\n");
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 10;
	G.numBuys = 2;
	memcpy(&testG, &G, sizeof(struct gameState));
	funcStatus = buyCard(province, &G);
	asserttrue((funcStatus == 0), "buy province");
	asserttrue((G.coins+getCost(province) == testG.coins), "coins for province subtracted");
	
	// ----------- TEST 10: successful buy: buys subtracted appropriately?  --------------
	printf("\n\nTEST 10: buys subtracted\n");
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 10;
	G.numBuys = 2;
	memcpy(&testG, &G, sizeof(struct gameState));
	funcStatus = buyCard(province, &G);
	asserttrue((funcStatus == 0), "buy province");
	asserttrue((G.numBuys+1 == testG.numBuys), "buys for province subtracted");
	
	memcpy(&testG, &G, sizeof(struct gameState));
	funcStatus = buyCard(province, &G);
	asserttrue((funcStatus == -1), "not buy province");
	asserttrue((G.numBuys == testG.numBuys), "buys for province not subtracted");
	
	memcpy(&testG, &G, sizeof(struct gameState));
	funcStatus = buyCard(estate, &G);
	asserttrue((funcStatus == 0), "buy estate");
	asserttrue((G.numBuys+1 == testG.numBuys), "buys for estate subtracted");
	asserttrue((G.numBuys == 0), "0 buys remaining");

	printf("\n\n\n");
	return 0;
	

}


