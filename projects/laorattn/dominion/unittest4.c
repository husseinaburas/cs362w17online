/* -----------------------------------------------------------------------
 * Unit test for updateCoins function
 * Author: Namtalay Laorattanavech
 * Include the following lines in your makefile:
 *
 * unittest1: unittest3.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"



int main() {
    int i,j;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
	int player = 0;
    
	printf("Unittest4: updateCoins\n");
	printf("Starting the game...\n");
	int maingame = initializeGame(numPlayer, k, seed, &G);
	assert(maingame==0);
	
	
	int player1_num_cards = G.handCount[0];
	int num_copper = 0;
	int num_silver = 0;
	int num_gold = 0;
	int num_bonus = floor( Random() * player1_num_cards );
	
	for (i = 0; i < player1_num_cards; i++){
		if (G.hand[0][i] == copper){
			num_copper++;
		}
		else if (G.hand[0][i] == silver){
			num_silver++;
		}
		else if (G.hand[0][i] == silver){
			num_gold++;
		}
	}	
	
	int total_coins = num_copper*1 + num_silver*2 + num_gold*3 + num_bonus;
	updateCoins(0, &G, num_bonus);
	assert(G.coins == total_coins && ": failed\n");
   

    printf("All tests passed!\n");

    return 0;
}