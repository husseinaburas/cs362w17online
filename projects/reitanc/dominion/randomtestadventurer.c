/*  randomtestadventurer.c
*
*	CS362 - W17 Assignment 4
*
*/

/*
 * Include the following lines in your makefile:
 *
 *	randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define DEBUG 0
#define NOISY_TEST 1

int main(int argc, char** argv){

/* Initialize variables for Testing */
	int i, n, p, RetVal;
	/*int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;*/
    int numPlayers = 2;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	struct gameState G, testG;

	int seedValue = atoi(argv[1]);

	PutSeed(seedValue);

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seedValue, &G);

	for (n=0; n < 50; n++){
		initializeGame(numPlayers, k, seedValue, &G);
		for (i = 0; i < 2; i++)
			{
				/* Add a bonus coin bias to attempt to push the Coins Count up over 6 to be able to play Adventurer. */
				p = floor(Random() * 6);
				G.whoseTurn = i;
				updateCoins(i, &G, p);
				memcpy(&testG, &G, sizeof(struct gameState));

				if (G.coins >= 6)
				{
					printf("\n Player %i is capable of playing Adventurer, G.coins = %i. ", i+1, G.coins);
					/*cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);*/
					RetVal = playAdventurer(&testG);
				}
				updateCoins(i, &testG, p);

				int TestCoins = testG.coins - G.coins;
				/*int discarded = testG.discardCount[i]-G.discardCount[i];*/
				if (RetVal == 0 && 
					TestCoins >= 1)
				{
					printf(">>>>> SUCCESS: Player %i discarded after playing Adventurer, net coins are: %i.<<<<<\n", i+1, TestCoins);
				}else
				{
					printf(">>>>> FAILED: Player %i Net Coins is: %i <<<<<\n", i+1, TestCoins);
				}
			}
			printf("\n");
		}

}