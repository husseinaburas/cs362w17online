/* -----------------------------------------------------------------------
 * File: unittest2.c
 * Function: isGameOver()
 * Author: Patrick OLarey
 * Date: 2/2/2017
 * Course/Assignment: CS362-400 / Assignment 3
 *
 * Source(s): Preprocessor #if/#endif statements for "noisy" tests and memset code
 *				to clear a gamestate sourced from instructor-provided
 *				testUpdateCoins.c
 *
 * Makefile
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

 // set HALTING_TEST to 0 to remove halting asserts
#define HALTING_TEST 0
 // set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0


// required #includes
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>


// max values
#define MAX_HANDCOUNT 500
#define MAX_PLAYERCOUNT 4
#define MAX_BONUS 10


//Unit test for: isGameOver()
int main() {
	
	int i;
	int j;
	int m;

	int failFlag = 0;

	// arguments for initializeGame()
	int player = 2;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	int seed = 999;
	struct gameState state;

	int gameOver;

	// Test for game over when province pile is 0..12 and all other supply piles are > 0.
	for (i = 12; i >= 0; i--)
	{
		// clear gamestate and initialize new gamestate
		memset(&state, 23, sizeof(struct gameState));		//clear gamestate
		initializeGame(player, k, seed, &state);			//initialize new gamestate

		// fill all supply piles (so that only an empty province pile will trigger game over).
		for (j = 0; j < 27; j++)
			state.supplyCount[j] = 54;

		// set province pile card count to i.
		state.supplyCount[province] = i;

		// if the province pile is empty (0), the game should be over
		if (i == 0)
			gameOver = 1;
		else
			gameOver = 0;

		if (isGameOver(&state) != gameOver)
			failFlag = 1;

#if (NOISY_TEST == 1)
		printf("isGameOver() returned %d, expected = %d\n", isGameOver(&state), gameOver);
#endif
#if (HALTING_TEST == 1)
		assert(isGameOver(&state) == gameOver);
#endif
	}

	// Test for 3 empty pile game over condition for cards 2 through 26
	for (i = 2; i < 27 ; i++)
	{
		// clear gamestate and initialize new gamestate
		memset(&state, 23, sizeof(struct gameState));		//clear gamestate
		initializeGame(player, k, seed, &state);			//initialize new gamestate
		
		//set two supply pile counts to empty (0)
		state.supplyCount[0] = 0;
		state.supplyCount[1] = 0;

		// fill all other supply piles 
		for (j = 2; j < 27; j++)
			state.supplyCount[j] = 54;

		// remove 1 card at a time from supply pile i until the pile is empty.
		for (m = 0; m < 54; m++)
		{
			state.supplyCount[i]--;

			// only when the pile is empty should the game be over
			if (state.supplyCount[i] == 0)
				gameOver = 1;
			else
				gameOver = 0;

			if (isGameOver(&state) != gameOver)
				failFlag = 1;

#if (NOISY_TEST == 1)
			printf("Cards remaining in supply pile %d = %d, isGameOver() returned %d, expected = %d\n", i, state.supplyCount[i], isGameOver(&state), gameOver);
#endif
#if (HALTING_TEST == 1)
			assert(isGameOver(&state) == gameOver);
#endif
		}

	}


	// Test for 3 empty pile game over condition for cards 0 through 1
	for (i = 0; i < 2; i++)
	{
		// clear gamestate and initialize new gamestate
		memset(&state, 23, sizeof(struct gameState));		//clear gamestate
		initializeGame(player, k, seed, &state);			//initialize new gamestate

															//set two supply pile counts to empty (0)
		
		// fill all supply piles
		for (j = 0; j < 27; j++)
			state.supplyCount[j] = 54;
		
		// set two of the piles equal to 0 (empty)
		state.supplyCount[8] = 0;
		state.supplyCount[9] = 0;

		// remove 1 card at a time from supply pile i until the pile is empty.
		for (m = 0; m < 54; m++)
		{
			state.supplyCount[i]--;

			// only when the pile is empty should the game be over
			if (state.supplyCount[i] == 0)
				gameOver = 1;
			else
				gameOver = 0;

			if (isGameOver(&state) != gameOver)
				failFlag = 1;

#if (NOISY_TEST == 1)
			printf("Cards remaining in supply pile %d = %d, isGameOver() returned %d, expected = %d\n", i, state.supplyCount[i], isGameOver(&state), gameOver);
#endif
#if (HALTING_TEST == 1)
			assert(isGameOver(&state) == gameOver);
#endif
		}

	}


	// print error if the failFlag was tripped, otherwise, print tests passed
	if (failFlag == 1)
		printf("unittest2 (ISGAMEOVER) - TESTS FAILED\n");
	else
		printf("unittest2 (ISGAMEOVER) - ALL TESTS PASSED\n");

	return 0;
}
