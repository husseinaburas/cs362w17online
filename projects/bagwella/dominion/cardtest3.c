/*
- Andrew Bagwell
- CS362 Assignment 3 
- bagwella@oregonGS.edu
- Test of dominion's council_room card via the cardEffect function 
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "assert.h"

//custom assert function

void assertTrue(int val1, int val2) {

	if (val1 != val2)
		printf("Test Case - FAILED\n");
	else 
		printf("Test Case - PASSED\n");

}

//Testing council room card

int main() {
	
	//set up variables for testing
	struct gameState GS;
	int c[10] = {adventurer, ambassador, gardens, great_hall, mine, minion, smithy, salvager, steward, village};
	
	printf("*************************************\n");
	printf("cardtest3:\n");
  	printf("TESTING -- council_room card -- BEGIN\n");
	

	//Standard initialization across all my tests...except you need 3 players here for testing
	initializeGame(3, c, 5, &GS);

	//give each player a single card...
	GS.handCount[0] = 1;
	GS.handCount[1] = 1;
	GS.handCount[2] = 1;
	
	GS.numBuys = 1;
	//Player 1 has 1 buy
	

	//Play the council_room card
	printf("TESTING - council_room executes successfully\n");
	assertTrue(cardEffect(council_room, 0, 0, 0, &GS, 0, NULL), 0);
	
	printf("TESTING - council_room's increase of handCount of owner +3 \n");
	assertTrue(GS.handCount[0], 4);

	printf("TESTING - council_room's increase of buys +1 \n");
	assertTrue(GS.numBuys, 2);
	
	printf("TESTING - council_room's increase of handCount for other players +1 \n");
	assertTrue(GS.handCount[1],2);
	assertTrue(GS.handCount[2],2);

	printf("TESTING--council_room card -- COMPLETE\n\n");
	
	return 0;
}