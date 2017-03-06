/* 
 * Unit Test #1: discardCard()
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
	printf("Unit Test 1 commencing - discardCard()\n");

	//Test Set: Discard First Card in Hand and not trashed
	retValue = discardCard(0, 0, &testState, 0);
	//	Test 1: First Card equals previous last card 
	zAssert(retValue == 0 && testState.hand[0][0] == storeState.hand[0][storeState.handCount[0]-2],1);
	//	Test 2: HandSize is decremented by 1
	zAssert(retValue == 0 && testState.handCount[0] == storeState.handCount[0]-1,2);	
	//	Test 3: Discarded card added to play pile
	zAssert(retValue == 0 && testState.playedCards[testState.playedCardCount- 1] == storeState.hand[0][0],3);	
	//	Test 4: Played card count increments
	zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount + 1, 4);	

	//restore testState to storedState	
	memcpy(&testState,&storeState,sizeof(struct gameState));
	
	//Test Set: Discard Last Card in Hand and not trashed
	retValue = discardCard(testState.handCount[0]-1, 0, &testState, 0);
	//	Test 5: LastCard equals previous second to last card
	zAssert(retValue == 0 && testState.hand[0][testState.handCount[0]-1] == 
storeState.hand[0][storeState.handCount[0]-2],5);
	//	Test 6: Handsize is decremented by 1
	zAssert(retValue == 0 && testState.handCount[0] == storeState.handCount[0]-1,6);
	//	Test 7: Discarded card added to play pile
	zAssert(retValue == 0 && testState.playedCards[testState.playedCardCount- 1] == storeState.hand[0][storeState.handCount[0]-1],7);	
	//	Test 8: Played card count increments
	zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount + 1, 8);
	
	memcpy(&testState,&storeState,sizeof(struct gameState));

	//Test Set: Discard Last Card in Hand and trash the card
	retValue = discardCard(testState.handCount[0]-1, 0, &testState, 1); 
	//	Test 9: LsatCard equals previous seconid to last card
	zAssert(retValue == 0 && testState.hand[0][testState.handCount[0]-1] == storeState.hand[0][storeState.handCount[0]-2],9);	
	//	Test 10: handsize is decremented by 1
	zAssert(retValue == 0 && testState.handCount[0] == storeState.handCount[0]-1,10);	
	//	Test 11: Discarded card not added to play pile
	zAssert(retValue == 0 && testState.playedCards[testState.playedCardCount - 1] != storeState.hand[0][storeState.handCount[0]-1],11);	
	//	Test 12: Played card count remains same 
	zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount, 12); 	
return 0;
}
   
