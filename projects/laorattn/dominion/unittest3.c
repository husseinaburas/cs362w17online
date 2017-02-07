/* -----------------------------------------------------------------------
 * Unit test for fullDeckCount function
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
    
	printf("Unittest3: fullDeckCount\n");
	printf("Starting the game...\n");
	int maingame = initializeGame(numPlayer, k, seed, &G);
	assert(maingame==0);
	
	
	int num_cards = treasure_map;
	
	for(i=0;i<num_cards;i++){
		int count=0;
		int card=i;
		//deck
		for(j=0;j<G.deckCount[player];j++){
			if(G.deck[player][j] == i){
				count++;
			}
		}
		//hand
		for(j=0;j<G.handCount[player];j++){
			if(G.hand[player][j] == i){
				count++;
			}
		}
		//discard
		for(j=0;j<G.discardCount[player];j++){
			if(G.discard[player][j] == i){
				count++;
			}
		}
		//check if match
		printf("Checking: fullDeckCount function matches the count");
		assert(fullDeckCount(player, card, &G)==count && ": failed\n");
	}
	
	
	
   

    printf("All tests passed!\n");

    return 0;
}