#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void asserttrue(int num1, int num2) {

	if (num1 != num2)
		printf("Test FAILED\n");
	else 
		printf("Test PASSED\n");

}


int main() {
	printf("\n--- TESTING Council Room ---\n");
	
	//set up variables 
	struct gameState game;
	int k[10] = {adventurer, smithy, council_room, feast, mine, gardens, remodel, village, great_hall, baron};
	
	
	
	//initialize 3 players
	initializeGame(2, k, 5, &game);

	//each player gets 1 card
	game.handCount[0] = 1;
	game.handCount[1] = 1;
	
	//Player 1 has 1 buy
	game.numBuys = 1;
	
	//Play the council_room card
	printf("test if council_room executes correctly\n");
	asserttrue(cardEffect(council_room, 0, 0, 0, &game, 0, NULL), 0);
	
	printf("test if council_room increases handCount of owner by 3 \n");
	asserttrue(game.handCount[0], 4);
	
	printf("test if council_room increases handCount for other players by 1 \n");
	asserttrue(game.handCount[1],2);

	printf("test if council_room increases buys by 1 \n");
	asserttrue(game.numBuys, 2);
	

	printf("\n--- END TESTING ---\n");	
	return 0;
}