#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(){
	printf("------  whoseTurn unit test ------\n");
	
	//initialize game
	int r, turn;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	struct gameState G;
	r = initializeGame(2, k, 1, &G);

	//Assign turn to player 1 and expect whose turn to return 0
	printf("Player 1 turn\n");
	G.whoseTurn = 0;
	turn = whoseTurn(&G);
	asserttrue(turn == 0);

	//Assign turn to player 2 and expect whose turn to return 1
	printf("Player 2 turn\n");
	G.whoseTurn = 1;
	turn = whoseTurn(&G);
	asserttrue(turn == 1);

	printf("--------------- end --------------\n");
	return 0;
}