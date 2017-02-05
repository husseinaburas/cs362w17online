/*
 * cardtest1.c (smithy)
 * bug: changed for (i = 0; i < 3; i++) to for (i = 0; i < 2; i++)
  */

  
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

void my_assert(int test, char* msg)
{
	if (!test) {
		printf ("ASSERT HAS FAILED: %s\n", msg);
	}
	return;
}

int main() {
    int i;
	int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

		
	printf("BFhand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("BFdeck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("BFcoins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);

	
	
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 3;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	my_assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "msg 1");
	my_assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "msg 2");
	my_assert(testG.coins == G.coins + xtraCoins, "msg 3");

	//check no change to supply card piles
    printf("Verify no change to the supply card piles\n");

    for (i=0; i<sizeof(testG.supplyCount)/sizeof(int); i++) {
        printf("supply card count = %d, expected = %d\n", testG.supplyCount[i], G.supplyCount[i]);
        my_assert(testG.supplyCount[i] == G.supplyCount[i], "msg 7"); 
    }
	
	//check no change to other players deck
    printf("other players deck count = %d, expected = %d\n", testG.deckCount[thisPlayer + 1], G.deckCount[thisPlayer + 1]);
    my_assert(testG.deckCount[thisPlayer + 1] == G.deckCount[thisPlayer + 1], "msg 6");
       
	//check no change to other players hand
	printf("other players hand count = %d, expected %d\n", testG.handCount[thisPlayer + 1], G.handCount[thisPlayer + 1]);
    my_assert(testG.handCount[thisPlayer + 1] == G.handCount[thisPlayer + 1], "msg 5");
       
	 	
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


