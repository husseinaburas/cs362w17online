/*
 * Random Card Test Adventurer
 *
 * John Teuber; CS362W17; Assign 4; 2/17/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"
#include "dominion.h"
#include "zAssert.h"
#include "refactor.h"

int main(int argc, char* argv[]){
	if(argc != 2 || atoi(argv[1]) < 0){
		printf("Requires positive integer to use as seed.\n");
		exit(0);
	}
	int randSeed = atoi(argv[1]);
	srand(randSeed);
	//create gamestates;
	struct gameState testState;
	struct gameState storeState;
	struct gameState originalState;

	int k[10] = {adventurer, smithy, council_room, feast, village, great_hall, gardens, mine, minion, tribute};

	int retValue = 0;
	
	printf("Beginning Adventurer test suite.\n");

	int i;
	for(i=0;i<10000;i++){
		printf("Random Test Set: #%d\n",i);
		//initialize game for testing
		int numPlayers = rand()%3 + 2;
		int currentPlayer = rand() % numPlayers;
	 
		initializeGame(numPlayers, k, (rand()%100)+1, &testState);	
		//copy to store state
		memcpy(&storeState,&testState,sizeof(struct gameState));
		memcpy(&originalState, &testState, sizeof(struct gameState));
		//Start Unit Tests
		
	
		//Scenario 1 - empty deck, discard has 3 coppers
		testState.discardCount[currentPlayer] = 3;
		testState.discard[currentPlayer][0] = copper;
		testState.discard[currentPlayer][1] = copper;
		testState.discard[currentPlayer][2] = copper;
		testState.deckCount[currentPlayer] = 0;
		testState.hand[currentPlayer][0] = adventurer;
		memcpy(&storeState,&testState,sizeof(struct gameState));

		playAdventurer(&testState,currentPlayer,0);

		//Unit Test 1 - Deck Count is 1
		zAssert(retValue == 0 && testState.deckCount[currentPlayer] == 1,1);
		//Unit Test 2 - Player hand has net increase of 1
		zAssert(retValue == 0 && testState.handCount[currentPlayer] == storeState.handCount[currentPlayer]+1,2);
		//Unit Test 3 - Player hand has 1 copper in first and 1 in last spot
		zAssert(retValue == 0 && testState.hand[currentPlayer][0] == copper && testState.hand[currentPlayer][testState.handCount[currentPlayer]-1],3);
		//Unit Test 4 - Player Discard Pile has no additional cards
		zAssert(retValue == 0 && testState.discardCount[currentPlayer] == 0,4);
		//Unit Test 5 - Adventurer removed from hand
		zAssert(retValue == 0 && testState.hand[currentPlayer][0] != adventurer,5);
		//Unit Test 6 - Played Pile has adventurer added
		zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount + 1,6);
		//revert to original state for Scenario 2
		memcpy(&storeState,&originalState,sizeof(struct gameState));
		memcpy(&testState,&originalState,sizeof(struct gameState));
	
		//Scenario 2 - Deck = gold, silver, copper
		testState.deck[currentPlayer][0] = copper;
		testState.deck[currentPlayer][1] = silver;
		testState.deck[currentPlayer][2] = gold;
		testState.deckCount[currentPlayer] = 3;	 
		testState.hand[currentPlayer][0] = adventurer;
		memcpy(&storeState,&testState,sizeof(struct gameState));

		playAdventurer(&testState,currentPlayer,0);
	
		//Unit Test 7 - Deck Count is 1
		zAssert(retValue == 0 && testState.deckCount[currentPlayer] == 1,7);
		//Unit Test 8 - Played Hand size increased by net of 1
		zAssert(retValue == 0 && testState.handCount[currentPlayer] == storeState.handCount[currentPlayer]+1,8);
		//Unit Test 9 - Player Hand has gold and Silver
		zAssert(retValue == 0 && (testState.hand[currentPlayer][testState.handCount[currentPlayer]-1] == gold || testState.hand[currentPlayer][testState.handCount[currentPlayer]-1] == silver) && (testState.hand[currentPlayer][0] == gold || testState.hand[currentPlayer][0] == silver),9);
		//Unit Test 10 - Player Discard Pile has no additional cards
		zAssert(retValue == 0 && testState.discardCount[currentPlayer] == storeState.discardCount[currentPlayer],10);
		//Unit Test 11 - Adventurer removed from hand
		zAssert(retValue == 0 && testState.hand[currentPlayer][0] != adventurer,11);
		//Unit Test 12 - Played card pile has adventurer added
		zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount + 1,12);
	
		//copy original game state for scenario 3
		memcpy(&testState, &originalState, sizeof(struct gameState));
		memcpy(&storeState, &originalState, sizeof(struct gameState));		 
		//Scenario 3 - Deck = copper, copper, smithy 
		testState.deck[currentPlayer][0] = copper;
		testState.deck[currentPlayer][1] = copper;
		testState.deck[currentPlayer][2] = smithy;
		testState.deckCount[currentPlayer] = 3;
		testState.hand[currentPlayer][0] = adventurer;
		memcpy(&storeState, &testState, sizeof(struct gameState));
	
		playAdventurer(&testState,currentPlayer,0);
	
		//Unit Test 13 - Deck Count is 0
		zAssert(retValue == 0 && testState.deckCount[currentPlayer] == 0,13);
		//Unit Test 14 - Player hand count has net increase of 1
		zAssert(retValue == 0 && testState.handCount[currentPlayer] == storeState.handCount[currentPlayer]+1,14);
		//Unit Test 15 - Player Hand has Copper and Copper
		zAssert(retValue == 0 && testState.hand[currentPlayer][testState.handCount[currentPlayer]-1] == copper && testState.hand[currentPlayer][testState.handCount[currentPlayer]-2] == copper,15);
		//Unit Test 16 - Player discard pile has one additional card
		zAssert(retValue == 0 && testState.discardCount[currentPlayer] == storeState.discardCount[currentPlayer] + 1,16);
		//Unit Test 17 - Discard top card is smithy
		zAssert(retValue == 0 && testState.discard[currentPlayer][testState.discardCount[currentPlayer]-1] == smithy,17);
		//Unit Test 18 - Adventurer removed from hand
		zAssert(retValue == 0 && testState.hand[currentPlayer][0] != adventurer,18);
		//Unit Test 19 - played pile has adventurer added
		zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount +1,19);


		//return to original for scenario 4
		memcpy(&testState,&originalState,sizeof(struct gameState));
		memcpy(&storeState,&originalState,sizeof(struct gameState));	

		//Scenario 4- Deck = copper, copper, copper, village, village
		testState.deck[currentPlayer][0] = copper;
		testState.deck[currentPlayer][1] = copper;
		testState.deck[currentPlayer][2] = copper;
		testState.deck[currentPlayer][3] = village;
		testState.deck[currentPlayer][4] = village;
		testState.deckCount[currentPlayer] = 5;
		testState.hand[currentPlayer][0] = adventurer;
		memcpy(&storeState,&testState,sizeof(struct gameState));
	
		playAdventurer(&testState,currentPlayer,0);

		//Unit Test 20 - Deck Count is 1
		zAssert(retValue == 0 && testState.deckCount[currentPlayer] == 1,20);
		//Unit test 21 - Player Hand has net increase of 1
		zAssert(retValue == 0 && testState.handCount[currentPlayer] == storeState.handCount[currentPlayer]+1,21);
		//Unit Test 22 - Player hand has copper + copper
		zAssert(retValue == 0 && testState.hand[currentPlayer][testState.handCount[currentPlayer]-1] == copper && testState.hand[currentPlayer][testState.handCount[currentPlayer]-2] == copper,22);
		//Unit Test 23 - Player Discard pile has 2 additional cards
		zAssert(retValue == 0 && testState.discardCount[currentPlayer] == storeState.discardCount[currentPlayer]+2,23);
		//Unit Test 24 - Discarded cards are both villages
		zAssert(retValue == 0 && testState.discard[currentPlayer][testState.discardCount[currentPlayer]-1] == village && testState.discard[currentPlayer][testState.discardCount[currentPlayer]-2] == village,24);
		//Unit Test 25 - Adventurer removed from hand
		zAssert(retValue == 0 && testState.hand[currentPlayer][0] != adventurer,25);
		//Unit Test 26 - Played pile has adventurer added
		zAssert(retValue == 0 && testState.playedCardCount == storeState.playedCardCount + 1,26);
		 		 
	}
	 	
return 0;
}
