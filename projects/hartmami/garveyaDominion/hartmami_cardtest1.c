/***********************************************************************************************
**
**  Author:       Michael Hartman
**
**  Date:           2017-02-06
**
**  Filename:       cardtest1.c
**
**  Description:    unittest for the card smithy in dominion tests:
**
**  verify preconditions
**  verify smithy is at the top of Player 1's discard pile
**  verify Player 1's playedCardCount has been incremented to 1
**  verify Player 1 has 7 cards in their hand
**  error verify Player 1 has 6 cards in their hand due to (assignment2 bug)
**  verify Player 1 has 4 cards in their deck
**  error Player 1 has 5 cards in their deck due to bug
**  verify the fifth card in Player 1's hand is a silver
**  verify the sixth card in Player 1's hand is a gold
**  verify the seventh card in Player 1's hand is a embargo
**  previous tests verify cards came from player1's deck into their hand
**  verify player2 is as expected
**  verify treasure_map is 26
**
***********************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define TESTCARD "smithy"

int main()
{
	int bonus = 0;
	int seed = 772;
	int bug = 1;  // if initialized to 0 then test will run additional known bug tests
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(2, k, seed, &G);  // initialize game state for 2 players

	printf("\n	Testing Card: %s \n\n", TESTCARD);

		G.hand[0][0] = smithy;  // player 1 first card
		G.hand[0][1] = adventurer;  // player 1 second card
		G.hand[0][2] = embargo;  // player 1 third card
		G.hand[0][3] = minion;  // player 1 fourth card
		G.hand[0][4] = mine;  // player 1 fifth card
		G.deck[0][4] = embargo;  // deck fifth card
		G.deck[0][5] = gold;  // deck sixth card
		G.deck[0][6] = silver;  // deck seventh card
		G.handCount[0] = 5;  // player 1 has 5 cards in their hand
		G.numActions = 2;  // player 1 has 2 actions
		G.deckCount[0] = 7;  // player 1 has 7 cards in their deck
		G.playedCardCount = 0;  // player 1 has not played any cards
		G.coins = 5;  // player 1 has 5 coins
		G.hand[1][0] = smithy;  // player 2 first card
		G.hand[1][1] = adventurer;  // player 2 second card
		G.hand[1][2] = embargo;  // player 2 third card
		G.hand[1][3] = minion;  // player 2 fourth card
		G.hand[1][4] = mine;  // player 2 fifth card
		G.deck[1][4] = embargo;  // deck fifth card
		G.deck[1][5] = gold;  // deck sixth card
		G.deck[1][6] = silver;  // deck seventh card
		G.handCount[1] = 5;  // player 2 has 5 cards in their hand
		G.deckCount[1] = 7;  // player 1 has 7 cards in their deck

		printf("Player 1 has 5 cards in their hand:  ");
		testAssert(G.handCount[0] == 5);  // run testAssert
		printf("\n");

		printf("The card at top of the deck is a silver:  ");
		testAssert(G.deck[0][6] == silver);  // run testAssert
		printf("\n");

		printf("The card 2nd from the top of the deck is a gold:  ");
		testAssert(G.deck[0][5] == gold);  // run testAssert
		printf("\n");

		printf("The card 3nd from the top of the deck is a embargo:  ");
		testAssert(G.deck[0][4] == embargo);  // run testAssert
		printf("\n");

		printf("Player 1 has 2 actions:  ");
		testAssert(G.numActions == 2);  // run testAssert
		printf("\n");

		printf("Player 1 has 7 cards in their deck:  ");
		testAssert(G.deckCount[0] == 7);  // run testAssert
		printf("\n");

		printf("Player 1 has not yet played a card:  ");
		testAssert(G.playedCardCount == 0);  // run testAssert
		printf("\n");

		printf("Player 1 has 5 coins:  ");
		testAssert(G.coins == 5);  // run testAssert
		printf("\n");

		printf("Player 2 has 5 cards in their hand:  ");
		testAssert(G.handCount[1] == 5);  // run testAssert
		printf("\n");

		printf("Player 2's top of the deck is a silver:  ");
		testAssert(G.deck[1][6] == silver);  // run testAssert
		printf("\n");

		printf("Player 2's 2nd card from the top of the deck is a gold:  ");
		testAssert(G.deck[1][5] == gold);  // run testAssert
		printf("\n");

		printf("Player 2's 3nd card from the top of the deck is a embargo:  ");
		testAssert(G.deck[1][4] == embargo);  // run testAssert
		printf("\n");

		printf("Player 2 has 7 cards in their deck:  ");
		testAssert(G.deckCount[1] == 7);  // run testAssert
		printf("\n");

		printf("	Playing %s\n", TESTCARD);

		// gameState, currentPlayer, handPos
		// card, choice1, choice2, choice3, gameState, handPos, bonus
		cardEffect(smithy, 0, 0, 0, &G, 0, &bonus);
		printf("\n	Results:\n\n");

		printf("Verify Player 1 has 1 actions:  ");
		testAssert(G.numActions == 1);  // run testAssert
		printf("\n");

		printf("Verify %s is at the top of Player 1's discard pile:  ", TESTCARD);
		testAssert(G.playedCards[0] == smithy);  // run testAssert
		printf("\n");

		printf("Verify Player 1's playedCardCount has been incremented to 1:  ");
		testAssert(G.playedCardCount == 1);  // run testAssert
		printf("\n");

		printf("Verify Player 1 has 7 cards in their hand:  ");
		testAssert(G.handCount[0] == 7);  // run testAssert
		printf("\n");
		printf("Player 1 has %d cards in their hand  \n", G.handCount[0]);
		printf("Player 1 has %d cards in their deck  \n", G.deckCount[0]);
		printf("The fifth card in Player 1's hand is a %d:  ", G.hand[0][0]);

		printf("\n");

		if( bug == 0 )
		{
			printf("	Verify Player 1 has 6 cards in their hand due to bug:  ");
			testAssert(G.handCount[0] == 6);  // run testAssert
			printf("\n");
		}

		printf("Verify Player 1 has 4 cards in their deck:  ");
		testAssert(G.deckCount[0] == 4);  // run testAssert
		printf("\n");

		if( bug == 0 )
		{
			printf("	Player 1 has 5 cards in their deck due to bug:  ");
			testAssert(G.deckCount[0] == 5);  // run testAssert
			printf("\n");
		}

		printf("Verify the fifth card in Player 1's hand is a silver:  ");
		testAssert(G.hand[0][5] == silver);  // run testAssert
		printf("\n");

		printf("Verify the sixth card in Player 1's hand is a gold:  ");
		testAssert(G.hand[0][6] == gold);  // run testAssert
		printf("\n");

		printf("Verify the seventh card in Player 1's hand is a embargo:  ");
		testAssert(G.hand[0][7] == embargo);  // run testAssert
		printf("\n");

		printf("Player 1 has 5 coins:  ");
		testAssert(G.coins == 5);  // run testAssert
		printf("\n");

		printf("Player 2 has 5 cards in their hand:  ");
		testAssert(G.handCount[1] == 5);  // run testAssert
		printf("\n");

		printf("Player 2's top of the deck is a silver:  ");
		testAssert(G.deck[1][6] == silver);  // run testAssert
		printf("\n");

		printf("Player 2's 2nd card from the top of the deck is a gold:  ");
		testAssert(G.deck[1][5] == gold);  // run testAssert
		printf("\n");

		printf("Player 2's 3nd card from the top of the deck is a embargo:  ");
		testAssert(G.deck[1][4] == embargo);  // run testAssert
		printf("\n");

		printf("Player 2 has 7 cards in their deck:  ");
		testAssert(G.deckCount[1] == 7);  // run testAssert
		printf("\n");

		printf("Verify the fifth card in Player 2's hand is a mine:  ");
		testAssert(G.hand[1][4] == mine);  // run testAssert
		printf("\n");

		printf("Verify the fourth card in Player 2's hand is a minion:  ");
		testAssert(G.hand[1][3] == minion);  // run testAssert
		printf("\n");

		printf("Verify treasure_map is 26:  ");  // verify provinces are all present
		testAssert(treasure_map == 26);  // run testAssert
		printf("\n");

	return 0;
}
