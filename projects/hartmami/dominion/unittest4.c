
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define TESTUNIT "buyCard()"

int main()
{
	int i = 0;
	int success = -1;
	int emptyPile = 0;
	int seed = 772;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(2, k, seed, &G);  // initialize game state for 2 players

// verify what player is buying the card
// verify number of buys is sufficent
// verify there is an avaiable card supply of the target card
// verify player has enough coins to buy the card

// verify card is added to top of discard pile
// verify other cards arent changed
// verify numBuys, num coins are correct
// if using the DEBUG the last printf statment is missing the last %d and closing parentsis.

// try to buy a card without enough coins
// try to buy a card with 0 supply
// try to buy a card wilh 0 buys

// verify player 2 is unaffected

	printf("\nTesting Unit: %s \n\n", TESTUNIT);

		G.handCount[0] = 5;  // player 1 has 5 cards in their hand
		G.deckCount[0] = 7;  // player 1 has 7 cards in their deck
		G.coins = 5;  // player 1 has 5 coins
		G.numBuys = 1;

		printf("	PRECONDITION TESTS\n\n");

			printf("Verify player1 has 5 coins:  ");
			testAssert(G.coins == 5);  // run testAssert
			printf("\n");

			printf("Verify player1 has 1 buys:  ");
			testAssert(G.numBuys == 1);  // run testAssert
			printf("\n");

			printf("Verify the count of empty piles is 0:  ");
			while( i < treasure_map)  // count the empty piles
			{
				if (G.supplyCount[i] == 0)
				{
					emptyPile++;
				}
				i++;
			}
			testAssert(emptyPile == 0);  // run testAssert
			printf("\n");

			printf("Verify Player 1 has 7 cards in their deck:  ");
			testAssert(G.deckCount[0] == 7);  // run testAssert
			printf("\n");

			printf("Verify Player 1 has 5 cards in their hand:  ");
			testAssert(G.handCount[0] == 5);  // run testAssert
			printf("\n");

			printf("Player1 has: %d coin:  \n", G.coins);
			printf("Player1 has: %d buys:  \n", G.numBuys);
			printf("There are: %d empty piles:  \n\n", emptyPile);

		printf("	POST TESTS\n\n");

//supplyPos, gameState
			success = buyCard(8, &G);  //verify card bought

			printf("	player1 buy sucessful: ");
			testAssert(success == 0);  // run testAssert
			printf("\n\n");

			printf("Verify player1 has 5 coins:  ");
			testAssert(G.coins == 5);  // run testAssert
			printf("\n");

			printf("Verify player1 has 0 buys:  ");
			testAssert(G.numBuys == 0);  // run testAssert
			printf("\n");

			printf("Verify Player 1 has 7 cards in their deck:  ");
			testAssert(G.deckCount[0] == 7);  // run testAssert
			printf("\n");

			printf("Verify Player 1 has 5 cards in their hand:  ");
			testAssert(G.handCount[0] == 5);  // run testAssert
			printf("\n");

			printf("Verify ??card is at the top of Player 1's discard pile:  "); // get card
			testAssert(G.playedCards[0] == cardhere);  // run testAssert
			printf("\n");

			printf("Player1 has: %d coin:  \n", G.coins);
			printf("Player1 has: %d buys:  \n\n", G.numBuys);

	return 0;
}
