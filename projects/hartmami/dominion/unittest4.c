/***********************************************************************************************
**
**  Author:       Michael Hartman
**
**  Date:           2017-02-06
**
**  Filename:       unittest4.c
**
**  Description:    unittest for the function buyCard() in dominion tests:
**
**  verify what player is buying the card
**  verify number of buys is sufficent
**  verify there is an avaiable card supply of the target card
**  verify player has enough coins to buy the card
**  verify card is added to top of discard pile
**  verify other cards arent changed
**  verify numBuys, coins are correct
**  if using the DEBUG the last printf statment is missing the last %d and closing parenthesis.
**  try to buy a card without enough coins
**  try to buy a card with 0 supply
**  try to buy a card with 0 buys
**  verify player 2 is unaffected
**
***********************************************************************************************/

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

	printf("\nTesting Unit: %s \n\n", TESTUNIT);

		G.handCount[0] = 5;  // player 1 has 5 cards in their hand
		G.deckCount[0] = 7;  // player 1 has 7 cards in their deck
		G.handCount[1] = 5;  // player 1 has 5 cards in their hand
		G.deckCount[1] = 7;  // player 1 has 7 cards in their deck
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

			printf("Verify Player 2 has 7 cards in their deck:  ");
			testAssert(G.deckCount[1] == 7);  // run testAssert
			printf("\n");

			printf("Verify Player 2 has 5 cards in their hand:  ");
			testAssert(G.handCount[1] == 5);  // run testAssert
			printf("\n");

			printf("Player1 has: %d coin:  \n", G.coins);
			printf("Player1 has: %d buys:  \n", G.numBuys);
			printf("There are: %d empty piles:  \n\n", emptyPile);

		printf("	BUY TESTS\n\n");

			printf("	Test player1 village buy: \n");
			//supplyPos, gameState
			success = buyCard(14, &G);  //verify card bought

			printf("\nVerify player1 buy village successful: ");
			testAssert(success == 0);  // run testAssert
			printf("\n");

			printf("Verify player1 has 2 coins:  ");
			testAssert(G.coins == 2);  // run testAssert
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

			printf("Verify Player 2 has 7 cards in their deck:  ");
			testAssert(G.deckCount[1] == 7);  // run testAssert
			printf("\n");

			printf("Verify Player 2 has 5 cards in their hand:  ");
			testAssert(G.handCount[1] == 5);  // run testAssert
			printf("\n");

			printf("Verify village card is at the top of Player 1's discard pile:  ");
			testAssert(G.playedCards[0] == village);  // run testAssert
			printf("\n");

			printf("Player1 has: %d coin:  \n", G.coins);
			printf("Player1 has: %d buys:  \n\n", G.numBuys);

			printf("	Test player1 village buy without enough coins; 1 buy added: \n");

			G.numBuys = 1;
			//supplyPos, gameState
			success = buyCard(14, &G);  //verify card bought

			printf("\nVerify player1 buy village unsuccessful: ");
			testAssert(success == -1);  // run testAssert
			printf("\n");

			printf("Verify player1 has 2 coins:  ");
			testAssert(G.coins == 2);  // run testAssert
			printf("\n");

			printf("Verify player1 has 1 buys:  ");
			testAssert(G.numBuys == 1);  // run testAssert
			printf("\n");

			printf("Verify Player 1 has 7 cards in their deck:  ");
			testAssert(G.deckCount[0] == 7);  // run testAssert
			printf("\n");

			printf("Verify Player 1 has 5 cards in their hand:  ");
			testAssert(G.handCount[0] == 5);  // run testAssert
			printf("\n");

			printf("Verify Player 2 has 7 cards in their deck:  ");
			testAssert(G.deckCount[1] == 7);  // run testAssert
			printf("\n");

			printf("Verify Player 2 has 5 cards in their hand:  ");
			testAssert(G.handCount[1] == 5);  // run testAssert
			printf("\n");

			printf("Player1 has: %d coin:  \n", G.coins);
			printf("Player1 has: %d buys:  \n\n", G.numBuys);

			printf("	Test player1 village buy without enough buys; 1 coin added, 1 buy removed: \n");

			G.numBuys = 0;
			G.coins = 3;
			//supplyPos, gameState
			success = buyCard(14, &G);  //verify card bought

			printf("\nVerify player1 buy village unsuccessful: ");
			testAssert(success == -1);  // run testAssert
			printf("\n");

			printf("Verify player1 has 3 coins:  ");
			testAssert(G.coins == 3);  // run testAssert
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

			printf("Verify Player 2 has 7 cards in their deck:  ");
			testAssert(G.deckCount[1] == 7);  // run testAssert
			printf("\n");

			printf("Verify Player 2 has 5 cards in their hand:  ");
			testAssert(G.handCount[1] == 5);  // run testAssert
			printf("\n");

			printf("Player1 has: %d coin:  \n", G.coins);
			printf("Player1 has: %d buys:  \n\n", G.numBuys);

			printf("	Test player1 village buy without enough supply avaiable; 1 buy added, all village supply removed: \n");

			G.numBuys = 1;
			G.supplyCount[village] = 0;
			//supplyPos, gameState
			success = buyCard(14, &G);  //verify card bought

			printf("\nVerify player1 buy village unsuccessful: ");
			testAssert(success == -1);  // run testAssert
			printf("\n");

			printf("Verify player1 has 3 coins:  ");
			testAssert(G.coins == 3);  // run testAssert
			printf("\n");

			printf("Verify player1 has 1 buys:  ");
			testAssert(G.numBuys == 1);  // run testAssert
			printf("\n");

			printf("Verify Player 1 has 7 cards in their deck:  ");
			testAssert(G.deckCount[0] == 7);  // run testAssert
			printf("\n");

			printf("Verify Player 1 has 5 cards in their hand:  ");
			testAssert(G.handCount[0] == 5);  // run testAssert
			printf("\n");

			printf("Verify Player 2 has 7 cards in their deck:  ");
			testAssert(G.deckCount[1] == 7);  // run testAssert
			printf("\n");

			printf("Verify Player 2 has 5 cards in their hand:  ");
			testAssert(G.handCount[1] == 5);  // run testAssert
			printf("\n");

			printf("Player1 has: %d coin:  \n", G.coins);
			printf("Player1 has: %d buys:  \n\n", G.numBuys);

	return 0;
}
