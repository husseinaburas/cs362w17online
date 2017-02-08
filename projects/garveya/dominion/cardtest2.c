//test for cutpurse card

#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "custom_assert.c"

#define SHOULD_ASSERT_FAIL 0

//so it prints out player's cards
//from: http://stackoverflow.com/questions/8159256/redefining-a-constant-in-c
#ifdef DEBUG
#undef DEBUG
#endif
#define DEBUG 1

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

//returns count of card in hand
int countCard(int playerNum, struct gameState *testGameState, int card){
	int ret = 0;
	int i;
	for(i = 0; i < testGameState->handCount[playerNum]; ++i){
		if(testGameState->hand[playerNum][i] == card){
			ret++;
		}
	}

	return ret;
}

//test cutpurse when other players have copper
void testCutpurseWithCopper(int playerNum){
	char *testName = "Test of cutpurse card when other players have copper";

	struct gameState testGameState;
	testGameState.numPlayers = 3;
	//initialize for discardCard
	testGameState.playedCardCount = 0;
	//initialize player hand
	testGameState.handCount[playerNum] = 1;
	testGameState.hand[playerNum][0] = cutpurse;

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

	testGameState.handCount[player2] = 1;
	testGameState.hand[player2][0] = copper;

	testGameState.handCount[player3] = 3;
	testGameState.hand[player3][0] = copper;
	testGameState.hand[player3][1] = smithy;
	testGameState.hand[player3][2] = copper;

	playCutpurse(playerNum, &testGameState, 0);

	//test player has 1 less card and doesn't have cutpurse anymore
	custom_assert(testGameState.handCount[playerNum] == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(!isInHand(playerNum, &testGameState, cutpurse), testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test that player2 has 1 less card
	custom_assert(testGameState.handCount[player2] == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(!isInHand(player2, &testGameState, copper), testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test that player3 has 1 less card
	custom_assert(testGameState.handCount[player3] == 2, testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(countCard(player3, &testGameState, copper) == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);
}


//test cutpurse when other players do not have copper
void testCutpurseWithoutCopper(int playerNum){
	char *testName = "Test of cutpurse card when other players do not have copper";

	struct gameState testGameState;
	testGameState.numPlayers = 3;
	//initialize for discardCard
	testGameState.playedCardCount = 0;
	//initialize player hand
	testGameState.handCount[playerNum] = 1;
	testGameState.hand[playerNum][0] = cutpurse;

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

	testGameState.handCount[player2] = 1;
	testGameState.hand[player2][0] = silver;

	testGameState.handCount[player3] = 3;
	testGameState.hand[player3][0] = gold;
	testGameState.hand[player3][1] = smithy;
	testGameState.hand[player3][2] = adventurer;

	playCutpurse(playerNum, &testGameState, 0);

	//test player has 1 less card and doesn't have cutpurse anymore
	custom_assert(testGameState.handCount[playerNum] == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(!isInHand(playerNum, &testGameState, cutpurse), testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test that player2 has same cards
	custom_assert(testGameState.handCount[player2] == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(testGameState.hand[player2][0] == silver, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test that player3 has same cards
	custom_assert(testGameState.handCount[player3] == 3, testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(testGameState.hand[player3][0] == gold, testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(testGameState.hand[player3][1] == smithy, testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(testGameState.hand[player3][2] == adventurer, testName, __LINE__, SHOULD_ASSERT_FAIL);
}

//tests that cutpurse adds 2 coins to player
void testCutpurseBonus(){
	char *testName = "Test of cutpurse card gives correct bonus to player";

	struct gameState testGameState;
	testGameState.numPlayers = 1;
	//initialize for discardCard
	testGameState.playedCardCount = 0;
	//initialize player hand
	testGameState.handCount[0] = 1;
	testGameState.hand[0][0] = cutpurse;

	playCutpurse(0, &testGameState, 0);
	int cutpurseBonus = testGameState.coins;
	int cutpurseCorrectBonus = updateCoins(0, &testGameState, 2);
	custom_assert(cutpurseBonus == cutpurseCorrectBonus, testName, __LINE__, SHOULD_ASSERT_FAIL);
}



int main(int argc, char const *argv[]){
	int i;
	for(i = 0; i < MAX_PLAYERS - 1; ++i){
		testCutpurseWithCopper(i);
	}
	for(i = 0; i < MAX_PLAYERS - 1; ++i){
		testCutpurseWithoutCopper(i);
	}
	testCutpurseBonus();
	return 0;
}