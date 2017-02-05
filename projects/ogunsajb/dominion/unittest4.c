/*
 * unittest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o refactor.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o refactor.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "updateCoins()"
#define ASSERT(exp, MSG) if(exp) printf("%s: PASS!\n", MSG); else printf("%s: FAILED!\n", MSG)
#define ASSERT(exp) if(!exp) {printf("Test FAILED!\n"); error = 1;}
#define ENDOFCARDS (treasure_map+1)

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

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing function: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: validate update coins --------------
	printf("TEST 1: validate update coins\n");

	//ensure there is at least one of each in a player's hand
	G.hand[thisPlayer][testG.handCount[thisPlayer]+1] = silver;
	testG.handCount[thisPlayer]++;

	G.hand[thisPlayer][testG.handCount[thisPlayer]+1] = gold;
	testG.handCount[thisPlayer]++;

	G.hand[thisPlayer][testG.handCount[thisPlayer]+1] = copper;
	testG.handCount[thisPlayer]++;	
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	testG.coins = 0;
	
	  //add coins for each Treasure card in player's hand
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
		//printf("DEBUG: testG.hand[thisPlayer][%d] = %d\n",i,testG.hand[thisPlayer][i]);
      if (testG.hand[thisPlayer][i] == copper)   testG.coins += 1;
	  else 
		if (testG.hand[thisPlayer][i] == silver) testG.coins += 2;
	  else 
		if (testG.hand[thisPlayer][i] == gold)   testG.coins += 3;
    }	

    //add bonus
    testG.coins += 50; //bonus
	
	updateCoins(thisPlayer, &G, 50);
	
	ASSERT((memcmp(&G, &testG, sizeof(struct gameState)) == 0));
	
	if (error)
		printf("TEST Failed!\n");
	else
		printf("TEST PASSED!\n");	
	

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}