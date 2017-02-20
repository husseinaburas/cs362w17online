#include "dominion.h"
#include "assert.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
	
	/* initialize the game variables */
 	struct gameState game;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
 	int curseSupply;
 	
 	/* test name and purpose */
 	printf("-----\nStart of Unit Test 3: supplyCount function\n-----\n");
 	printf("\nThis test will cover the supplyCount function in Dominion.\n");
    printf("We will set up game state with 2 players which will set the supply count accordingly.\n");
    
    /* initialize the game with 2 players, 10 cards and the game state */
    initializeGame(2, k, 1, &game);
    
    /* get the supply count for the curse card*/
    curseSupply = supplyCount(curse, &game);
    
    assert(curseSupply == 10);
    printf("\nCorrect Amount of curse cards in the supply: %d\n", curseSupply);
    
    printf("\n-----\nEnd of Unit Test 3: supplyCount function\n-----\n");
    
    return 0;
}