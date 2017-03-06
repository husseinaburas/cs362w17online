/* -----------------------------------------------------------------------
 * Cardtest for Council room
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

int myassert(int i){
	if (i==0){
		printf("Test failed\n");
		return -1;
	}
	return 1;
}

int main() {
	int assert_check=0;
    int i,j;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount, deckCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
	int player = 0;
	
	int action_before, action_after, card_before, card_after, supply_after, supply_before;
	int buy_before, buy_after;
	
	printf("Cardtest5: Council Room\n");
	printf("Starting the game...\n");
	int maingame = initializeGame(numPlayer, k, seed, &G);
	assert_check=myassert(maingame==0);
	
	buy_before=G.numBuys;
	printf("Buy before using council room: %i\n", buy_before);
	card_before = numHandCards(&G);
	printf("Cards in hand before using council room: %i\n", card_before);
	
	//use card
	cardEffect(council_room,0,0,0,&G,4,0);
	
	buy_after=G.numBuys;
	printf("Buy after using council room: %i\n", buy_after);
	card_after = numHandCards(&G);
	printf("Cards in hand after using council room: %i\n", card_after);
	
	//compare results
	assert_check=myassert(buy_before+1 == buy_after && ": failed\n");
	assert_check=myassert((card_after-3) == card_before && ": failed\n");
	
	
	if(assert_check==-1){
		printf("Some of the test failed...\n");
		return 0;
	}
	
	printf("results match\n");	

    printf("All tests passed!\n");

    return 0;
}