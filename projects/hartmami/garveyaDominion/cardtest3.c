//test for adventurer card

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

//returns count of treasure cards in hand
int countTreasureCards(int playerNum, struct gameState *testGameState){
	int ret = 0;
	int i;
	for(i = 0; i < testGameState->handCount[playerNum]; ++i){
		int currentCard = testGameState->hand[playerNum][i];
		if(currentCard == copper || currentCard == silver || currentCard == gold){
			ret++;
		}
	}

	return ret;
}

void testAdventurerAddsTreasure(int playerNum){
	char *testName = "Test adventurer card adds 2 treasures";
	struct gameState testGameState;
	//initialize for discardCard
	testGameState.playedCardCount = 0;
	//initialize player hand
	testGameState.handCount[playerNum] = 1;
	testGameState.hand[playerNum][0] = adventurer;
	//initialize discard
	testGameState.discardCount[playerNum] = 4;
	testGameState.discard[playerNum][0] = smithy;
	testGameState.discard[playerNum][0] = gold;
	testGameState.discard[playerNum][0] = province;
	testGameState.discard[playerNum][0] = silver;

	playAdventurer(playerNum, &testGameState);
	//test adventurer discarded
	custom_assert(!isInHand(playerNum, &testGameState, adventurer), testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(testGameState.handCount[playerNum] == 2, testName, __LINE__, SHOULD_ASSERT_FAIL);
	//test adventurer is not in hand and 2 treasures have been added
	custom_assert(countTreasureCards(playerNum, &testGameState) == 2, testName, __LINE__, SHOULD_ASSERT_FAIL);
	//test treasures taken from discard pile
	custom_assert(testGameState.discardCount[playerNum] == 2, testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(testGameState.discard[playerNum][1] == province, testName, __LINE__, SHOULD_ASSERT_FAIL);

}

int main(int argc, char const *argv[]){
	int i;
	for (i = 0; i < MAX_PLAYERS; ++i)
	{
		testAdventurerAddsTreasure(i);
	}
	
	return 0;
}