/*
 * Unit Test #4: drawCard()
 *
 * John Teuber; CS362W17; Assign 3; 2/4/2017
 */

#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "zAssert.h"

int main(){
	//create gamestates;
	struct gameState testState;
	struct gameState storeState;

	int k[10] = {adventurer, smithy, council_room, feast, village, great_hall, gardens, mine, minion, tribute};

	int retValue;

	//initialize game for testing
	initializeGame(2, k, 17, &testState);	
	//copy to store state
	memcpy(&storeState,&testState,sizeof(struct gameState));

	//Start Unit Tests
	printf("Unit Test 4 commencing - drawCard()\n");
	
	//Test Case 1: Empty Hand and Draw Card = 1 card in hand
	testState.handCount[0] = 0;
	retValue = drawCard(0,&testState);
	zAssert(retValue == 0 && testState.handCount[0] == 1,1);
	
	//Test Case 2: Ensure empty discardCount after draw
	zAssert(retValue == 0 && testState.discardCount[0] == 0,2);
	memcpy(&testState,&storeState,sizeof(struct gameState));
	
	//Test Case 3: Arbitrary # in hand and Draw Card = +1
	retValue = drawCard(0,&testState);
	zAssert(retValue == 0 && storeState.handCount[0]+1 == testState.handCount[0],3);
	//Test Case 4: Ensure empty discardCount after draw:
	zAssert(retValue == 0 && testState.discardCount[0] == 0, 4);
	
return 0;
}
