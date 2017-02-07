/* -----------------------------------------------------------------------
 * Author: Elton Lee
 * Date: 2-4-2017
 * unittest1.c
 * unit test for updateCoins function
 * Modified from testUpdateCoins.c provided from OSU CS362 Winter Quarter 2017
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(){
	int i;
	int seed = 1000;
	int numPlayer = 2;
	int p;
	int hiHandCount = 10;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

	printf ("TESTING updateCoins():\n");
	for (p=0; p < numPlayer; p++){
		memset(&G, 23, sizeof(struct gameState)); // clear the game state
		initializeGame(numPlayer, k, seed, &G);  // initialize a new game
		printf("\nRunning tests for player %d\n", p+1);
		// 0 treasures, 0 bonus
		printf("Test 1. 0 treasures and 0 bonus.\n");
		G.handCount[p] = 0;  // set the number of cards on hand
		updateCoins(p, &G, 0);
		printf("G.coins = %d, expected = %d\n", G.coins, 0);
		assert(G.coins == 0);

		// 0 treasure, 100 bonus
		printf("Test 2. 0 treasures and 100 bonus.\n");
		G.handCount[p]=0;
		int bonus = 100;
		updateCoins(p, &G, bonus);
		printf("G.coins = %d, expected = %d\n", G.coins, bonus);
		assert(G.coins == bonus);

		// 3 treasures, copper, silver, gold
		printf("Test 3. copper, silver, gold.\n");
		G.handCount[p]=3;
		G.hand[p][0] = copper;
		G.hand[p][1] = silver;
		G.hand[p][2] = gold;
		updateCoins(p, &G, 0);
		printf("G.coins = %d, expected = %d\n", G.coins, 6);
		assert(G.coins == 6);

		// Testing hand with hiHandCount coppers.
		printf("Test 4. %d coppers.\n",hiHandCount);
		G.handCount[p]=hiHandCount;
		for (i=0; i < hiHandCount; ++i){
			G.hand[p][i] = copper;
		}
		updateCoins(p, &G, 0);
		printf("G.coins = %d, expected = %d\n", G.coins, hiHandCount*1);
		assert(G.coins == hiHandCount*1);

		// Testing hand with hiHandCount silvers.
		printf("Test 5. %d silvers.\n",hiHandCount);
		G.handCount[p]=hiHandCount;
		for (i=0; i < hiHandCount; ++i){
			G.hand[p][i] = silver;
		}
		updateCoins(p, &G, 0);
		printf("G.coins = %d, expected = %d\n", G.coins, hiHandCount*2);
		assert(G.coins == hiHandCount*2);

		// Testing hand with hiHandCount golds.
		printf("Test 6. %d golds.\n",hiHandCount);
		G.handCount[p]=hiHandCount;
		for (i=0; i < hiHandCount; ++i){
			G.hand[p][i] = gold;
		}
		updateCoins(p, &G, 0);
		printf("G.coins = %d, expected = %d\n", G.coins, hiHandCount*3);
		assert(G.coins == hiHandCount*3);
	}
	printf("All tests passed!\n");
	return 0;
}