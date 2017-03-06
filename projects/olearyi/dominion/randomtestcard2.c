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
    int tests = 300000;
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
		memcpy(&testG, &G, sizeof(struct gameState));
		int handI=0;
		int deckI=0;
		int handF=0;
		int deckF=0;
		int actI = 0;
		int actF = 0;


		
		deckI = G.deckCount[currentPlayer];
		handI = G.handCount[currentPlayer];
		actI = G.numActions;

		cardEffect(village, choice1, choice2, choice3, &G, handpos, &bonus);

		deckF = G.deckCount[currentPlayer];
		handF = G.handCount[currentPlayer];
		actF = G.numActions;

		int handChange = handF - handI;
		int deckChange = deckF - deckI;
		int actChange = actF - actI;

		if(handChange == 0 && deckChange == 1 && actChange == 2){
			passed++;
		}
		else{
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


