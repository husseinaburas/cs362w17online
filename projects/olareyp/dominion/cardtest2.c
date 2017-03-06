/* -----------------------------------------------------------------------
 * File: cardtest2.c
 * Card: smithy
 * Author: Patrick OLarey
 * Date: 2/2/2017
 * Course/Assignment: CS362-400 / Assignment 3
 *
 * Source(s): Preprocessor #if/#endif statements for "noisy" tests and memset code
 *				to clear a gamestate sourced from instructor-provided
 *				testUpdateCoins.c
 *
 * Makefile
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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


//Unit test for: Smithy
int main() {

	int i;
	int j;

	int failFlag = 0;

	// arguments for initializeGame()
	int player;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	int seed = 999;
	struct gameState state;

	int bonus = 0;
	int handPos;
	int count;
	int numActions = 1;

	// holds the state before of these arrays prior to the unit test
	// to be compared to the state of the arrays post unit test
	int oldSupplyCount[treasure_map + 1];

	int oldDeck[MAX_PLAYERS][MAX_DECK];
	int oldDiscard[MAX_PLAYERS][MAX_DECK];
	int oldHand[MAX_PLAYERS][MAX_DECK];

	int oldHandCount[MAX_PLAYERS];
	int oldDeckCount[MAX_PLAYERS];
	int oldDiscardCount[MAX_PLAYERS];
	
	int ok[10];

	for (player = 0; player < MAX_PLAYERCOUNT; player++)
	{
		for (count = 3; count < MAX_DECK-400; count++)
		{
			for (handPos = 0; handPos < count; handPos++)
			{
				// clear gamestate and initialize new gamestate
				memset(&state, 23, sizeof(struct gameState));
				initializeGame(4, k, seed, &state);

				//state.playedCardCount = 0;
				state.whoseTurn = player;
				state.numActions = numActions;
				state.handCount[player] = count;
				state.deckCount[player] = count;
				state.discardCount[player] = count;
				//set the three cards in the player's deck that will be drawn to a unique value so we can see if it was in-fact the card drawn and from the player's deck
				state.deck[player][count - 1] = 99;
				state.deck[player][count - 2] = 99;
				state.deck[player][count - 3] = 99;

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



				//play smithy card
				cardEffect(smithy, 1, 1, 1, &state, handPos, &bonus);



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


				// verify drawn cards came from the player's pile
				// the first drawn card replaces the played card in the player's hand (taking its handPos), any additionally drawn cards are placed a back of hand
#if (HALTING_TEST == 1)
				assert(state.hand[player][handPos] == 99);
				assert(state.hand[player][state.handCount[player] - 1] == 99);
				assert(state.hand[player][state.handCount[player] - 2] == 99);
#endif
				if (state.hand[player][handPos] != 99 || state.hand[player][state.handCount[player] - 1] != 99 || state.hand[player][state.handCount[player] - 2] != 99)
					failFlag = 1;
				//player discarded smithy (handCount[player]--) and drew three new cards (handCount[player]+=3) so hand count should increase by 2
#if (NOISY_TEST == 1)
					printf("Count: %d. Player: %d. handCount = %d, deckCount = %d, discardCount = %d\n", count, player, state.handCount[player], state.deckCount[player], state.discardCount[player]);
#endif
#if (HALTING_TEST == 1)
				assert(state.handCount[player] == count + 2);
#endif
				if (state.handCount[player] != count + 2)
					failFlag = 1;
				//though discarded, discardCount doesn't increment until end-of-turn (which is encountered in this test) so discard count should stay the same as count
#if (HALTING_TEST == 1)
					assert(state.discardCount[player] == count);
#endif
				if (state.discardCount[player] != count)
					failFlag = 1;
				//player drew three cards from deck so deckCount should dec by 1
#if (HALTING_TEST == 1)
					assert(state.deckCount[player] == count - 3);
#endif
				if (state.deckCount[player] != count - 3)
					failFlag = 1;
			}
		}
	}


	// print error if the failFlag was tripped, otherwise, print tests passed
	if (failFlag == 1)
		printf("cardtest2 (SMITHY) - TESTS FAILED\n");
	else
		printf("cardtest2 (SMITHY) - ALL TESTS PASSED\n");

	return 0;
}
