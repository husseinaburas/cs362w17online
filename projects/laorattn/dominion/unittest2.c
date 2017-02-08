/* -----------------------------------------------------------------------
 * Unit test for buyCard function
 * Author: Namtalay Laorattanavech
 * Include the following lines in your makefile:
 *
 * unittest1: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"



int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
	
    
	printf("Unittest2: buyCard\n");
	G.numBuys=2;
	G.coins=2;
	printf("Buying with not enough coin [should not be able to]\n");
	assert(buyCard(2,&G)==-1);	
	
	G.numBuys=2;
	G.coins=10;
	printf("Buying with enough coin\n");
	assert(buyCard(2,&G)==-1);	
	
	G.numBuys = -1;
	printf("Buying without any buying left [should not be able to]\n");
	assert(buyCard(2,&G)==-1);	
	
	
	

    printf("All tests passed!\n");

    return 0;
}