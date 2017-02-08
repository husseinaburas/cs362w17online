//test for council room card

#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "custom_assert.c"

#define SHOULD_ASSERT_FAIL 0

//returns 1 if card is in hand, 0 if not
int isInHand(int playerNum, struct gameState *testGameState, int card){
	int i;
	for(i = 0; i < testGameState->handCount[playerNum]; ++i){
		if(testGameState->hand[playerNum][i] == card){
			return 1;
		}
	}

	return 0;
}

void testCouncilRoomDrawsCards(int playerNum){
	char *testName = "Test council room draws correct number of cards";

	struct gameState testGameState;
	//initialize for discardCard
	testGameState.playedCardCount = 0;
	//initialize buys
	testGameState.numBuys = 0;
	//initialize players
	testGameState.numPlayers = 3;
	//initialize player hand and deck
	testGameState.handCount[playerNum] = 1;
	testGameState.hand[playerNum][0] = council_room;

	testGameState.deckCount[playerNum] = 4;
	testGameState.deck[playerNum][0] = silver;
	testGameState.deck[playerNum][1] = province;
	testGameState.deck[playerNum][2] = sea_hag;
	testGameState.deck[playerNum][3] = gold;

	int player2;
	int player3;
	switch(playerNum){
		case 0:
			player2 = 1;
			player3 = 2;
			break;
		case 1:
			player2 = 0;
			player3 = 2;
			break;
		default:
			player2 = 0;
			player3 = 1;
			break;
	}

	testGameState.handCount[player2] = 0;
	testGameState.deckCount[player2] = 1;
	testGameState.deck[player2][0] = copper;

	testGameState.handCount[player3] = 0;
	testGameState.deckCount[player3] = 2;
	testGameState.deck[player3][0] = province;
	testGameState.deck[player3][1] = smithy;

	playCouncil_Room(playerNum, &testGameState, 0);

	//test player that used card has correct number of cards
	custom_assert(testGameState.handCount[playerNum] == 4, testName, __LINE__, SHOULD_ASSERT_FAIL);
	//test council_room discarded
	custom_assert(!isInHand(playerNum, &testGameState, council_room), testName, __LINE__, SHOULD_ASSERT_FAIL);
	//test player got correct cards
	custom_assert(isInHand(playerNum, &testGameState, silver), testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(isInHand(playerNum, &testGameState, province), testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(isInHand(playerNum, &testGameState, sea_hag), testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(isInHand(playerNum, &testGameState, gold), testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test player2 got 1 card
	custom_assert(testGameState.handCount[player2] == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(isInHand(player2, &testGameState, copper), testName, __LINE__, SHOULD_ASSERT_FAIL);
	printf("%d\n", testGameState.hand[player2][0]);

	//test player3 got 1 card
	custom_assert(testGameState.handCount[player3] == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(testGameState.hand[player3][0] == smithy, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test 1 buy was added
	custom_assert(testGameState.numBuys == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);
}


int main(int argc, char const *argv[]){
	int i;
	for (i = 0; i < MAX_PLAYERS - 1; ++i)
	{
		testCouncilRoomDrawsCards(i);
	}
	return 0;
}