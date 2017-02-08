
/*  James Le
 *	CS 362
 *	Assignment 3
 *	Ali Aburas
 */

#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "time.h"
#include "interface.h"

int testShuffle(){

  // initialize variables and gamestate
	struct gameState state;
	int players = 2;
	int test = -1;	// test set to -1 if testing fails to complete
	int seed = 0;

	seed = rand();

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	            remodel, smithy, village, baron, great_hall};

	// test to see if game runs
	test = initializeGame(players, k, seed, &state);

	assert (test == 0);


   // testing shuffle function
   //===========================================================
	test = -1;  // reset test to -1

	// create cards for shuffling
	state.deckCount[0] = 6;
	state.deck[0][0] = copper;
	state.deck[0][1] = silver;
	state.deck[0][2] = gold;
	state.deck[0][3] = mine;
	state.deck[0][4] = feast;
	state.deck[0][5] = gardens;

	// test shuffle, if test >= 0, then the function works


	test = shuffle(0, &state);

	// test that shuffle function works
	if(test == -1){
		printf ("\nshuffle failed\n");
			return 1;
	} else {
		printf ("\nshuffle passed\n");
	}

	// test that the position of some cards changed after shuffle
	if(state.deck[0][0] == copper && state.deck[0][1] == silver &&
			   state.deck[0][2] == gold && state.deck[0][3] == mine &&
			   state.deck[0][4] == feast && state.deck[0][5] == gardens){

		printf ("\ndeck position failed\n");
			return 1;

	} else {
		printf ("\ndeck position passed\n");
	}

	int cards[MAX_DECK] = {0};
	int i;

	// set the index of each cards to 1
	for (i=0; i<6; i++){
		cards[state.deck[0][i]] = 1;
	}

	// test that all cards are still in deck after shuffle
	if(!(cards[copper] && cards[silver] && cards[gold]
				&& cards[mine] && cards[feast] && cards[gardens])){
		printf("\ndeck failed\n");
			return 1;
	} else {
		 printf ("\ndeck passed\n");
	}

	printf ("\ntestShuffle COMPLETED.\n");

	return 0;
}

int main (){

	printf ("\nSTARTING unittest1 TEST.\n");

	testShuffle();

	printf ("\nFINISHED unittest1 TEST.\n\n");

	return 0;
}