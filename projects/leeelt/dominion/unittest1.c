/* -----------------------------------------------------------------------
 * Author: Elton Lee
 * Date: 2-4-2017
 * unittest1.c
 * unit test for updateCoins function
 * Modified from testUpdateCoins.c provided from OSU CS362 Winter Quarter 2017
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
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
	int p, r, handCount;
	int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++){
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
	printf ("TESTING updateCoins():\n");
	for (p=0; p < numPlayer; p++){
		printf("Test player %d with 0 treasures and 0 bonus.\n", p+1);
		memset(&G, 23, sizeof(struct gameState)); // clear the game state
		r = initializeGame(numPlayer, k, seed, &G);  // initialize a new game
		G.handCount[p] = 0;  // set the number of cards on hand
		updateCoins(p, &G, 0);
		printf("G.coins = %d, expected = %d\n", G.coins, 0);
		assert(G.coins == 0);
	}
	printf("All tests passed!\n");
	return 0;
}