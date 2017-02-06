/*
- Andrew Bagwell
- CS362 Assignment 3 
- bagwella@oregonGS.edu
- Test of dominion's great_hall card via the cardEffect function 
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

//custom assert function

void assertTrue(int val1, int val2) {

	if (val1 != val2)
		printf("Test Case - FAILED\n");
	else 
		printf("Test Case - PASSED\n");

}

//Testing great_hall 

int main () {
	
	//set up variables for testing
	struct gameState GS;
	int c[10] = {adventurer, ambassador, gardens, great_hall, mine, minion, smithy, salvager, steward, village};
	
	printf("*************************************\n");
	printf("cardtest4:\n");
  	printf("TESTING -- great_hall card -- BEGIN\n");
	
	//Standard initialization across all my tests...except you need 3 players here for testing
	initializeGame(2, c, 5, &GS);
	//Set the current player's handcount to 1 and their numActions to 1
	GS.handCount[0] = 1;
	GS.numActions = 1;

	printf("Calling the great_hall card..\n");
	printf("TESTING - great_hall executes successfully\n");
	assertTrue(playGreatHall(&GS, 0, 0), 0);

	printf("TESTING - great_hall changes handCount -draw a card and discard great_hall\n");
	assertTrue(GS.handCount[0], 1);

	printf("TESTING - great_hall increases numActions for player +1\n");
	assertTrue(GS.numActions, 2);
	
	printf("TESTING--great_hall card -- COMPLETE\n\n");
	
	return 0;
	
}