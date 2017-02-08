#include "dominion.h"
#include "assert.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
	
	/* initialize the game variables */
 	struct gameState game;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
 	int choice1 = 0, choice2 = 0, choice3 = 0;
 	
 	/* test name and purpose */
 	printf("-----\nStart of Card Test 1: adventurer card\n-----\n");
 	printf("\nThis test will cover the adventurer card in Dominion.\n");
    printf("We will pass the adventurer card to the cardEffect function and assert whether 0 is returned.\n");
    
    /* initialize the game with 2 players, 10 cards and the game state */
    initializeGame(2, k, 4, &game);

    assert(cardEffect(adventurer, choice1, choice2, choice3, &game, 0, NULL) == 0);
    
    printf("\n-----\nEnd of Card Test 1: adventurer card\n-----\n");
    
    return 0;
}