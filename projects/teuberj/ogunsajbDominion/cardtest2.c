/*
 * Card Test #2: Council Room  card
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
	//copy to store state
	testState.hand[0][0] = council_room;
	memcpy(&storeState,&testState,sizeof(struct gameState));

	//Start Unit Tests
	printf("Unit Test #6 commencing - Council Room card\n");

	//Test Scenario: 2 Players and Player 1 plays Council Room
	playCouncil_room(&testState,0, 0);
	//Test Case #1: Player draws 4 cards
	zAssert(retValue == 0 && testState.handCount[0] == storeState.handCount[0] + 3,1);
	//Test Case #2: Other player draws a card
	zAssert(retValue == 0 && testState.handCount[1] == storeState.handCount[1] + 1,2);
	//Test Case #3: Number of Buys increases
	zAssert(retValue == 0 && testState.numBuys == storeState.numBuys + 1,3);
	//Test Case #4: Council Room is added to played Pile
	zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount + 1,4);
	//Test Case #5: Council Room added to top of playedd pile 
	zAssert(retValue == 0 && testState.playedCards[testState.playedCardCount-1] == council_room,5);
	
	//Test Scenario: 5 Players and Player 2 plays council room
	initializeGame(5, k, 17, &testState);
	testState.hand[1][0] = council_room;
	memcpy(&storeState, &testState, sizeof(struct gameState));
	
	playCouncil_room(&testState,1, 0);
	//Test Case #6: Player 1 draws 4 cards
	zAssert(retValue == 0 && testState.handCount[1] == storeState.handCount[1] + 3, 6);
	//Test Case #7: Player 0 draws card
	zAssert(retValue == 0 && testState.handCount[0] == storeState.handCount[0] + 1, 7);
	//Test Case #8: Player 2 draws card
	zAssert(retValue == 0 && testState.handCount[2] == storeState.handCount[2] + 1, 8); 
	//Test Case #9: Player 3 draws card
	zAssert(retValue == 0 && testState.handCount[3] == storeState.handCount[3] + 1, 9);
	//Test Case #10: Player 4 draws card
	zAssert(retValue == 0 && testState.handCount[4] == storeState.handCount[4] + 1, 10);
	//Test Case #11: Number of Buys increases
	zAssert(retValue == 0 && testState.numBuys == storeState.numBuys + 1,11);
	//Test Case #12: Council Room is added to played Pile
	zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount + 1,12);
	//Test Case #13: Council Room is added to top of played pile
	zAssert(retValue == 0 && testState.playedCards[testState.playedCardCount - 1] == council_room, 13); 
		
return 0;
}
