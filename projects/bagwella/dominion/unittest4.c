/*
- Andrew Bagwell
- CS362 Assignment 3 
- bagwella@oregonstate.edu
- Test of dominion's isGameOver function
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

//Testing isGameOver function 

int main(){

	struct gameState GS;
	int c[10] = {adventurer, ambassador, gardens, great_hall, mine, minion, smithy, salvager, steward, village};
	
	//Standard initialization across all my tests...
  	initializeGame(2, c, 5, &GS);

  	printf("*************************************\n");
	printf("unittest4:\n");
  	printf("TESTING -- isGameOver() function -- BEGIN\n");
	
	//Make sure game is not over
	printf("TESTING - isGameOver() returns 0 at start of newGame\n");
	assertTrue(isGameOver(&GS), 0);
	

	//no province cards ends the game
	printf("TESTING - isGameOver() returns 1 at after setting count of province cards to 0\n");
	GS.supplyCount[province] = 0;
	assertTrue(isGameOver(&GS), 1);

	//Now testing all possible permutations of the 3 supplyCount's being 0
	printf("TESTING - isGameOver() returns 1 if supplyCount is 0\n");
	//reset province cards to full
	GS.supplyCount[province] = 8;
	
	for(int i = 0; i < 8; i++) {
		for(int j =i+1; j < 9; j++) {
			for(int k =j+1; k < 10; k++) {

				GS.supplyCount[i] = 0;
				GS.supplyCount[j] = 0;
				GS.supplyCount[k] = 0;

				printf("Testing - isGameOver() returns 1 if 3 Kingdom cards are 0\n"); //prints too much
				assertTrue(isGameOver(&GS), 1);

				//reset card count
				GS.supplyCount[i] = 10;
				GS.supplyCount[j] = 10;
				GS.supplyCount[k] = 10;
				
			}
		}
	}
	printf("TESTING -- isGameOver() function -- COMPLETE\n\n");
	
	return 0;
}