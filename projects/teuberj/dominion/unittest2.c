/*
 * Unit Test #2: gainCard()
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
	printf("Unit Test 2 commencing - gainCard()\n");
	//Test Case 1: Card not in Supply
	retValue = gainCard(treasure_map,&testState, 0, 0);
	zAssert(retValue == -1,1);
	memcpy(&testState,&storeState,sizeof(struct gameState));
	//Test Case 2: Card in Supply with 0 count
	testState.supplyCount[k[0]] = 0;
	retValue = gainCard(k[0], &testState, 0, 0);
	zAssert(retValue == -1, 2);
	memcpy(&testState,&storeState,sizeof(struct gameState));
	//Test Set: Add card to hand
	retValue = gainCard(k[0], &testState, 2, 0);
	//Test Case 3: Supply of card should have deceremented by 1
	zAssert(retValue == 0 && testState.supplyCount[k[0]] == storeState.supplyCount[k[0]] - 1, 3);
	//Test Case 4: Card added to player hand
	zAssert(retValue == 0 && testState.handCount[0] == storeState.handCount[0] + 1,4);

	memcpy(&testState, &storeState,sizeof(struct gameState));	
	//Test Set: Add card to deck
	retValue = gainCard(k[0], &testState, 1, 0);
	//Test Case 5: Supply of card should have decremented by 1
	zAssert(retValue == 0 && testState.supplyCount[k[0]] == storeState.supplyCount[k[0]] - 1, 5);
	//Test Case 6: Card added to deck
	zAssert(retValue == 0 && testState.deckCount[0] == storeState.deckCount[0] + 1, 6);
	
	memcpy(&testState, &storeState, sizeof(struct gameState));
	//Test Set: Add card to discard
	retValue = gainCard(k[0], &testState, 0, 0);
	//Test Case 7: Supply of card should have decremented by 1
	zAssert(retValue == 0 && testState.supplyCount[k[0]] == storeState.supplyCount[k[0]] - 1, 7);
	//Test Case 8: Card added to discard
	zAssert(retValue == 0 && testState.discardCount[0] == storeState.discardCount[0] + 1, 8);
	
return 0;
}
