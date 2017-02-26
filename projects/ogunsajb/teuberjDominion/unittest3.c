/*
 * unittest3.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o refactor.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o refactor.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "gainCard()"
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

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("----------------- Testing function: %s ----------------\n", TESTCARD);

	// ----------- TEST 1:check if supply pile is empty --------------
	printf("TEST 1: check if supply pile is empty \n");

	for (i=0; i < ENDOFCARDS; i++)
		G.supplyCount[i] = 0; //empty out all 


	ASSERT((-1 == gainCard(smithy, &G, 0, thisPlayer)));
	
	
	if (error)
		printf("TEST Failed!\n");
	else
		printf("TEST PASSED!\n");

	// ----------- TEST 2: check ToFlag = 0 --------------	
	printf("TEST 2: check ToFlag = 0\n");
	error=0;
	
	// restore the game state to a test case
	memcpy(&G,&testG, sizeof(struct gameState));

	testG.discard[thisPlayer][ testG.discardCount[thisPlayer] ] = smithy;
	testG.discardCount[thisPlayer]++;
	testG.supplyCount[smithy]--;

	gainCard(smithy, &G, 0, thisPlayer);
	
	ASSERT((memcmp(&G, &testG, sizeof(struct gameState)) == 0));
	
	if (error)
		printf("TEST Failed!\n");
	else
		printf("TEST PASSED!\n");
	
	
	// ----------- TEST 3: check ToFlag = 1 --------------	
	printf("TEST 3: check ToFlag = 1\n");
	error=0;
	
	testG.deck[thisPlayer][ testG.deckCount[thisPlayer] ] = smithy;
	testG.deckCount[thisPlayer]++;
	testG.supplyCount[smithy]--;

	gainCard(smithy, &G, 1, thisPlayer);
	
	ASSERT((memcmp(&G, &testG, sizeof(struct gameState)) == 0));
	
	if (error)
		printf("TEST Failed!\n");
	else
		printf("TEST PASSED!\n");	


	// ----------- TEST 4: check ToFlag = 2 --------------	
	printf("TEST 4: check ToFlag = 2\n");
	error=0;
	
	testG.hand[thisPlayer][ testG.handCount[thisPlayer] ] = smithy;
	testG.handCount[thisPlayer]++;
	testG.supplyCount[smithy]--;

	gainCard(smithy, &G, 2, thisPlayer);
	
	ASSERT((memcmp(&G, &testG, sizeof(struct gameState)) == 0));
	
	if (error)
		printf("TEST Failed!\n");
	else
		printf("TEST PASSED!\n");
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}