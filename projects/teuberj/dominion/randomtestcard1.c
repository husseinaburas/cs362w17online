/*
 * random card test #1: Council Room
 *
 * John Teuber; CS362W17; Assign 4; 2/19/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"
#include "dominion.h"
#include "zAssert.h"

int main(int argc, char* argv[]){
	
	if (argc != 2 || atoi(argv[1]) < 1){
		printf("Requires 1 positive integer to use as seed.\n");
		exit(0);
	}
	int randSeed = atoi(argv[1]);
	srand(randSeed);
	//create gamestates;
	struct gameState testState;
	struct gameState storeState;

	int k[10] = {adventurer, smithy, council_room, feast, village, great_hall, gardens, mine, minion, tribute};

	int retValue;

	printf("Beginning Council Room test suite.\n");

	int i;
	for(i=0;i<10000;i++){
		printf("Random Test Set: #%d\n",i);
		//initialize game for testing
		int numPlayers = rand()%3 + 2;
		int currentPlayer = rand() % numPlayers;
		initializeGame(numPlayers, k, (rand()%100)+1, &testState);	
		//copy to store state
		testState.hand[currentPlayer][0] = council_room;
		memcpy(&storeState,&testState,sizeof(struct gameState));
	
		//Test Scenario: Random # players  and random player plays Council Room
		retValue = playCouncilRoom(currentPlayer, &testState, 0);
		//Test Case #1: Player draws 4 cards
		zAssert(retValue == 0 && testState.handCount[currentPlayer] == storeState.handCount[currentPlayer] + 3,1);
		//Test Case #3: Number of Buys increases
		zAssert(retValue == 0 && testState.numBuys == storeState.numBuys + 1,2);
		//Test Case #4: Council Room is added to played Pile
		zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount + 1,3);
		//Test Case #5: Council Room added to top of playedd pile 
		zAssert(retValue == 0 && testState.playedCards[testState.playedCardCount-1] == council_room,4);
		//all other players draw a card
		int j;
		for(j=0;j<numPlayers;j++){
			if(j != currentPlayer){
				zAssert(retValue = 0 && testState.handCount[j] == storeState.handCount[j] + 1, 5+j);
			}
		}		
	}		
return 0;
}
