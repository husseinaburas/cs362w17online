/***********************************************************************************************
**
**  Author:       Michael Hartman
**
**  Date:           2017-02-06
**
**  Filename:       unittest2.c
**
**  Description:    unittest for the function updateCoins() in dominion tests:
**
**  verify preconditions
**  verify adding a copper to player1's hand adds 1 coin
**  verify adding a silver to player1's hand adds 2 coins
**  verify adding a gold to player1's hand adds 3 coins
**  verify removing a copper from player1's hand removes 1 coin
**  verify removing a silver from player1's hand removes 2 coins
**  verify removing a gold from player1's hand removes 3 coins
**  verify adding 1 bonus adds 1 coin
**  verify adding 9 bonus adds 9 coins
**  verify adding -1 bonus produces error
**  verify error (adding -1 bonus has no effect)
**
***********************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define TESTUNIT "updateCoins()"

int main()
{
	int seed = 772;
	int playerOneCoins = 0;
	int playerTwoCoins = 0;
	int success = -1;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(2, k, seed, &G);  // initialize game state for 2 players

	printf("\nTesting Unit: %s \n\n", TESTUNIT);

	printf("	PRECONDITION TESTS\n\n");

	//player, gameState, bonus
		updateCoins(0, &G, 0);
		playerOneCoins = G.coins;

		updateCoins(1, &G, 0);
		playerTwoCoins = G.coins;

		printf("Verify player1 has >= 0 coins:  ");
		testAssert(playerOneCoins >= 0);  // run testAssert
		printf("\n");

		printf("Verify player2 has >= 0 coins:  ");
		testAssert(playerTwoCoins >= 0);  // run testAssert
		printf("\n");

		printf("Player1 has: %d coin:  \n", playerOneCoins);
		printf("Player2 has: %d coins:  ", playerTwoCoins);
		printf("\n\n");

	printf("	ADDING TREASURE TESTS\n\n");

		gainCard(copper, &G, 2, 0);  // add a copper to player1's hand
		updateCoins(0, &G, 0);  //  update
		printf("Verify adding a copper to player1's hand adds 1 coin:  ");
		testAssert(playerOneCoins + 1 == G.coins);  // run testAssert
		printf("\n");
		playerOneCoins = G.coins;

		gainCard(silver, &G, 2, 0);  // add a silver to player1's hand
		updateCoins(0, &G, 0);  //  update
		printf("Verify adding a silver to player1's hand adds 2 coins:  ");
		testAssert(playerOneCoins + 2 == G.coins);  // run testAssert
		printf("\n");
		playerOneCoins = G.coins;

		gainCard(gold, &G, 2, 0);  // add a gold to player1's hand
		updateCoins(0, &G, 0);  //  update
		printf("Verify adding a gold to player1's hand adds 3 coins:  ");
		testAssert(playerOneCoins + 3 == G.coins);  // run testAssert
		printf("\n");
		playerOneCoins = G.coins;

		printf("	REMOVING TREASURE TESTS\n\n");

		printf("Verify card to remove is a copper:  ");
		testAssert(G.hand[0][G.handCount[0] - 3] == copper);  // run testAssert
		printf("\n");

		printf("Verify the card in Player 1's hand is a copper:  ");
		testAssert(G.hand[0][4] == copper);  // run testAssert
		printf("\n");

		discardCard((G.handCount[0] - 3), 0, &G, 0);   // remove a copper from player1's hand
		updateCoins(0, &G, 0);  //  update
		printf("Verify removing a copper from player1's hand removes 1 coin:  ");
		testAssert(playerOneCoins - 1 == G.coins);  // run testAssert
		printf("\n");
		playerOneCoins = G.coins;

		printf("Verify card to remove is a silver:  ");
		testAssert(G.hand[0][G.handCount[0] - 1] == silver);  // run testAssert
		printf("\n");

		printf("Verify the card in Player 1's hand is a silver:  ");
		testAssert(G.hand[0][6] == silver);  // run testAssert
		printf("\n");

		discardCard(6, 0, &G, 0);   // remove a silver from player1's hand
		updateCoins(0, &G, 0);  //  update
		printf("Verify removing a silver from player1's hand removes 2 coins:  ");
		testAssert(playerOneCoins - 2 == G.coins);  // run testAssert
		printf("\n");
		playerOneCoins = G.coins;

		printf("Verify card to remove is a gold:  ");
		testAssert(G.hand[0][G.handCount[0] - 1] == gold);  // run testAssert
		printf("\n");

		printf("Verify the card in Player 1's hand is a gold:  ");
		testAssert(G.hand[0][5] == gold);  // run testAssert
		printf("\n");

		discardCard(5, 0, &G, 0);   // remove a gold from player1's hand
		updateCoins(0, &G, 0);  //  update
		printf("Verify removing a gold from player1's hand removes 3 coins:  ");
		testAssert(playerOneCoins - 3 == G.coins);  // run testAssert
		printf("\n");
		playerOneCoins = G.coins;

		printf("	BONUS TESTS\n\n");

		printf("player1 coins: %d \n",G.coins);
		printf("player1 expected coins: %d \n\n",playerOneCoins);
		gainCard(copper, &G, 2, 0);  // add a copper to player1's hand
		updateCoins(0, &G, 1);  //  update
		printf("Verify adding a copper and 1 bonus adds 2 coins:  ");
		testAssert(playerOneCoins + 2 == G.coins);  // run testAssert
		playerOneCoins = G.coins;
		printf("player1 coins: %d \n",G.coins);
		printf("player1 expected coins: %d \n",playerOneCoins);
		printf("\n");

		gainCard(silver, &G, 2, 0);  // add a silver to player1's hand
		updateCoins(0, &G, 9);  //  update
		printf("Verify adding a silver and 9 bonus adds 11 coins:  ");
		testAssert(playerOneCoins + 11 == G.coins);  // run testAssert
		playerOneCoins = G.coins;
		printf("player1 coins: %d \n",G.coins);
		printf("player1 expected coins: 17 \n");
		printf("\n");

		gainCard(gold, &G, 2, 0);  // add a gold to player1's hand
		success = updateCoins(0, &G, -1);  //  update
		printf("Verify adding a gold and -1 bonus doesn't work:  ");
		testAssert(success == -1);  // run testAssert
		playerOneCoins = G.coins;
		printf("player1 coins: %d \n",G.coins);
		printf("player1 expected coins: 17 \n");
		printf("\n");

		gainCard(gold, &G, 2, 0);  // add a gold to player1's hand
		success = updateCoins(0, &G, -1);  //  update
		printf("error Verify adding a gold and -1 bonus adds 3 coins:  ");
		testAssert(playerOneCoins + 3 == G.coins); // run testAssert
		printf("\n");
		playerOneCoins = G.coins;
		printf("player1 coins: %d \n",G.coins);
		printf("player1 expected coins: %d \n",playerOneCoins);

	return 0;
}
