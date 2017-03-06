/*
 * Random Card Test #2: Smithy Card
 *
 * John Teuber; CS362W17; Assign 4; 2/19/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"
#include "dominion.h"
#include "zAssert.h"
#include "refactor.h"

int main(int argc, char* argv[]){
	if(argc != 2 || atoi(argv[1]) < 1){
		printf("Requires a positive integer to use as seed.\n");
		exit(0);
	}
	int randSeed = atoi(argv[1]);
	srand(randSeed);
	//create gamestates;
	struct gameState testState;
	struct gameState storeState;

	int k[10] = {adventurer, smithy, council_room, feast, village, great_hall, gardens, mine, minion, tribute};

	int retValue = 0;
	
	printf("Beginning Smithy test suite.\n");

	int i;
	for(i=0;i<10000;i++){
		printf("Random Test Set: #%d\n",i);
		//initialize game for testing
		int numPlayers = rand()%3 + 2;
		int currentPlayer = rand() % numPlayers;
		initializeGame(numPlayers, k, (rand()%100)+1, &testState);	
		testState.hand[currentPlayer][0] = smithy;
		if(testState.handCount[currentPlayer] == 0){
			testState.handCount[currentPlayer]++;
		}
		testState.hand[currentPlayer][testState.handCount[currentPlayer]] = smithy;
		testState.handCount[currentPlayer]++;
		//copy to store state
		memcpy(&storeState,&testState,sizeof(struct gameState));
	
		//Start Unit Tests
		//Test Scenario - currentPlayer plays smithy from handpos first
		playSmithy(&testState, currentPlayer, 0);
		//Test Case #1 - Player draws 3 cards
		zAssert(retValue == 0 && testState.handCount[currentPlayer] == storeState.handCount[currentPlayer] + 2, 1);
		//Test Case #2 - Former last card is first card in hand
		//printf("%d, %d\n", testState.hand[currentPlayer][0],smithy);
		zAssert(retValue == 0 && testState.hand[currentPlayer][0] != smithy,2);
		//Test Case #3 - Card added to played card pile
		zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount + 1, 3); 
		//Test Case #4 - Smithy is on top of played card pile
		//printf("%d, %d\n", testState.playedCards[testState.playedCardCount-1],smithy);	
		zAssert(retValue == 0 && testState.playedCards[testState.playedCardCount-1] == smithy, 4);	
	
		memcpy(&testState, &storeState, sizeof(struct gameState));
		//Test Scenario - Player plays smithy from handpos last
		playSmithy(&testState, currentPlayer, testState.handCount[currentPlayer] - 1);
		//Test Case #5 - Played draws 3 cards
		zAssert(retValue == 0 && testState.handCount[currentPlayer] == storeState.handCount[currentPlayer] + 2, 5);
		//Test Case #6 - Current top card minus drawn is dormer 2nd to last card
		zAssert(retValue == 0 && testState.hand[currentPlayer][storeState.handCount[currentPlayer]-2] == storeState.hand[currentPlayer][storeState.handCount[currentPlayer]-2],6);
		//Test Case #7 - Card added to played card pile
		zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount + 1, 7); 
		//Test Case #8 - Smithy is on top of played card pile
		zAssert(retValue == 0 && testState.playedCards[testState.playedCardCount-1] == smithy, 8); 	
	}		
return 0;
}
