
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
	int bug = 0;  // if initialized to 0 then test will run additional known bug tests
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

		printf("	Playing %s\n", TESTCARD);

		// use playcard instead to track coins aswell

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

	return 0;
}
