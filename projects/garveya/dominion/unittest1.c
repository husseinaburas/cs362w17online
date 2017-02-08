//test for dominion scoreFor function

#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "custom_assert.c"

#define SHOULD_ASSERT_FAIL 0

void testScoreForPlayer(int playerNum){
	char *testName = "Test scoreFor coins counted correctly for player";
	struct gameState testGameState;

	switch(playerNum){
		case 0:
			testName = "Test scoreFor for player 1";
			break;
		case 1:
			testName = "Test scoreFor for player 2";
			break;
		case 2:
			testName = "Test scoreFor for player 3";
			break;
		case 3:
			testName = "Test scoreFor for player 4";
			break;
	}

	//test 0 score
	testGameState.handCount[playerNum] = 0;
	testGameState.discardCount[playerNum] = 0;
	testGameState.deckCount[playerNum] = 0;

	custom_assert(scoreFor(playerNum, &testGameState) == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test score calculation for hand
	testGameState.handCount[playerNum] = 14;
	testGameState.hand[playerNum][0] = estate;
	testGameState.hand[playerNum][1] = duchy;
	testGameState.hand[playerNum][2] = province;
	testGameState.hand[playerNum][3] = curse;
	testGameState.hand[playerNum][4] = adventurer;
	testGameState.hand[playerNum][5] = smithy;
	testGameState.hand[playerNum][6] = estate;
	testGameState.hand[playerNum][7] = great_hall;
	testGameState.hand[playerNum][8] = gold;
	testGameState.hand[playerNum][9] = silver;
	testGameState.hand[playerNum][10] = sea_hag;
	testGameState.hand[playerNum][11] = province;
	testGameState.hand[playerNum][12] = duchy;
	testGameState.hand[playerNum][13] = curse;

	custom_assert(scoreFor(playerNum, &testGameState) == 19, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test score calculation for hand and discard
	testGameState.discardCount[playerNum] = 9;
	testGameState.discard[playerNum][0] = copper;
	testGameState.discard[playerNum][1] = duchy;
	testGameState.discard[playerNum][2] = baron;
	testGameState.discard[playerNum][3] = curse;
	testGameState.discard[playerNum][4] = great_hall;
	testGameState.discard[playerNum][5] = smithy;
	testGameState.discard[playerNum][6] = estate;
	testGameState.discard[playerNum][7] = feast;
	testGameState.discard[playerNum][8] = province;
	testGameState.discard[playerNum][9] = curse;

	custom_assert(scoreFor(playerNum, &testGameState) == 28, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test score calculation for hand, discard and deck
	testGameState.deckCount[playerNum] = 6;
	testGameState.discard[playerNum][0] = copper;
	testGameState.discard[playerNum][1] = adventurer;
	testGameState.discard[playerNum][2] = smithy;
	testGameState.discard[playerNum][3] = curse;
	testGameState.discard[playerNum][4] = great_hall;
	testGameState.discard[playerNum][5] = curse;

	custom_assert(scoreFor(playerNum, &testGameState) == 27, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test just deck
	testGameState.discardCount[playerNum] = 0;
	testGameState.handCount[playerNum] = 0;
	custom_assert(scoreFor(playerNum, &testGameState) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test just discard
	testGameState.discardCount[playerNum] = 9;
	testGameState.handCount[playerNum] = 0;
	testGameState.deckCount[playerNum] = 0;
	custom_assert(scoreFor(playerNum, &testGameState) == 9, testName, __LINE__, SHOULD_ASSERT_FAIL);

}

//tests if calculations for gardens card score is correct
void testGardensForPlayer(int playerNum){
	char *testName = "Test scoreFor gardens calculations for player";
	struct gameState testGameState;

	switch(playerNum){
		case 0:
			testName = "Test scoreFor gardens calculations for player 1";
			break;
		case 1:
			testName = "Test scoreFor gardens calculations for player 2";
			break;
		case 2:
			testName = "Test scoreFor gardens calculations for player 3";
			break;
		case 3:
			testName = "Test scoreFor gardens calculations for player 4";
			break;
	}

	//initialize counts
	testGameState.handCount[playerNum] = 0;
	testGameState.discardCount[playerNum] = 0;
	testGameState.deckCount[playerNum] = 0;

	//test gardens with only hand, less than 10 cards
	testGameState.handCount[playerNum] = 9;
	testGameState.hand[playerNum][0] = gold;
	testGameState.hand[playerNum][1] = adventurer;
	testGameState.hand[playerNum][2] = gardens;
	testGameState.hand[playerNum][3] = copper;
	testGameState.hand[playerNum][4] = adventurer;
	testGameState.hand[playerNum][5] = smithy;
	testGameState.hand[playerNum][6] = sea_hag;
	testGameState.hand[playerNum][7] = silver;
	testGameState.hand[playerNum][8] = gold;

	custom_assert(scoreFor(playerNum, &testGameState) == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test gardens with 10 cards
	testGameState.handCount[playerNum] = 10;
	testGameState.hand[playerNum][9] = gold;
	custom_assert(scoreFor(playerNum, &testGameState) == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test gardens with more than 10 cards
	testGameState.handCount[playerNum] = 11;
	testGameState.hand[playerNum][10] = silver;
	custom_assert(scoreFor(playerNum, &testGameState) == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test gardens with treasure cards
	testGameState.hand[playerNum][9] = province;
	testGameState.hand[playerNum][10] = curse;
	custom_assert(scoreFor(playerNum, &testGameState) == 6, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test discard with gardens
	testGameState.handCount[playerNum] = 0;
	testGameState.discardCount[playerNum] = 9;
	testGameState.discard[playerNum][0] = gold;
	testGameState.discard[playerNum][1] = adventurer;
	testGameState.discard[playerNum][2] = gardens;
	testGameState.discard[playerNum][3] = copper;
	testGameState.discard[playerNum][4] = adventurer;
	testGameState.discard[playerNum][5] = smithy;
	testGameState.discard[playerNum][6] = sea_hag;
	testGameState.discard[playerNum][7] = silver;
	testGameState.discard[playerNum][8] = gold;

	custom_assert(scoreFor(playerNum, &testGameState) == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test gardens with 10 cards
	testGameState.discardCount[playerNum] = 10;
	testGameState.discard[playerNum][9] = gold;
	custom_assert(scoreFor(playerNum, &testGameState) == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test gardens with more than 10 cards
	testGameState.discardCount[playerNum] = 11;
	testGameState.discard[playerNum][10] = silver;
	custom_assert(scoreFor(playerNum, &testGameState) == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test gardens with treasure cards
	testGameState.discard[playerNum][9] = province;
	testGameState.discard[playerNum][10] = curse;
	custom_assert(scoreFor(playerNum, &testGameState) == 6, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test deck with gardens
	testGameState.discardCount[playerNum] = 0;
	testGameState.deckCount[playerNum] = 9;
	testGameState.deck[playerNum][0] = gold;
	testGameState.deck[playerNum][1] = adventurer;
	testGameState.deck[playerNum][2] = gardens;
	testGameState.deck[playerNum][3] = copper;
	testGameState.deck[playerNum][4] = adventurer;
	testGameState.deck[playerNum][5] = smithy;
	testGameState.deck[playerNum][6] = sea_hag;
	testGameState.deck[playerNum][7] = silver;
	testGameState.deck[playerNum][8] = gold;

	custom_assert(scoreFor(playerNum, &testGameState) == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test gardens with 10 cards
	testGameState.deckCount[playerNum] = 10;
	testGameState.deck[playerNum][9] = gold;
	custom_assert(scoreFor(playerNum, &testGameState) == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test gardens with more than 10 cards
	testGameState.deckCount[playerNum] = 11;
	testGameState.deck[playerNum][10] = silver;
	custom_assert(scoreFor(playerNum, &testGameState) == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test gardens with treasure cards
	testGameState.deck[playerNum][9] = province;
	testGameState.deck[playerNum][10] = curse;
	custom_assert(scoreFor(playerNum, &testGameState) == 6, testName, __LINE__, SHOULD_ASSERT_FAIL);

}


int main(int argc, char const *argv[]){
	//test score for valid players
	int i;
	for(i = 0; i < MAX_PLAYERS; ++i){
		testScoreForPlayer(i);
	}

	for(i = 0; i < MAX_PLAYERS; ++i){
		testGardensForPlayer(i);
	}
	return 0;
}