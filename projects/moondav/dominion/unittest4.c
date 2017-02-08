/*********************************************************************
unittest4.c

Author: David Moon
Date: 2-1-2017
Description:
    This unit test will test the isGameOver() function in dominion.c.
    The following are key points the test will check:
    - The game ends when 3 supply piles are empty
    - The game ends when a combination of 3 supply piles and kingodm
      piles are empty
    - The game ends when the Province pile is empty
    - The game continues if there are less than 3 empty piles, and
      the Province pile is not empty

Note: Some skeleton code for game setup was taken from cardtest4.c,
    which was posted to the OSU CS-362 course web page.

Include the following lines in your makefile:

unittest4: unittest4.c dominion.o rngs.o
    gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

**********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest1.h"


int main() {
    int testResult = FAIL;
    int observed;
    int expected;
    int seed = 5;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    int currentPlayer = whoseTurn(&G);
    int i;
    int numCardTypes = 25;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    printf("\n\n############# TESTING isGameOver() FUNCTION ###############\n");


    printf("TEST 1: Empty supply pile of Province cards.\n\n");
    // setup
    // Ensure that all card piles have cards in them.
    for(i = 0; i < numCardTypes; i++){
        G.supplyCount[i] = 10;
    }

    // Empty the Province pile
    G.supplyCount[province] = 0;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
        
    // Check that the game is over.
    observed = isGameOver(&testG);
    expected = 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Empty Province Pile: Game Status", observed, expected);


    printf("\n\nTEST 2: 3 empty supply piles.\n\n");
    // setup
    // Ensure that all card piles have cards in them.
    for(i = 0; i < numCardTypes; i++){
        G.supplyCount[i] = 10;
    }

    // Empty 3 piles
    G.supplyCount[adventurer] = 0;
    G.supplyCount[smithy] = 0;
    G.supplyCount[embargo] = 0;    

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
        
    // Check that the game is over.
    observed = isGameOver(&testG);
    expected = 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "3 Empty Supply Piles: Game Status", observed, expected);

    
    printf("\n\nTEST 3: 2 empty supply piles and 1 empty kingdom pile.\n\n");
    // setup
    // Ensure that all card piles have cards in them.
    for(i = 0; i < numCardTypes; i++){
        G.supplyCount[i] = 10;
    }

    // Empty 2 supply piles and a kingdom pile
    G.supplyCount[duchy] = 0;
    G.supplyCount[adventurer] = 0;
    G.supplyCount[village] = 0;    

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
        
    // Check that the game is over.
    observed = isGameOver(&testG);
    expected = 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "2 Empty Supply Piles and 1 Empty Kingdom Pile: Game Status", observed, expected);


    printf("\n\nTEST 4: 2 empty supply piles.\n\n");
    // setup
    // Ensure that all card piles have cards in them.
    for(i = 0; i < numCardTypes; i++){
        G.supplyCount[i] = 10;
    }

    // Empty 2 supply piles
    G.supplyCount[mine] = 0;
    G.supplyCount[village] = 0;    

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
        
    // Check that the game is over.
    observed = isGameOver(&testG);
    expected = 0;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "2 Empty Supply Piles: Game Status", observed, expected);


    printf("\n\nTEST 5: Empty Duchy and Estate piles.\n\n");
    // setup
    // Ensure that all card piles have cards in them.
    for(i = 0; i < numCardTypes; i++){
        G.supplyCount[i] = 10;
    }

    // Empty the Duchy and Estate piles
    G.supplyCount[duchy] = 0;
    G.supplyCount[estate] = 0;  

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
        
    // Check that the game is over.
    observed = isGameOver(&testG);
    expected = 0;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Empty Duchy and Estate Piles: Game Status", observed, expected);
    

    printf("\n\nEND OF UNIT TEST 4\n\n");

    return 0;
}