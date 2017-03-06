/* -----------------------------------------------------------------------
 * File: unittest1.c
 * Function: fullDeckCount()
 * Author: Patrick OLarey
 * Date: 2/2/2017
 * Course/Assignment: CS362-400 / Assignment 3
 *
 * Source(s): Preprocessor #if/#endif statements for "noisy" tests and memset code
 *				to clear a gamestate sourced from instructor-provided
 *				testUpdateCoins.c
 *
 * Makefile
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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
#define MAX_CARD 26


//Unit test for: fullDeckCount()
int main() {
	
	int j;

	int card;
	int fullDeckCardCount;

	int count;

	int failFlag = 0;

	// arguments for initializeGame()
	int player;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	int seed = 999;
	struct gameState state;


	for (player = 0; player < MAX_PLAYERCOUNT; player++)
	{
		for (card = 0; card <= MAX_CARD; card++)
		{
			for (count = 0; count < 500; count++)
			{
				fullDeckCardCount = 0;
				// clear gamestate and initalize new gamestate
				memset(&state, 23, sizeof(struct gameState));		
				initializeGame(player, k, seed, &state);			
				
				state.deckCount[player] = count;
				state.handCount[player] = count;
				state.discardCount[player] = count;

				for (j = 0; j < count; j++)
				{
					state.deck[player][j] = card;
					state.hand[player][j] = card;
					fullDeckCardCount += 2;
				}
				for (j = 0; j < count; j++)
				{
					state.discard[player][j] = card;
					fullDeckCardCount += 1 ;
				}

				#if (NOISY_TEST == 1)
				printf("Player: %d, Card: %d, Count: %d. fullDeckCount() returned %d, expected = %d\n", player, card, count, fullDeckCount(player, card, &state), fullDeckCardCount);
				#endif
				if (fullDeckCount(player, card, &state) != fullDeckCardCount)
					failFlag = 1;
				#if (HALTING_TEST == 1)
				assert(fullDeckCount(player, card, &state) == fullDeckCardCount);
				#endif

			}
		}
	}

	// print error if the failFlag was tripped, otherwise, print tests passed
	if (failFlag == 1)
		printf("unittest1 (FULLDECKCOUNT) - TESTS FAILED\n");
	else
		printf("unittest1 (FULLDECKCOUNT) - ALL TESTS PASSED\n");

	return 0;
}
