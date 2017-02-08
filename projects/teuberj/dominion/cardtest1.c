/*
 * Card Test #1: Village
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
	printf("Unit Test #5 commencing	- Village card\n");

	testState.hand[0][0] = village;
	retValue = playVillage(0, &testState, 0);	
	//Test Case #1: Verify number of actions increased by 2
	zAssert(retValue == 0 && testState.numActions == storeState.numActions + 2, 1);  
	//Test Case #2: Verify card discarded from hand
	zAssert(retValue == 0 && testState.handCount[0] == storeState.handCount[0], 2);
	//Test Case #3: verify card added to discard pile
	zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount + 1,3); 
	//Test Case #4: Verify top card of discard is village
	zAssert(retValue == 0 && testState.playedCards[testState.playedCardCount - 1] == village,4);
	//Test Case #5: Verify hand card replaced by former last in hand 
	zAssert(retValue == 0 && testState.hand[0][0] == storeState.hand[0][storeState.handCount[0]-1],5);

return 0;
}
