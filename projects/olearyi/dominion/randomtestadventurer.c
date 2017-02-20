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

#define TESTCARD "adventurer"

int main(int ranseed) {
	struct gameState G, testG;
    int newCards = 0;
	int passed = 0;
	int failed = 0;
    int currentPlayer;
    int i, j;
    int tests = 300000;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = ranseed;
    int numPlayers = 4;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, great_hall};


for (j = 0; j < tests; j++){
	// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		
		// copy the game state to a test case
		currentPlayer = (rand() % numPlayers);
		G.handCount[currentPlayer] = (rand() % 10) +1;
		G.deckCount[currentPlayer] = 10 - G.handCount[currentPlayer];
		memcpy(&testG, &G, sizeof(struct gameState));
		int handTi=0;
		int deckTi=0;
		int handTf=0;
		int deckTf=0;
		int tempCount = 0;

		for(i = 0; i < G.deckCount[currentPlayer]; i++)
		{
			newCards = G.deck[currentPlayer];
			if(newCards == copper || newCards == silver || newCards == gold)
			{
				tempCount++;
			}
		}
		deckTi = tempCount;
		tempCount = 0;
		for(i = 0; i < G.handCount[currentPlayer]; i++)
		{
			newCards = G.hand[currentPlayer][i];
			if(newCards == copper || newCards == silver || newCards == gold)
			{
				tempCount++;
			}
		}
		handTi = tempCount;
		tempCount = 0;

		cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

		for(i = 0; i < G.deckCount[currentPlayer]; i++)
		{
			newCards = G.deck[currentPlayer];
			if(newCards == copper || newCards == silver || newCards == gold)
			{
				tempCount++;
			}
		}
		deckTf = tempCount;
		tempCount = 0;
		for(i = 0; i < G.handCount[currentPlayer]; i++)
		{
			newCards = G.hand[currentPlayer][i];
			if(newCards == copper || newCards == silver || newCards == gold)
			{
				tempCount++;
			}
		}
		handTf = tempCount;

		int handChange = handTf - handTi;
		int deckChange = deckTf - deckTi;

		if(handChange == deckChange && ((handChange > 0 && handChange < 3) || deckTi == 0)){
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


