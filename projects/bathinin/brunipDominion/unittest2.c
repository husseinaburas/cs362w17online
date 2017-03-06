/*Name: Nipun Bathini
  Assignment: 3
  
  unittest for updateCoins() function
  */ 

#include "dominion.h"
#include "dominion_helpers.h"
#include "stdlib.h"
#include "stdio.h"
#include "rngs.h" 
#include <string.h>


int testUpdateCoins(){
	printf("\n --Unit Test 2-- \n");
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int player = 0;
	int bonus = 0;
    int i, handCount;

    initializeGame(2, k, 1000, &G);
    G.coins = 0; //start at 0

	// TEST 1 zero
    for (i = 0; i < G.handCount[player]; i++){
        G.hand[player][i] = 1;
    }

    updateCoins(player, &G, bonus); //run updatecoins function
	//print that everything is 0
    printf("Testing: updateCoins()  Should equal 0, there are "); // should be equal to zero, print before if

    if(G.coins == 0){ //there should be zero coins
        printf("%d coins which is equal 0, test PASS\n", G.coins);
    }else if(G.coins != 0){//if not equal print an error message
        printf("%d coins do NOT equal 0,Test FAIL\n", G.coins);
    }
	// TEST 2 adding 5
    G.coins = 0; //reset zero

    for (i = 0; i < G.handCount[player]; i++){
        G.hand[player][i] = 4;
    }
    updateCoins(player, &G, bonus);
	printf("Testing: updateCoins() Should equal 5, there are ");

	if(G.coins == 5){ //make sure equal to 5 after adding the 5 cards
        printf("%d coins which is equal to 5, test PASS\n", G.coins);
    }else if(G.coins != 5){
        printf("%d coins which is NOT equal to 5, test PASS\n", G.coins);
    }
	// TEST 3 adding gold, silcer and copper, and the bonus
    G.coins = 0; //reset to 0 for next test
    bonus = 5; //for the next test we will add a bonus of 5
	
	for(i = 0; i< G.handCount[player]; i++){
		if(i < 2){
			G.hand[player][i] = 4;
		}else if(i < 4){
			G.hand[player][i] = 5;
		}else if (i == 4){
			G.hand[player][i] == 6;
		}
	}
	
    printf("Testing: updateCoins()Should equal 12, there are ");
    updateCoins(player, &G, bonus);
    if(G.coins == 12){
        printf("%d coins which is equal to 12. test PASS\n", G.coins);
    }else if(G.coins != 12){
        printf("%d coins which is not equal to 12. test FAIL\n", G.coins);
    }
	return 0;
}

int main(){
	if(testUpdateCoins() == 0){
		return 0;
	}else{
		printf("Error: testUpdateCoins");
		exit(1);
	}
}