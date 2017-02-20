/***********************************************************************************************
**
**  Author:       Michael Hartman
**
**  Date:           2017-02-06
**
**  Filename:       unittest3.c
**
**  Description:    unittest for the function discardCard() in dominion tests:
**
**  verify preconditions
**  verify correct card is discarded
**  verify playedCardCount is incremented
**  verify player1's hand is as expected
**  verify player1's deck is as expected
**  verify discardCount is incremented
**  verify player1 cannot discard more cards than in hand
**  verify player2 cannot discard more cards than in hand
**  verify trashFlag ensures playedCardCount is NOT incremented
**  verify trashFlag ensures card is NOT discarded
**  verify player1's hand is as expected with trashFlag
**  verify player1's deck is as expected with trashFlag
**
***********************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define TESTUNIT "discardCard()"

int main()
{
	int seed = 772;
	int playerOneHandCount = 0;
	int playerOneDeckCount = 0;
	int playerOneDiscardCount = 0;
	int playerTwoHandCount = 0;
	int playerTwoDeckCount = 0;
	int playerTwoDiscardCount = 0;
	struct gameState G;
	struct gameState H;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(2, k, seed, &G);  // initialize game state for 2 players

	printf("\nTesting Unit: %s \n\n", TESTUNIT);

	printf("	PRECONDITION TESTS\n");

		playerOneHandCount = G.handCount[0];
		playerOneDeckCount = G.deckCount[0];
		playerOneDiscardCount = G.discardCount[0];
		G.hand[0][0] = mine;
		playerTwoHandCount = G.handCount[1];
		playerTwoDeckCount = G.deckCount[1];
		playerTwoDiscardCount = G.discardCount[1];

		printf("\nplayer 1 handCount is:  %d", playerOneHandCount);
		printf("\nplayer 1 deckCount is:  %d", playerOneDeckCount);
		printf("\nplayer 1 discardCount is:  %d", playerOneDiscardCount);
		printf("\nplayer 2 handCount is:  %d", playerTwoHandCount);
		printf("\nplayer 2 deckCount is:  %d", playerTwoDeckCount);
		printf("\nplayer 2 discardCount is:  %d", playerTwoDiscardCount);
		printf("\n\n");

		printf("Player 1 has 5 cards in their hand:  ");
		testAssert(G.handCount[0] == 5);  // run testAssert
		printf("\n");

		printf("Player 1 has 1 actions:  ");
		testAssert(G.numActions == 1);  // run testAssert
		printf("\n");

		printf("Player 1 has 5 cards in their deck:  ");
		testAssert(G.deckCount[0] == 5);  // run testAssert
		printf("\n");

		printf("Player 1 has not yet played a card:  ");
		testAssert(G.playedCardCount == 0);  // run testAssert
		printf("\n");

	printf("	HAND, DECK, AND DISCARD TESTS\n\n");

		// handPos, currentPlayer, gameState, trashFlag
		discardCard(0, 0, &G, 0);

		printf("Verify mine is at the top of Player 1's discard pile:  ");
		testAssert(G.playedCards[0] == mine);  // run testAssert
		printf("\n");

		printf("Verify Player 1's playedCardCount has been incremented to 1:  ");
		testAssert(G.playedCardCount == 1);  // run testAssert
		printf("\n");

		printf("Verify Player 1 has 4 cards in their hand:  ");
		testAssert(G.handCount[0] == 4);  // run testAssert
		printf("\n");

		printf("Verify Player 1 has 5 cards in their deck:  ");
		testAssert(G.deckCount[0] == 5);  // run testAssert
		printf("\n");

		printf("Verify Player 1's discardCount is 1:  ");
		testAssert(G.discardCount[0] == 1);  // run testAssert
		printf("\n");

		discardCard(0, 0, &G, 0);
		discardCard(0, 0, &G, 0);
		discardCard(0, 0, &G, 0);
		discardCard(0, 0, &G, 0);
		discardCard(0, 0, &G, 0);
		printf("Verify Player 1 cannot discard more cards than in hand:  ");
		testAssert(G.handCount[0] == 0);  // run testAssert
		printf("\n");

		discardCard(0, 1, &G, 0);

		printf("Verify Player 2 cannot discard more cards than in hand:  ");
		testAssert(G.handCount[1] == 0);  // run testAssert

		playerOneHandCount = G.handCount[0];
		playerOneDeckCount = G.deckCount[0];
		playerOneDiscardCount = G.discardCount[0];
		playerTwoHandCount = G.handCount[1];
		playerTwoDeckCount = G.deckCount[1];
		playerTwoDiscardCount = G.discardCount[1];
		printf("\nplayer 1 handCount is:  %d", playerOneHandCount);
		printf("\nplayer 1 deckCount is:  %d", playerOneDeckCount);
		printf("\nplayer 1 discardCount is:  %d", playerOneDiscardCount);
		printf("\nplayer 2 handCount is:  %d", playerTwoHandCount);
		printf("\nplayer 2 deckCount is:  %d", playerTwoDeckCount);
		printf("\nplayer 2 discardCount is:  %d", playerTwoDiscardCount);
		printf("\n\n");

	printf("	TRASHFLAG TESTS\n\n");

	  printf("	Make a new gameState\n");
		initializeGame(2, k, seed, &H);  // initialize game state for 2 players

			playerOneHandCount = H.handCount[0];
			playerOneDeckCount = H.deckCount[0];
			playerOneDiscardCount = H.discardCount[0];
			H.hand[0][0] = mine;
			playerTwoHandCount = H.handCount[1];
			playerTwoDeckCount = H.deckCount[1];
			playerTwoDiscardCount = H.discardCount[1];
			printf("\nplayer 1 handCount is:  %d", playerOneHandCount);
			printf("\nplayer 1 deckCount is:  %d", playerOneDeckCount);
			printf("\nplayer 1 discardCount is:  %d", playerOneDiscardCount);
			printf("\nplayer 2 handCount is:  %d", playerTwoHandCount);
			printf("\nplayer 2 deckCount is:  %d", playerTwoDeckCount);
			printf("\nplayer 2 discardCount is:  %d", playerTwoDiscardCount);
			printf("\n\n");

	// handPos, currentPlayer, gameState, trashFlag
	discardCard(0, 0, &H, 1);

	printf("Verify mine is NOT at the top of Player 1's discard pile:  ");
	testAssert(H.playedCards[0] != mine);  // run testAssert
	printf("\n");

	printf("Verify Player 1's playedCardCount is 0:  ");
	testAssert(H.playedCardCount == 0);  // run testAssert
	printf("\n");

	printf("Verify Player 1 has 4 cards in their hand:  ");
	testAssert(H.handCount[0] == 4);  // run testAssert
	printf("\n");

	printf("Verify Player 1 has 5 cards in their deck:  ");
	testAssert(H.deckCount[0] == 5);  // run testAssert
	printf("\n");

	printf("Verify Player 1's discardCount is 1:  ");
	testAssert(H.discardCount[0] == 1);  // run testAssert
	printf("\n");

	printf("player 1 handCount is:  %d", H.handCount[0]);
	printf("\nplayer 1 deckCount is:  %d", H.deckCount[0]);
	printf("\nplayer 1 discardCount is:  %d", H.discardCount[0]);
	printf("\nplayer 2 handCount is:  %d", H.handCount[1]);
	printf("\nplayer 2 deckCount is:  %d", H.deckCount[1]);
	printf("\nplayer 2 discardCount is:  %d", H.discardCount[1]);
	printf("\n\n");

	return 0;
}
