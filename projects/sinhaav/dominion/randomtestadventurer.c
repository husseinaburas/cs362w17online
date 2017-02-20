/*
Aviral Sinha
CS 362
Random Testing for Adventurer Card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TESTCARD "adventurer"

//NOISY_TEST set to 0 and remove printfs from output
#define NOISY_TEST 1

int passed_tests = 0;
int failed_tests = 0;

void assert_true(int val){
	if (val == 0) {
		failed_tests++;
	}
	else
		passed_tests++;
}

int main(int argc, char* args[]){
	//have a single input
	if(argc != 2){
		printf("Usage: randomtestadventurer seed\n");
	return -1;
	}
	int n; 
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int seed = atoi(args[1]);
	struct gameState G, testG;
	srand(seed);
	int num_players;
	
	//random number generator for each variable
	
	for (n=0; n < 2000; n++){
		//generate random number of players
		num_players = rand() % 4 + 1;
		
		//initialize game
		initializeGame(num_players, cards, seed, &G);
		
		//hand must have adventurer card
		G.hand[0][0] = adventurer;
		
		//set up player's deck
		G.deck[0][4] = smithy;
		G.deck[0][3] = silver;
		G.deck[0][2] = tribute;
		G.deck[0][1] = embargo;
		G.deck[0][0] = gold;
		
		//randomize state variables
		G.numActions = rand() % 5;
		G.coins = rand() % 5;
		G.numBuys = rand() % 5;
		
		//save initial state and call cardEffect
		memcpy(&testG, &G, sizeof(struct gameState));
		
		cardEffect(adventurer, 0, 0, 0, &testG, 0, 0);
		
		//test number of cards in hand
		assert_true(testG.handCount[0] == G.handCount[0] + 1);
		
		assert_true(testG.deckCount[0] == G.deckCount[0] - 5);
		
		//test other players for state change
		assert_true(testG.deckCount[1] == G.handCount[1]);
		
		assert_true(testG.handCount[1] == G.handCount[1]);
		
		assert_true(testG.discardCount[1] == G.discardCount[1]);
		
	}
	printf("Random test adventurer completed\n");
	printf("number of tests passed = %d \n", passed_tests);
	printf("number of tests failed = %d \n", failed_tests);
	
	return 0;
}

