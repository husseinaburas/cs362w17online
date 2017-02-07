/***********************************************************************************************
**
**  Author:       Michael Hartman
**
**  Date:           2017-02-06
**
**  Filename:       unittest1.c
**
**  Description:    unittest for the function isGameOver() in dominion tests:
**
**  verify preconditions
**  verify treasure_map is 26
**  verify game isn't over when proviences = 8 and 0 supply piles are empty
**  verify game isn't over when proviences = 8 and 1 supply piles are empty
**  verify game isn't over when proviences = 8 and 2 supply piles are empty
**  verify game is over when proviences = 8 and 3 supply piles are empty
**  verify game isn't over when proviences = 8 and 2 supply piles are empty
**  verify game isn't over when proviences = 1 and 2 supply piles are empty
**  verify game is over when proviences = 0 and 2 supply piles are empty
**
***********************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define TESTUNIT "isGameOver()"

int main()
{
	int i = 0;
	int emptyPile = 0;
	int seed = 772;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(2, k, seed, &G);  // initialize game state for 2 players

	printf("\nTesting Unit: %s \n\n", TESTUNIT);

	printf("	PRECONDITION TESTS\n\n");

		printf("Verify treasure_map is 26:  ");  // verify provinces are all present
		testAssert(treasure_map == 26);  // run testAssert
		printf("\n");

		G.supplyCount[province] = 8;
		printf("Verify there are 8 provinces:  ");  // verify provinces are all present
		testAssert(G.supplyCount[province] == 8);  // run testAssert
		printf("\n");

		printf("Verify the count of empty piles is < 3:  ");
		while( i < treasure_map)  // count the empty piles
		{
			if (G.supplyCount[i] == 0)
			{
				emptyPile++;
			}
			i++;
		}
		testAssert(emptyPile < 3);  // run testAssert
		printf("\n");
		emptyPile = 0;  // return emptyPile to 0
		i = 0; // return i to 0

		printf("Verify the count of empty piles is 0:  ");
		testAssert(emptyPile == 0);  // run testAssert
		printf("\n");

		printf("Verify game isn't over:  ");
		testAssert(isGameOver(&G) == 0);  // run testAssert
		printf("\n");

	printf("	EMPTY PILE TESTS\n\n");

		printf("Verify game isn't over with 1 empty pile:  ");
		G.supplyCount[duchy] = 0;
		testAssert(isGameOver(&G) == 0);  // run testAssert
		printf("\n");

		printf("Verify game isn't over with 2 empty piles:  ");
		G.supplyCount[estate] = 0;
		testAssert(isGameOver(&G) == 0);  // run testAssert
		printf("\n");

		printf("Verify the count of empty piles is < 3:  ");
		while( i < treasure_map)  // count the empty piles
		{
			if (G.supplyCount[i] == 0)
			{
				emptyPile++;
			}
			i++;
		}
		testAssert(emptyPile < 3);  // run testAssert
		printf("\n");
		emptyPile = 0;  // return emptyPile to 0
		i = 0; // return i to 0

		printf("Verify game is over with 3 empty piles:  ");
		G.supplyCount[adventurer] = 0;
		testAssert(isGameOver(&G) == 1);  // run testAssert
		printf("\n");

		printf("Verify the count of empty piles is 3:  ");
		while( i < treasure_map)  // count the empty piles
		{
			if (G.supplyCount[i] == 0)
			{
				emptyPile++;
			}
			i++;
		}
		testAssert(emptyPile == 3);  // run testAssert
		printf("\n");
		emptyPile = 0;  // return emptyPile to 0
		i = 0; // return i to 0

	printf("	PROVINCE PILE TESTS\n\n");

		G.supplyCount[adventurer] = 1;  // return 1 pile

		printf(":Verify there are 8 provinces:  ");
		G.supplyCount[province] = 8;
		testAssert(G.supplyCount[province] == 8);  // run testAssert
		printf("\n");

		printf("Verify game isn't over with 8 provinces left:  ");
		G.supplyCount[province] = 8;
		testAssert(isGameOver(&G) == 0);  // run testAssert
		printf("\n");

		printf("Verify game isn't over with 1 province left:  ");
		G.supplyCount[province] = 1;
		testAssert(isGameOver(&G) == 0);  // run testAssert
		printf("\n");

		printf("Verify game is over with no provinces left:  ");
		G.supplyCount[province] = 0;
		testAssert(isGameOver(&G) == 1);  // run testAssert
		printf("\n");

	return 0;
}
