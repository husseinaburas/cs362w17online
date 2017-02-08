
//Konstantin Yakovenko
//2k17/02/07
//Unit Test for updateCoins()

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

	struct gameState G;	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	//run unit tests
	//things we can test: setting coins to different players, setting a large # of coins,
	//setting a negative number of coins, setting different bonuses
	printf("\n----------------- Test Function: updateCoins() ----------------\n");

	// ----------- TEST 1  --------------
	printf("TEST 1: player 0, 1g/1s/1c, 0 bonus\n");

	//fill the hand with cards
	G.hand[thisPlayer][0] = gold;
    G.hand[thisPlayer][1] = silver;
    G.hand[thisPlayer][2] = copper;
    G.hand[thisPlayer][3] = mine;
    G.hand[thisPlayer][4] = smithy;
    G.handCount[thisPlayer] = 5;

	//count those card values
	updateCoins(thisPlayer, &G, 0);

	printf("Hand: 1g+1s+1c should equal 6: %d\n", G.coins);  

	//output results
	failFlag += assertTrue(G.coins == 6);

	// ----------- TEST 2  --------------
	printf("TEST 2: player 0, 1g/1s/1c, 1 bonus\n");
	updateCoins(thisPlayer, &G, 1);
	printf("Hand: 1g+1s+1c should equal 7: %d\n", G.coins); 

	failFlag += assertTrue(G.coins == 7);

	// ----------- TEST 3  --------------
	printf("TEST 3: player 0, pushing no coins\n");
	G.hand[thisPlayer][0] = village;
    G.hand[thisPlayer][1] = sea_hag;
    G.hand[thisPlayer][2] = mine;
    G.hand[thisPlayer][3] = mine;
    G.hand[thisPlayer][4] = smithy;
    G.handCount[thisPlayer] = 5;

    updateCoins(thisPlayer, &G, 0);

	printf("Hand: No treasure cards should equal 0: %d\n", G.coins); 

	failFlag += assertTrue(G.coins == 0);

	// ----------- TEST 4  --------------
	printf("TEST 4: player 0, unreasonably large negative bonus\n");
	G.hand[thisPlayer][0] = village;
    G.hand[thisPlayer][1] = sea_hag;
    G.hand[thisPlayer][2] = mine;
    G.hand[thisPlayer][3] = mine;
    G.hand[thisPlayer][4] = smithy;
    G.handCount[thisPlayer] = 5;

    //unreasonably large bonus
    updateCoins(thisPlayer, &G, -15000000); 

	printf("Hand: -15000000 bonus(just out of curiosity): %d\n", G.coins); 

	//since this isn't in the documentation, I won't pass/fail this.
	//assertTrue(G.coins == 0);

	printf("\n UNIT TESTS for updateCoins(): ");
	assertTrue(failFlag == 0);
	printf("\n");
	

	return 0;
}

