/* -----------------------------------------------------------------------
 * File: cardtest3.c
 * Card: Adventurer
 * Author: Patrick OLarey
 * Date: 2/2/2017
 * Course/Assignment: CS362-400 / Assignment 3
 *
 * Source(s): Preprocessor #if/#endif statements for "noisy" tests and memset code
 *				to clear a gamestate sourced from instructor-provided
 *				testUpdateCoins.c
 *
 * Makefile
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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

//Unit test for: Adventurer
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
	int treasureCard;

	int expectedDiscard;

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
		for (count = 2; count < MAX_DECK - 490; count++)
		{
			for (handPos = 0; handPos < count; handPos++)
			{
				for (treasureCard = copper; treasureCard <= gold; treasureCard++)
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

					//replace all players' decks with estates so we know that the treasure cards are being drawn from the player's own deck (treasure cards placed in player's deck below).
					for (j = 0; j < MAX_PLAYERCOUNT; j++)
						for (i = 0; i < count; i++)
						{
							state.deck[j][i] = estate;
							state.hand[j][i] = estate;
						}


					//set the first and last cards in the player's deck to each of the treasure cards (copper, silver, gold).
					state.deck[player][count - count] = treasureCard;
					state.deck[player][count - 1] = treasureCard;
					//both cards are treasure cards so no other cards are discarded
					expectedDiscard = 0;
					//when the deck is larger than 2, add a 3rd treasure card to the middle of the deck and verify that only 2 treasure cards are drawn
					if (count > 2)
					{
						state.deck[player][count / 2] = treasureCard;
						//all the cards between the first card and the middle card will be discarded
						expectedDiscard = (count - 1) - (count / 2) - 1;
					}


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


					//play adventurer card
					cardEffect(adventurer, -1, -1, -1, &state, handPos, &bonus);
					
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
					assert(state.hand[player][handPos] == treasureCard);
					assert(state.hand[player][state.handCount[player] - 1] == treasureCard);
#endif
					if (state.hand[player][handPos] != treasureCard || state.hand[player][state.handCount[player] - 1] != treasureCard)
						failFlag = 1;
					//player discarded adventurer (handCount[player]--) and drew two new cards (handCount[player]+=2) so hand count should increase by 1
#if (NOISY_TEST == 1)
					printf("Count: %d. Player: %d. handCount = %d, deckCount = %d, discardCount = %d, expected DC = %d\n", count, player, state.handCount[player], state.deckCount[player], state.discardCount[player], expectedDiscard);
#endif
#if (HALTING_TEST == 1)
					assert(state.handCount[player] == count + 1);
#endif
					if (state.handCount[player] != count + 1)
						failFlag = 1;
					//though discarded, discardCount doesn't increment until end-of-turn (which is encountered in this test) so discard count should stay the same as count
#if (HALTING_TEST == 1)
					assert(state.discardCount[player] == count + expectedDiscard );
#endif
					if (state.discardCount[player] != count + expectedDiscard)
						failFlag = 1;
					//player drew two treasurecards and expectedDiscard non-treasure cards from deck so deckCount should dec by (2 + expectedDiscard)
#if (HALTING_TEST == 1)
					assert(state.deckCount[player] == count - 2 - expectedDiscard);
#endif
					if (state.deckCount[player] != count - 2 - expectedDiscard)
						failFlag = 1;
				}
			}
		}
	}


	// print error if the failFlag was tripped, otherwise, print tests passed
	if (failFlag == 1)
		printf("cardtest3 (ADVENTURER) - TESTS FAILED\n");
	else
		printf("cardtest3 (ADVENTURER) - ALL TESTS PASSED\n");

	return 0;
}
