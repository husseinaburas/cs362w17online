/* -----------------------------------------------------------------------
 * Cardtest for Steward
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
               , remodel, smithy, village, steward, great_hall};
    struct gameState G;
    int maxHandCount = 5;
	int player = 0;
	
	int action_before, action_after, card_before, card_after, supply_after, supply_before;
	int buy_before, buy_after;
	int coin_before, coin_after;
	int playedCardCount_after, playedCardCount_before;
	
	///////////choice1/////////////
	printf("Cardtest6: Steward\n");
	printf("Starting the game...\n");
	int maingame = initializeGame(numPlayer, k, seed, &G);
	assert_check=myassert(maingame==0);
	
	printf("When choice1\n");
	
	card_before = numHandCards(&G);
	printf("Cards in hand before using Steward: %i\n", card_before);
	
	//use card choice1
	cardEffect(steward,1,0,0,&G,4,0);
	
	
	card_after = numHandCards(&G);
	printf("Cards in hand after using Steward: %i\n", card_after);
	
	//compare results
	
	assert_check=myassert((card_after-1) == card_before && ": failed\n");
	
	
	if(assert_check==-1){
		printf("Some of the test failed...\n");
		//return 0;
	}
	else
		printf("results match\n");	
	
	////////////choice2/////////

	printf("Starting the game...\n");
	maingame = initializeGame(numPlayer, k, seed, &G);
	assert_check=myassert(maingame==0);
	
	printf("When choice2\n");
	coin_before=G.coins;
	printf("Coin before using Steward: %i\n", coin_before);
	
	
	//use card choice2
	cardEffect(steward,2,0,0,&G,4,0);
	
	coin_after=G.coins;
	printf("Coin after using Steward: %i\n", coin_after);
	
	
	//compare results
	
	assert_check=myassert((coin_after-2) == coin_before && ": failed\n");
	
	
	if(assert_check==-1){
		printf("Some of the test failed...\n");
		//return 0;
	}
	else
		printf("results match\n");		
	
	///////////choice3////////////

	printf("Starting the game...\n");
	maingame = initializeGame(numPlayer, k, seed, &G);
	assert_check=myassert(maingame==0);
	
	printf("When choice3\n");
	
	card_before = numHandCards(&G);
	printf("Cards in hand before using Steward: %i\n", card_before);
	playedCardCount_before= G.playedCardCount;
	printf("Played Cards before using Steward: %i\n", playedCardCount_before);
	
	//use card choice1
	cardEffect(steward,3,0,0,&G,4,0);
	
	
	card_after = numHandCards(&G);
	printf("Cards in hand after using Steward: %i\n", card_after);
	playedCardCount_after= G.playedCardCount;
	printf("Played Cards after using Steward: %i\n", playedCardCount_after);
	
	//compare results
	
	assert_check=myassert((card_after+3) == card_before && ": failed\n");
	assert_check=myassert((playedCardCount_after) == playedCardCount_before && ": failed\n");
	
	
	if(assert_check==-1){
		printf("Some of the test failed...\n");
		//return 0;
	}
	else
		printf("results match\n");	

    printf("All tests done\n");

    return 0;
}