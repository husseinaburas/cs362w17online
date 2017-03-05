/*
Aviral Sinha
CS 362
Random Testing for Village Card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h> 
#include "rngs.h"
#include <stdlib.h>

#define MAX_TESTS 100
#define NOISY 1	

#define TESTCARD "Village"

void my_assert(int test, char* msg)
{
	if (!test) {
		printf ("Assert has failed: %s\n", msg);
	}
	return;
}


int main(int argc, char* argv[]) {
    int i, j;
	int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
	int newActions = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	if (argc > 1) {
        seed = atoi(argv[1]);      
		printf("user input seed: %s\n", argv[1]);
    } 
	else {
        printf("no seed input instead a standard seed of %d used\n", seed);
    } 

	for (j=0; j<MAX_TESTS; j++) {
		
		numPlayers = (rand() % 4) + 1;
									
		initializeGame(numPlayers, k, seed, &G);

		printf("Testing Card: %s \n", TESTCARD);
		
		G.deckCount[thisPlayer] = (rand() % (MAX_DECK - 1) ) + 1;
		G.handCount[thisPlayer] = (rand() % (MAX_HAND - 1) ) + 1;

		memcpy(&testG, &G, sizeof(struct gameState));

		 if (NOISY == 0) {
			printf("# of players = %d\n", numPlayers);	
			printf("Before hand count = %d\n", testG.handCount[thisPlayer]);
			printf("Before deck count = %d\n", testG.deckCount[thisPlayer]);
		 }	
					
		cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
		newCards = 1;
		xtraCoins = 0;
		newActions = 2;
			
		if (NOISY == 0) {
			printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
			printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
			printf("actions = %d, expected = %d\n", testG.numActions, G.numActions + newActions);
		}	
					
		my_assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "msg 1");
		my_assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "msg 2");
		my_assert(testG.numActions == G.numActions + newActions, "msg 4");


			
		
		
		if (NOISY == 0) {
			printf("Check to see if no change to the supply card piles\n");
		}	
		
		for (i=0; i<sizeof(testG.supplyCount)/sizeof(int); i++) {
		
		if (NOISY == 0) {
			printf("supply card count = %d, expected = %d\n", testG.supplyCount[i], G.supplyCount[i]);
		}	
			my_assert(testG.supplyCount[i] == G.supplyCount[i], "msg 7"); 
		}
		
		if (NOISY == 0) {
			printf("other players deck count = %d, expected = %d\n", testG.deckCount[thisPlayer + 1], G.deckCount[thisPlayer + 1]);
		}	
		my_assert(testG.deckCount[thisPlayer + 1] == G.deckCount[thisPlayer + 1], "msg 6");
		   
		if (NOISY == 0) {
			printf("other players hand count = %d, expected %d\n", testG.handCount[thisPlayer + 1], G.handCount[thisPlayer + 1]);
		}	
		my_assert(testG.handCount[thisPlayer + 1] == G.handCount[thisPlayer + 1], "msg 5");
		  
			
	}	

	printf("\n Success: Testing complete %s \n\n", TESTCARD);


	return 0;
}