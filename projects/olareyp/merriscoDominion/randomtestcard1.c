/* -----------------------------------------------------------------------
 * File: randomtestcard1.c
 * Card: Great Hall
 * Author: Patrick OLarey
 * Date: 2/12/2017
 * Course/Assignment: CS362-400 / Assignment 4
 *
 * Source(s): Preprocessor #if/#endif statements for "noisy" tests and code
 *				to completely fill gamestate with random values sourced from instructor-provided
 *				betterTestDrawCard.c
 *
 * Makefile
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */


// required #includes
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

// set HALTING_TEST to 0 to remove halting asserts
#define HALTING_TEST 0
// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0


// max values
#define MAX_HANDCOUNT 500
#define MAX_PLAYERCOUNT 4
#define MAX_BONUS 10
#define MAX_DECKCOUNT 100

//random tester for: great_hall
int main(int argc, char *argv[]) {

	// generally used for loop and array indices
	int i;
	int j;
	int n;
	
	// set to 1 when a failure is detected
	int failFlag = 0;

	// gamestate variables
	struct gameState state;
	int player;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	int bonus;
	int handPos;
	int count;
	int numActions;
	int playedCardCount;

	// holds the state before of these arrays prior to the unit test
	// to be compared to the state of the arrays post unit test
	int oldSupplyCount[treasure_map + 1];

	int oldDeck[MAX_PLAYERS][MAX_DECK];
	int oldDiscard[MAX_PLAYERS][MAX_DECK];
	int oldHand[MAX_PLAYERS][MAX_DECK];
	int ok[10];	//old kingdom cards

	int oldHandCount[MAX_PLAYERS];
	int oldDeckCount[MAX_PLAYERS];
	int oldDiscardCount[MAX_PLAYERS];
	
	// seed for random number generator if supplied in command line argument, otherwise, use seed of 999
	if (argc == 2)
		srand(atoi(argv[1]));
	else
		srand(999);

	//number of random tests to perform
	for (n = 0; n < 1000; n++) 
	{
		// creates a random gamestate
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&state)[i] = floor(Random() * 256);
		}

		// randomly generate select gamestate values
		player = rand() % MAX_PLAYERCOUNT;		// randomly selects a player (0-3)
		count = (rand() % MAX_DECKCOUNT)  + 1;	// randomly selects a count (1-101)
		handPos = rand() % count;				// randomly selects a position for the card in the player's hand (0-count)
		numActions = rand() % 11;				// randomly selects a numActions value (0-10)
		bonus = rand() % 11;					// randomly selects a bonus value (0-10)
		playedCardCount = rand() % count;	// randomly selects a playedCardCount value (0-count)

		// set select gamestate values to the randomly generated values
		state.whoseTurn = player;
		state.numActions = numActions;
		state.handCount[player] = count;
		state.deckCount[player] = count;
		state.discardCount[player] = count;
		state.playedCardCount = playedCardCount;

		//set the card in the player's deck that will be drawn to a unique value so we can see if it was in-fact the card drawn
		state.deck[player][count - 1] = 99;

		//make copy of original kingdom cards
		for (i = 0; i < 10; i++)
			ok[i] = k[i];

		//make copy of original states of the deck, hand, discard, supply, and counts
		for (i = 0; i < MAX_PLAYERS; i++)
		{
			//deck, hand, discard cards
			for (j = 0; j < count; j++)
			{
				oldDeck[i][j] = state.deck[i][j];
				oldDiscard[i][j] = state.discard[i][j];
				oldHand[i][j] = state.hand[i][j];
			}

			//deck, hand, and discard counts
			oldHandCount[i] = state.handCount[i];
			oldDeckCount[i] = state.deckCount[i];
			oldDiscardCount[i] = state.discardCount[i];
		}

		//make copy of supply cards (treasure, victory, kingdom, and curse)
		for (i = 0; i < treasure_map + 1; i++)
			oldSupplyCount[i] = state.supplyCount[i];


		//play great_hall card - passing it a random state, handpos, and bonus
		cardEffect(great_hall, 1, 1, 1, &state, handPos, &bonus);


		//check that old and current states for the other players and supply are the same
		for (i = 0; i < MAX_PLAYERS; i++)
			if (i != player)
			{
				//check that no changes have been made to deck, hand, discard cards
				for (j = 0; j < count; j++)
				{
					if (oldDeck[i][j] != state.deck[i][j])
					{
						failFlag = 1;
#if (NOISY_TEST == 1)
						printf("Deck Change Detected - Player: %d. Pos: %d. oldDeck = %d, newDeck = %d\n", i, j, oldDeck[i][j], state.deck[i][j]);
#endif
					}
					if (oldDiscard[i][j] != state.discard[i][j])
					{
						failFlag = 1;
#if (NOISY_TEST == 1)
						printf("Discard Change Detected - Player: %d. Pos: %d. oldDeck = %d, newDeck = %d\n", i, j, oldDiscard[i][j], state.discard[i][j]);
#endif
					}
					if (oldHand[i][j] != state.hand[i][j])
					{
						failFlag = 1;
#if (NOISY_TEST == 1)
						printf("Hand Change Detected - Player: %d. Pos: %d. oldDeck = %d, newDeck = %d\n", i, j, oldHand[i][j], state.hand[i][j]);
#endif
					}
				}

				//check that no changes have been made to deck, hand, and discard counts
				if (oldHandCount[i] != state.handCount[i])
				{
					failFlag = 1;
#if (NOISY_TEST == 1)
					printf("HandCount Change Detected - Player: %d. oldCount = %d, newCount = %d\n", i, oldHandCount[i], state.handCount[i]);
#endif
				}
				if (oldDeckCount[i] != state.deckCount[i])
				{
					failFlag = 1;
#if (NOISY_TEST == 1)
					printf("DeckCount Change Detected - Player: %d. oldCount = %d, newCount = %d\n", i, oldDeckCount[i], state.deckCount[i]);
#endif
				}
				if (oldDiscardCount[i] != state.discardCount[i])
				{
					failFlag = 1;
#if (NOISY_TEST == 1)
					printf("DiscardCount Change Detected - Player: %d. oldCount = %d, newCount = %d\n", i, oldDiscardCount[i], state.discardCount[i]);
#endif
				}
			}


		//check that no changes have been made to supply cards (treasure, victory, kingdom, and curse)
		for (i = 0; i < treasure_map + 1; i++)
			if (oldSupplyCount[i] != state.supplyCount[i])
			{
				failFlag = 1;
#if (NOISY_TEST == 1)
				printf("SupplyCount Change Detected - SupplyPile: %d. oldCount = %d, newCount = %d\n", i, oldSupplyCount[i], state.supplyCount[i]);
#endif
			}

		//check that kingdom cards haven't been altered (supply of each is checked above)
		for (i = 0; i < 10; i++)
			if (ok[i] != k[i])
			{
				failFlag = 1;
#if (NOISY_TEST == 1)
				printf("KingdomCard Change Detected - KingdomCard Pile: %d. oldCard = %d, newCard = %d\n", i, ok[i], k[i]);
#endif
			}


		// verify drawn card came from the player's pile
		// the drawn card replaces the played card in the player's hand (taking its handPos)
