/*
 * Card Test #3: Smithy Card 
 *
 * John Teuber; CS362W17; Assign 3; 2/4/2017
 */

#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "zAssert.h"
#include "refactor.h"

int main(){
	//create gamestates;
	struct gameState testState;
	struct gameState storeState;

	int k[10] = {adventurer, smithy, council_room, feast, village, great_hall, gardens, mine, minion, tribute};

	int retValue = 0;

	//initialize game for testing
	initializeGame(2, k, 17, &testState);	
	testState.hand[0][0] = smithy;
	testState.hand[1][testState.handCount[1] - 1] = smithy;
	//copy to store state
	memcpy(&storeState,&testState,sizeof(struct gameState));

	//Start Unit Tests
	printf("Unit Test #7 commencing - Smithy card\n");

	//Test Scenario - Player 1 plays smithy from handpos first
	playSmithy(&testState,0, 0);
	//Test Case #1 - Player draws 3 cards
	zAssert(retValue == 0 && testState.handCount[0] == storeState.handCount[0] + 2, 1);
	//Test Case #2 - Former last card is first card in hand
	zAssert(retValue == 0 && testState.hand[0][0] == storeState.hand[0][storeState.handCount[0]-1],2);
	//Test Case #3 - Card added to played card pile
	zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount + 1, 3); 
	//Test Case #4 - Smithy is on top of played card pile
	zAssert(retValue == 0 && testState.playedCards[testState.playedCardCount-1] == smithy, 4);	

	memcpy(&testState, &storeState, sizeof(struct gameState));
	//Test Scenario - Player 2 plays smithy from handpos last
	playSmithy(&testState,1, testState.handCount[1] - 1);
	//Test Case #5 - Played draws 3 cards
	zAssert(retValue == 0 && testState.handCount[1] == storeState.handCount[1] + 2, 5);
	//Test Case #6 - Current top card minus drawn is dormer 2nd to last card
	zAssert(retValue == 0 && testState.hand[1][storeState.handCount[1]-2] == storeState.hand[1][storeState.handCount[1]-2],6);
	//Test Case #7 - Card added to played card pile
	zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount + 1, 7); 
	//Test Case #8 - Smithy is on top of played card pile
	zAssert(retValue == 0 && testState.playedCards[testState.playedCardCount-1] == smithy, 8); 	
	
return 0;
}
