/*
 * Unit Test #3: isGamaeOver()
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
	printf("Unit Test 3 commencing - isGameOver()\n");
	
	//Test Case 1: Province supply is depleted and Game ends
	testState.supplyCount[province] = 0;
	retValue = isGameOver(&testState);
	zAssert(retValue == 1 && testState.supplyCount[province] ==  0,1); 
	memcpy(&testState, &storeState, sizeof(struct gameState));
	//Test Case 2: Province supply is not depleted and Game continues
	testState.supplyCount[province]++;
	retValue = isGameOver(&testState);
	zAssert(retValue == 0  && testState.supplyCount[province] > 0, 2); 
	memcpy(&testState, &storeState, sizeof(struct gameState));
	//Test Case 3: No supply piles at 0
	int i;
	for(i = 0; i < 25; i++){
		testState.supplyCount[i] = 1;
	}
	retValue = isGameOver(&testState);
	zAssert(retValue == 0,3);  
	memcpy(&testState, &storeState, sizeof(struct gameState));
	//Test Case 4: All supply piles are 0
	for(i = 0; i < 25; i++){
		testState.supplyCount[i] = 0;
	}
	retValue = isGameOver(&testState);
	zAssert(retValue == 1,4);
	memcpy(&testState, &storeState, sizeof(struct gameState));
	//Test Case 5: 3 supply piles at 0
	for(i = 0; i < 25; i++){
		testState.supplyCount[i] = 1;
	}
	testState.supplyCount[0] = 0;
	testState.supplyCount[1] = 0;
	testState.supplyCount[2] = 0;	
	retValue = isGameOver(&testState);
	zAssert(retValue = 1,5);
	
return 0;
}