#if (HALTING_TEST == 1)
		assert(state.hand[player][handPos] == 99);
#endif
		if (state.hand[player][handPos] != 99)
			failFlag = 1;
		//player discarded great_hall (handCount[player]--) and drew one new card (handCount[player]++) so hand count stays the same
#if (NOISY_TEST == 1)
			printf("Count: %d. Player: %d. handCount = %d, deckCount = %d, discardCount = %d\n", count, player, state.handCount[player], state.deckCount[player], state.discardCount[player]);
#endif
#if (HALTING_TEST == 1)
		assert(state.handCount[player] == count);
#endif
		if (state.handCount[player] != count)
			failFlag = 1;
		//though discarded, discardCount doesn't increment until end-of-turn (which is encountered in this test) so discard count should stay the same as count
#if (HALTING_TEST == 1)
			assert(state.discardCount[player] == count);
#endif
		if (state.discardCount[player] != count)
			failFlag = 1;
		//player drew card from deck so deckCount should dec by 1
#if (HALTING_TEST == 1)
			assert(state.deckCount[player] == count - 1);
#endif
		if (state.deckCount[player] != count - 1)
			failFlag = 1;
		// player's number of actions should increase by one. the numActions decrement for playing great_hall doesn't occur until control is returned to playCard()
		// which is not part of this test, so it is correct to only count the increase to actions here.
#if (HALTING_TEST == 1)
		assert(state.numActions == numActions + 1);
#endif
		if (state.numActions != numActions + 1)
			failFlag = 1;
	}

	// print error if the failFlag was tripped, otherwise, print tests passed
	if (failFlag == 1)
		printf("randomtestcard1 (GREATHALL) - TESTS FAILED\n");
	else
		printf("randomtestcard1 (GREATHALL) - ALL TESTS PASSED\n");

	return 0;
}
