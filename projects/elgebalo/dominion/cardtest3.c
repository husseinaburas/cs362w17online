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

int main () {
	
	printf("\n--- TESTING Great_Hall---\n");
	
	//set up variables 
	struct gameState Game;
	int k[10] = {adventurer, smithy, council_room, feast, mine, gardens, remodel, village, great_hall, baron};
	

	//initialize 3 players
	initializeGame(2, k, 5, &Game);
	
	//Set current player handcount and numactions to 1
	Game.handCount[0] = 1;
	Game.numActions = 1;


	printf("test if great_hall executes correctly\n");
	asserttrue(playGreat_Hall(&Game, 0, 0), 0);

	printf("test if great_hall changes handCount by drawing card\n");
	asserttrue(Game.handCount[0], 1);
	
	printf("test if great_hall increases numActions for player by 1\n");
	asserttrue(Game.numActions, 2);

	printf("test if great_hall is discarded\n");
	asserttrue(Game.discard[0][0], great_hall);

	
	
	printf("\n--- END TESTING ---\n");		
	return 0;
	
}