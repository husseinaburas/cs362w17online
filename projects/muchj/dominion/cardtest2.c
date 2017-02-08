/**************************************
Adam Much
CS 362
Assignment 3
Adventurer card test

Add to Makefile:

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

**************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TESTCARD "Adventurer"

int main() {
    int newCards = 2;
    int discarded = 0;
    
    int shuffledCards = 0;
	
    int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
   
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	
	// Keep the same kingdom cards as the example.
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	// But use a different set for the test to check for changes.
	int testK[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// Initialize a game state and player cards.
	initializeGame(numPlayers, k, seed, &G);
	initializeGame(numPlayers, testK, seed, &testG);	
	
	
	// Play the card.
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	
	printf("----------------- Testing Card: %s ----------------\n\n", TESTCARD);	

	// ----------- TEST 1:  --------------
	printf("TEST 1: Correct number of cards in player's hand.\n");	
	printf("hand count = %d, expected = %d\n\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	
	// ----------- TEST 2:  --------------
	printf("TEST 2: Correct number of cards in player's deck.\n");	
	printf("deck count = %d, expected = %d\n\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	
	// ----------- TEST 3:  --------------
	printf("TEST 3: No state change for the other player.\n");
	printf("hand count (player 2) = %d, expected = %d\n", testG.handCount[1], G.handCount[1]);
	printf("deck count (player 2) = %d, expected = %d\n\n", testG.deckCount[1], G.deckCount[1]);
	
	// ----------- TEST 4:  --------------
	printf("TEST 4: No state changes to the kingdom cards.\n");
	
	for(i = 0; i < 10; i++){
		printf("Kingdom card = %d, expected = %d\n", testK[i], k[i]);	
	};
	
	// ----------- TEST 5:  --------------
	printf("\nTEST 5: No state changes to the victory cards.\n");
	printf("Estate supply = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
	printf("Duchy supply = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
	printf("Province supply = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
	
	
	// ----------- TEST 6:  --------------
	printf("\nTEST 6: Make sure cards added are copper cards (4).\n");
	for(i = G.handCount[thisPlayer]; i < testG.handCount[thisPlayer]; i++){
		printf("Card value = %d, expected = 4\n", testG.hand[thisPlayer][i]);	
	};
	
	
	// Throw in some asserts just for fun.
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
	assert(testG.handCount[1] == G.handCount[1]);
	assert(testG.deckCount[1] == G.deckCount[1]);
	
	for(i = 0; i < 10; i++){
		assert(testK[i] == k[i]);	
	};
	
	assert(testG.supplyCount[estate] == G.supplyCount[estate]);
	assert(testG.supplyCount[duchy] == G.supplyCount[duchy]);
	assert(testG.supplyCount[province] == G.supplyCount[province]);
		
	assert(testG.hand[thisPlayer][5] == 4);
	assert(testG.hand[thisPlayer][6] == 4);
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
