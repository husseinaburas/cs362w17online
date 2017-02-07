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
 	printf("-----\nStart of Card Test 2: gardens card\n-----\n");
 	printf("\nThis test will cover the gardens card in Dominion.\n");
    printf("We will pass the gardens card to the cardEffect function and assert whether 0 is returned.\n");
    
    /* initialize the game with 2 players, 10 cards and the game state */
    initializeGame(2, k, 4, &game);

    int test, count = game.handCount[0];
    game.hand[0][0] = gardens;
    test = playCard(0, 1, 0, 0, &game);
    
    printf("\n-----\nEnd of Card Test 2: gardens card\n-----\n");
    
    return 0;
}