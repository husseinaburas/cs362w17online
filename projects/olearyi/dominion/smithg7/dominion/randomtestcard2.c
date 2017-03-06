/*********************************************
*   Format used from cardtest4.c example
*
*********************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main(int ranseed) {
    int tests = 10;
    int passed = 0;
	int failed = 0;
	int currentPlayer;
    int j;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = ranseed;
    int numPlayers = 4;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, great_hall};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);


for (j = 0; j < tests; j++){
	// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		
		// copy the game state to a test case
		currentPlayer = (rand() % numPlayers);
		G.handCount[currentPlayer] = (rand() % 10) +1;
		G.deckCount[currentPlayer] = 10 - G.handCount[currentPlayer];
		int handI=0;
		int deckI=0;
		int handF=0;
		int deckF=0;
		int actI = 0;
		int actF = 0;


		
		deckI = G.deckCount[currentPlayer];
		handI = G.handCount[currentPlayer];
		actI = G.numActions;

		printf("handI = %d , deckI = %d , actI = %d, currentPlayer = %d", handI, deckI, actI, currentPlayer);

		handleVillage(currentPlayer, &G, handpos);

		deckF = G.deckCount[currentPlayer];
		handF = G.handCount[currentPlayer];
		actF = G.numActions;

		printf("handF = %d , deckF = %d , actF = %d, currentPlayer = %d", handF, deckF, actF, currentPlayer);

		int handChange = handF - handI;
		int deckChange = deckF - deckI;
		int actChange = actF - actI;

		if(handChange == 0 && deckChange == 1 && actChange == 2){
			passed++;
		}
		else{
			printf("handChange = %d out of 0, deckChange = %d out of 1, actChange = %d out of 2", handChange, deckChange, actChange);
			failed++;
		}

	}
	

			if (passed > 0){
		printf("Test passed: %d", passed);
		}
	 	if(failed > 0){
		printf("Test failed: %d\n", failed);
		}


	return 0;
}


