/***************************************
* Name: James Stewart
* Date: 1/31/2017
* File: cardtest1.c
* Description: Tests the isGameOver() Function
***************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "unittest.h"

int main() {
    int testResult = FAIL;
    int observed, i;
    int seed = 5;
    int numPlayers = 2;
	int numCardTypes = 25;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	void newHand(){
    for(i = 0; i < numCardTypes; i++){
        G.supplyCount[i] = 10;
    }
	}
			
	void process(int expected, char *name){
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		observed = isGameOver(&testG);
		if(observed == expected){testResult = PASS;}
		else{testResult = FAIL;}
		assertTrue(testResult, name, observed, expected);
	}
			
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
    printf("\n\n----------------- TESTING isGameOver() FUNCTION -----------------\n\n");
    newHand();
    G.supplyCount[province] = 0;
	process(1, "Test 1: Province pile is empty");
	
    newHand();
    G.supplyCount[adventurer] = 0;
    G.supplyCount[smithy] = 0;
    G.supplyCount[embargo] = 0;    
    process(1, "Test 2: 3 supplies piles are empty");

    newHand();
    G.supplyCount[duchy] = 0;
    G.supplyCount[adventurer] = 0;
    G.supplyCount[village] = 0;    
    process(1, "Test 3: 1 empty kingdom pile & 2 empty supplies piles");

    newHand();
    G.supplyCount[mine] = 0;
    G.supplyCount[village] = 0;    
    process(0, "Test 4: 2 supplies piles are empty");    

	printf(" >>>>> SUCCESS: Testing isGameOver() complete <<<<<\n\n");
	
    return 0;
}