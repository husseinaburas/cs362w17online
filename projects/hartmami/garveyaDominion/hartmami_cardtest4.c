/***********************************************************************************************
**
**  Author:       Michael Hartman
**
**  Date:           2017-02-06
**
**  Filename:       cardtest4.c
**
**  Description:    unittest for the card baron in dominion tests:
**
**  verify preconditions
**  verify Player 1 has 1 actions
**  error verify Player 1 has 2 actions (bug actions not decremented)
**  verify baron is at the top of Player 1's discard pile
**  verify Player 1's playedCardCount has been incremented to 1
**  verify Player 1 has 4 cards in their hand
**  verify Player 1 has 8 cards in their deck
**  verify the fifth card (estate) in Player 1's hand is gone
**  verify the numBuys is incremented to 1
**  error verify Player 1 has 2 numBuys (bug numBuys is 2 when it should be 1) due to (assignment2 bug)
**  verify Player 1 has 4 coins
**  Test with no estate in hand; verify a sixth card (estate) in Player 1's hand is added
**  error verify Player 1 has 2 numBuys (bug numBuys is 2 when it should be 1) due to (assignment2 bug)
**
***********************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define TESTCARD "baron"

int main()
{
	int bonus = 0;
	int seed = 772;
	int choice1 = 0;
	int choice2 = 0;
	struct gameState G;
	struct gameState H;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, baron, tribute, smithy, council_room};

	initializeGame(2, k, seed, &G);  // initialize game state for 2 players

	printf("\n	Testing Card: %s \n\n", TESTCARD);

		G.hand[0][0] = baron;  // player 1 first card
		G.hand[0][1] = smithy;  // player 1 second card
		G.hand[0][2] = embargo;  // player 1 third card
		G.hand[0][3] = minion;  // player 1 fourth card
		G.hand[0][4] = estate;  // player 1 fifth card
		G.deck[0][4] = embargo;  // deck fifth card
		G.deck[0][5] = gold;  // deck sixth card
		G.deck[0][6] = silver;  // deck seventh card
		G.deck[0][7] = copper;  // deck seventh card
		G.handCount[0] = 5;  // player 1 has 5 cards in their hand
		G.numActions = 2;  // player 1 has 2 actions
		G.deckCount[0] = 8;  // player 1 has 8 cards in their deck
		G.playedCardCount = 0;  // player 1 has not played any cards
		G.coins = 0;  // player 1 has 0 coins
		choice1 = estate;  // card to be trashed
		G.numBuys = 0;  // player 1 has no buys

		printf("Player 1 has 5 cards in their hand:  ");
		testAssert(G.handCount[0] == 5);  // run testAssert
		printf("\n");

		printf("The card at top of the deck is a copper:  ");
		testAssert(G.deck[0][7] == copper);  // run testAssert
		printf("\n");

		printf("The card 2nd from the top of the deck is a silver:  ");
		testAssert(G.deck[0][6] == silver);  // run testAssert
		printf("\n");

		printf("The card 3nd from the top of the deck is a gold:  ");
		testAssert(G.deck[0][5] == gold);  // run testAssert
		printf("\n");

		printf("The card 4th from the top of the deck is a embargo:  ");
		testAssert(G.deck[0][4] == embargo);  // run testAssert
		printf("\n");

		printf("Player 1 has 2 actions:  ");
		testAssert(G.numActions == 2);  // run testAssert
		printf("\n");

		printf("Player 1 has 8 cards in their deck:  ");
		testAssert(G.deckCount[0] == 8);  // run testAssert
		printf("\n");

		printf("Player 1 has not yet played a card:  ");
		testAssert(G.playedCardCount == 0);  // run testAssert
		printf("\n");

		printf("Player 1 has 0 coins:  ");
		testAssert(G.coins == 0);  // run testAssert
		printf("\n");

		printf("Player 1 has 0 buys:  ");
		testAssert(G.numBuys == 0);  // run testAssert
		printf("\n");

		printf("	Playing %s\n", TESTCARD);

		// currentPlayer, gameState, choice1
		// card, choice1, choice2, choice3, gameState, handPos, bonus
		cardEffect(baron, choice1, choice2, 0, &G, 0, &bonus);
		printf("\n	Results:\n\n");

		printf("Verify Player 1 has 1 actions:  ");
		testAssert(G.numActions == 1);  // run testAssert
		printf("\n");

		printf("Verify error Player 1 has 2 actions:  ");
		testAssert(G.numActions == 2);  // run testAssert
		printf("\n");

		printf("Verify %s is at the top of Player 1's discard pile:  ", TESTCARD);
		testAssert(G.playedCards[0] == baron);  // run testAssert
		printf("\n");

		printf("Verify Player 1's playedCardCount has been incremented to 1:  ");
		testAssert(G.playedCardCount == 1);  // run testAssert
		printf("\n");

		printf("Verify Player 1 has 4 cards in their hand:  ");
		testAssert(G.handCount[0] == 4);  // run testAssert
		printf("\n");

		printf("Verify Player 1 has 8 cards in their deck:  ");
		testAssert(G.deckCount[0] == 8);  // run testAssert
		printf("\n");

		printf("Verify the fifth card (estate) in Player 1's hand is gone:  ");
		testAssert( (0 == (G.hand[0][4] == estate) ) );  // run testAssert
		printf("\n");

		printf("Player 1 has 1 buys:  ");
		testAssert(G.numBuys == 1);  // run testAssert
		printf("\n");
		printf("numBuys is: %d \n\n", G.numBuys);

		printf("     Verify Player 1 has 2 buys (due to assignment2 bug):  ");
		testAssert(G.numBuys == 2);  // run testAssert
		printf("\n");

		printf("Player 1 has 4 coins:  ");
		testAssert(G.coins == 4);  // run testAssert
		printf("\n");

		initializeGame(2, k, seed, &H);  // initialize game state for 2 players

		H.hand[0][0] = baron;  // player 1 first card
		H.hand[0][1] = smithy;  // player 1 second card
		H.hand[0][2] = embargo;  // player 1 third card
		H.hand[0][3] = minion;  // player 1 fourth card
		H.hand[0][4] = smithy;  // player 1 fifth card
		H.deck[0][4] = embargo;  // deck fifth card
		H.deck[0][5] = gold;  // deck sixth card
		H.deck[0][6] = silver;  // deck seventh card
		H.deck[0][7] = copper;  // deck seventh card
		H.handCount[0] = 5;  // player 1 has 5 cards in their hand
		H.numActions = 2;  // player 1 has 2 actions
		H.deckCount[0] = 8;  // player 1 has 8 cards in their deck
		H.playedCardCount = 0;  // player 1 has not played any cards
		H.coins = 0;  // player 1 has 0 coins
		choice1 = estate;  // card to be trashed
		H.numBuys = 0;  // player 1 has no buys

		printf("	Test with no estate in hand \n");

		// currentPlayer, gameState, choice1
		// card, choice1, choice2, choice3, gameState, handPos, bonus
		cardEffect(baron, choice1, choice2, 0, &H, 0, &bonus);
		printf("\n	Results:\n\n");

		printf("Verify Player 1 has 1 actions:  ");
		testAssert(H.numActions == 1);  // run testAssert
		printf("\n");

		printf("Verify error Player 1 has 2 actions:  ");
		testAssert(H.numActions == 2);  // run testAssert
		printf("\n");

		printf("Verify %s is at the top of Player 1's discard pile:  ", TESTCARD);
		testAssert(H.playedCards[0] == baron);  // run testAssert
		printf("\n");

		printf("Verify Player 1's playedCardCount has been incremented to 1:  ");
		testAssert(H.playedCardCount == 1);  // run testAssert
		printf("\n");

		printf("Verify Player 1 has 5 cards in their hand:  ");
		testAssert(H.handCount[0] == 5);  // run testAssert
		printf("\n");

		printf("Verify Player 1 has 8 cards in their deck:  ");
		testAssert(H.deckCount[0] == 8);  // run testAssert
		printf("\n");

		printf("Verify a sixth card (estate) in Player 1's hand is added:  ");
		testAssert( (0 == (H.hand[0][5] == estate) ) );  // run testAssert
		printf("\n");

		printf("Player 1 has 1 buys:  ");
		testAssert(H.numBuys == 1);  // run testAssert
		printf("\n");
		printf("numBuys is: %d \n\n", H.numBuys);

		printf("     Verify Player 1 has 2 buys (due to assignment2 bug):  ");
		testAssert(H.numBuys == 2);  // run testAssert
		printf("\n");

	return 0;
}
