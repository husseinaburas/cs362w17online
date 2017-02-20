#include "dominion.h"
#include "assert.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
	
	/* initialize the game variables */
 	struct gameState game;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
 	
 	/* test name and purpose */
 	printf("-----\nStart of Unit Test 2: updateCoins function\n-----\n");
 	printf("\nThis test will cover the updateCoins function in Dominion.\n");
    printf("We will set up the players with various amounts of coins and test whether the the right amount of coins are correctly adjusted.\n");
    printf("The coins will then be printed to the screen.\n");
    
    /* initialize the game with 2 players, 10 cards and the game state */
    initializeGame(2, k, 1, &game);
    
    /* set player one's hand with 4 copper coins, 3 silver coins and 2 gold coins*/
    game.handCount[0] = 4;
    
    game.hand[0][0] = copper;
    game.hand[0][1] = copper;
    game.hand[0][2] = copper;
    game.hand[0][3] = copper;
    
    game.hand[0][4] = silver;
    game.hand[0][5] = silver;
    game.hand[0][6] = silver;
    
    game.hand[0][7] = gold;
    game.hand[0][8] = gold;
    
    game.coins = 0;
    
    updateCoins(0, &game, 1);
    
    assert(game.coins == 5);
    printf("\nCorrect Amount of game coins: %d\n", game.coins);
    
    printf("\n-----\nEnd of Unit Test 2: updateCoins function\n-----\n");
    
    return 0;
}