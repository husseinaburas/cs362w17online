/*
  unit test for updateCoins() 
  */ 



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
	int bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	struct gameState G;
    int i;

    initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing Unit: updateCoins ----------------\n");

	// ----------- TEST 1: Testing if updateCoins updates to 5 --------------
	printf("TEST 1: Testing if G.coins == 5\n");
    G.coins = 0;
    for (i = 0; i < G.handCount[thisPlayer]; i++){
        G.hand[thisPlayer][i] = 4;
    }
    updateCoins(thisPlayer, &G, bonus);
	printf("coins = %d, expected = 5\n", G.coins);
	assert(G.coins == 5);
	
	// ----------- TEST 2: Testing if updateCoins updates to 0 --------------
    printf("TEST 2: Testing if G.coins == 0\n"); 
	G.coins = 0; 
    for (i = 0; i < G.handCount[thisPlayer]; i++){
        G.hand[thisPlayer][i] = 1;
    }
    updateCoins(thisPlayer, &G, bonus); 
	printf("coins = %d, expected = 0\n", G.coins);
    assert(G.coins == 0);
	
	// ----------- TEST 3: Testing the bonus variable --------------
	printf("TEST 3: Testing the bonus variable\n");
	//add a bonus of 5	
    bonus = 5;
    G.coins = 0;
	
	for(i = 0; i< G.handCount[thisPlayer]; i++){
		if(i < 2){
			G.hand[thisPlayer][i] = 4;
		}else if(i < 4){
			G.hand[thisPlayer][i] = 5;
		}else if (i == 4){
			G.hand[thisPlayer][i] = 6;
		}
	}
    updateCoins(thisPlayer, &G, bonus);
	printf("coins = %d, expected = 14\n", G.coins);
    assert(G.coins == 14);
	
	printf("\n >>>>> SUCCESS: Testing complete for unittest2 <<<<<\n\n");
	return 0;
}
