#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(){
	printf("******begin unit test on whoseTurn()******\n");
	
	//initialize game
	struct gameState G;
	int result, randomVar = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	randomVar = rand() % 10;
	result = initializeGame(2, k, randomVar, &G);
	int turn = 0;
	int i;
	
	//testing for successful turns
	for (i = 0; i < 10; i++){
		G.whoseTurn = turn;
		result = whoseTurn(&G);
		asserttrue(result == turn);
		turn++;
	}
	printf("******end unit test on whoseTurn()******\n");
	return 0;
}