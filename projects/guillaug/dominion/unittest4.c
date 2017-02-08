#include "dominion.h"
#include "assert.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
	
	/* initialize the game variables */
 	struct gameState game;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
 	int turn;
 	
 	/* test name and purpose */
 	printf("-----\nStart of Unit Test 4: whoseTurn function\n-----\n");
 	printf("\nThis test will cover the whoseTurn function in Dominion.\n");
    printf("We will set up game state with 2 players and correctly assert that its player one's turn.\n");
    
    /* initialize the game with 2 players, 10 cards and the game state */
    initializeGame(2, k, 1, &game);
    
    /* get the supply count for the curse card*/
    turn = whoseTurn(&game);
    
    assert(turn == 0);
    printf("\nCorrect turn for the game state: %d\n", turn);
    
    printf("\n-----\nEnd of Unit Test 4: whoseTurn function\n-----\n");
    
    return 0;
}