/*
 * cardtest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int coppertrue, silvertrue, i;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	
	// ----------- TEST 1: Testing if 2 cards added to hand --------------
	printf("TEST 1: Testing if a card was drawn\n");
	
		// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
		//Setting what the handcount; the same lol
	G.handCount[thisPlayer] = G.handCount[thisPlayer] + 2;
		//Trying the test
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);

	
	//set up test game
	for(i=0; i<5; i++){
        testG.deck[0][i] = k[i+1]; //fill with 5 cards
    }

	testG.deck[0][5] = copper; //set copper
	testG.deck[0][6] = silver; //set silver
	testG.deckCount[0]=7; // set to 6 cards total
	testG.hand[0][0] = adventurer; //sets adventurer card
	testG.handCount[0] = 1;//set to 1 card in hand
	
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	// ----------- TEST 2: Testing if copper in hand--------------
	printf("TEST 2: Testing if copper in hand\n");
	coppertrue = 0;
	//step through hand looking for copper
	for(i = 0; i < testG.handCount[0]; i++){
		if(testG.hand[0][i] == copper){
			coppertrue = 1;
		}
	}
	printf("copper true: = %d, expected = 1\n", coppertrue);
	assert(testG.hand[0][1] == copper || testG.hand[0][2] == copper);
	
	// ----------- TEST 3: Testing if silver in hand--------------
	
	printf("TEST 2: Testing if silver in hand\n");
	silvertrue = 0;
	printf("printing 1: %d\n",silver);
	printf("printing 2: %d\n",testG.hand[0][2]);
	//step through hand looking for silver
	for(i = 0; i < testG.handCount[0]; i++){
		if(testG.hand[0][i] == silver){
			silvertrue = 1;
		}
	}
	printf("silver true: = %d, expected = 1\n", silvertrue);
	assert(silvertrue == 1);
	

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


