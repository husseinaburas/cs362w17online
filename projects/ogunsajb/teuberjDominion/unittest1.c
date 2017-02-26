/*
 * unittest1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o refactor.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o refactor.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "handCard()"
#define ASSERT(exp, MSG) if(exp) printf("%s: PASS!\n", MSG); else printf("%s: FAILED!\n", MSG)
#define ASSERT(exp) if(!exp) {printf("Test FAILED!\n"); error = 1;}
	
int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m, error=0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	int currentPlayer;
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing function: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: check handCard() --------------
	printf("TEST 1: check if handCard()returns expected values\n");

	//set player's hands to known values
	for(i=0; i<numPlayers; i++){
		for (j=0; j<MAX_HAND; j++){
			G.hand[i][j] = MAX_HAND - j -1;
			//printf("saving G.hand[%d][%d] = %d\n",i,j,G.hand[i][j]);
		}
	}
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));	

	//check if handCard returns saved state with known values
	for(i=0; i<numPlayers; i++){
		G.whoseTurn = i;
		
		for (j=0; j<MAX_HAND; j++){
			//printf("expected G.hand[%d][%d] = %d; actual = %d\n",i,j,testG.hand[i][j], handCard(j, &G) );
			ASSERT((testG.hand[i][j] == handCard(j, &G)));
		}
				
	}	
	
	if (error)
		printf("TEST Failed!\n");
	else
		printf("TEST PASSED!\n");
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


