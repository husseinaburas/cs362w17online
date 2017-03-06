/*
- Andrew Bagwell
- CS362 Assignment 3 
- bagwella@oregonstate.edu
- Test of dominion's whoseTurn function
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

//Testing whoseTurn

int main() {

	struct gameState GS;
	int c[10] = {adventurer, ambassador, gardens, great_hall, mine, minion, smithy, salvager, steward, village};
	
	//Standard initialization across all my tests, 
  	initializeGame(2, c, 5, &GS);

  	printf("*************************************\n");
  	printf("unitTest3:\n");
  	printf("TESTING -- testing whoseTurn() -- BEGIN\n");
	
	//Testing  whoseTurn function initializes
	printf("TESTING - whoseTurn() executes successfully\n");
	assertTrue(endTurn(&GS),0);

	printf("TESTING - whoseTurn() changes \n");
  	for (int i = 0; i < 27 ; i++) {
  		printf("TESTING - %d whoseTurn after manual change to gameState property...\n", i);
 		GS.whoseTurn = i;
    	assertTrue(whoseTurn(&GS), i);
	}

  	printf("TESTING--getCost() -- COMPLETE\n\n");

	return 0;
}