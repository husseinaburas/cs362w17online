/* -----------------------------------------------------------------------
 * File: unittest4.c
 * Function: updateCoins()
 * Author: Patrick OLarey
 * Date: 2/2/2017
 * Course/Assignment: CS362-400 / Assignment 3
 *
 * Source(s): Much of this code was based on the testUpdateCoins.c file provided
 *			by the instructor of the course. 
 *
 * Makefile
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */


// required #includes
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>


// set HALTING_TEST to 0 to remove halting asserts
#define HALTING_TEST 0
// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0


// max values
#define MAX_HANDCOUNT 500
#define MAX_PLAYERCOUNT 4
#define MAX_BONUS 10

//Unit test for: updateCoins()
int main() {

	int i;

	// 1 = failures, 0 = no failures
	int failFlag = 0;

	// seed for initializeGame()
	int seed = 999;
	
	// kingdom cards
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	
	struct gameState state;
	
	int player;
	int handCount;
	int bonus;

	// arrays to be filled with copper, silver, or gold
	int copperHand[MAX_HANDCOUNT];
	int silverHand[MAX_HANDCOUNT];
	int goldHand[MAX_HANDCOUNT];
	
	// fill the arrays
	for (i = 0; i < MAX_HANDCOUNT; i++)
	{
		copperHand[i] = copper;
		silverHand[i] = silver;
		goldHand[i] = gold;
	}

	//Iterate through inputs verifying updateCoins() produces the correct output for each combination of inputs
	for (player = 0; player < MAX_PLAYERCOUNT; player++)
	{
		for (handCount = 0; handCount < MAX_HANDCOUNT; handCount++)
		{
			for (bonus = 0; bonus <= MAX_BONUS; bonus++)
			{
				// copper test
				memset(&state, 23, sizeof(struct gameState));		//clear gamestate
				initializeGame(player, k, seed, &state);			//initialize new gamestate
				state.handCount[player] = handCount;				//set player's handcount
				memcpy(state.hand[player], copperHand, sizeof(int) * handCount);//set player's hand to all coppers
				updateCoins(player, &state, bonus);
				#if (NOISY_TEST == 1)
				printf("state.coins = %d, expected = %d\n", state.coins, handCount * 1 + bonus);
				#endif
				if (state.coins != handCount * 1 + bonus)
					failFlag = 1;
				#if (HALTING_TEST == 1)
				assert(state.coins == handCount * 1 + bonus);
				#endif

				// silver test
				memset(&state, 23, sizeof(struct gameState));		//clear gamestate
				initializeGame(player, k, seed, &state);			//initialize new gamestate
				state.handCount[player] = handCount;				//set player's handcount
				memcpy(state.hand[player], silverHand, sizeof(int) * handCount);//set player's hand to all silvers
				updateCoins(player, &state, bonus);
				#if (NOISY_TEST == 1)
				printf("state.coins = %d, expected = %d\n", state.coins, handCount * 2 + bonus);
				#endif
				if (state.coins != handCount * 2 + bonus)
					failFlag = 1;
				#if (HALTING_TEST == 1)
				assert(state.coins == handCount * 2 + bonus);
				#endif

				// gold test
				memset(&state, 23, sizeof(struct gameState));		//clear gamestate
				initializeGame(player, k, seed, &state);			//initialize new gamestate
				state.handCount[player] = handCount;				//set player's handcount
				memcpy(state.hand[player], goldHand, sizeof(int) * handCount);//set player's hand to all golds
				updateCoins(player, &state, bonus);
				#if (NOISY_TEST == 1)
				printf("state.coins = %d, expected = %d\n", state.coins, handCount * 3 + bonus);
				#endif
				if (state.coins != handCount * 3 + bonus)
					failFlag = 1;
				#if (HALTING_TEST == 1)
				assert(state.coins == handCount * 3 + bonus);
				#endif
			}
		}
	}

	// print error if the failFlag was tripped, otherwise, print tests passed
	if (failFlag == 1)
		printf("unittest 4 (UPDATECOINS) - TESTS FAILED\n");
	else
		printf("unittest 4 (UPDATECOINS) - ALL TESTS PASSED\n");

	return 0;
}
