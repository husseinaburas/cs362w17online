//test for dominion updateCoins function

#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "custom_assert.c"
#include <limits.h>

#define SHOULD_ASSERT_FAIL 0

void testCoinCount(int playerNum){
	char *testName = "Test updateCoins coins counted correctly for player";
	struct gameState testGameState;

	switch(playerNum){
		case 0:
			testName = "Test updateCoins coins counted correctly for player 1";
			break;
		case 1:
			testName = "Test updateCoins coins counted correctly for player 2";
			break;
		case 2:
			testName = "Test updateCoins coins counted correctly for player 3";
			break;
		case 3:
			testName = "Test updateCoins coins counted correctly for player 4";
			break;
	}

	//test copper coins
	testGameState.hand[playerNum][0] = copper;
	testGameState.hand[playerNum][1] = copper;
	testGameState.handCount[playerNum] = 2;
	updateCoins(playerNum, &testGameState, 0);
	custom_assert(testGameState.coins == 2, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test non treasure cards
	testGameState.hand[playerNum][0] = adventurer;
	testGameState.hand[playerNum][1] = smithy;
	testGameState.handCount[playerNum] = 2;
	updateCoins(playerNum, &testGameState, 0);
	custom_assert(testGameState.coins == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test treasure and non treasure cards
	testGameState.hand[playerNum][0] = adventurer;
	testGameState.hand[playerNum][1] = copper;
	testGameState.hand[playerNum][2] = smithy;
	testGameState.handCount[playerNum] = 3;
	updateCoins(playerNum, &testGameState, 0);
	custom_assert(testGameState.coins == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test multiple treasure cards
	testGameState.hand[playerNum][0] = silver;
	testGameState.hand[playerNum][1] = copper;
	testGameState.hand[playerNum][2] = gold;
	testGameState.hand[playerNum][3] = copper;
	testGameState.hand[playerNum][4] = silver;
	testGameState.handCount[playerNum] = 5;
	updateCoins(playerNum, &testGameState, 0);
	custom_assert(testGameState.coins == 9, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//mix in non-treasure card
	testGameState.hand[playerNum][3] = gardens;
	updateCoins(playerNum, &testGameState, 0);
	custom_assert(testGameState.coins == 8, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//try with bonus
	updateCoins(playerNum, &testGameState, 1);
	custom_assert(testGameState.coins == 9, testName, __LINE__, SHOULD_ASSERT_FAIL);
}

void testBonus(){
	char *testName = "Test of updateCoins with bonuses";
	struct gameState testGameState;
	//test all valid players with different bonus amounts
	int i;
	for(i = 0; i < MAX_PLAYERS; ++i){
		//set handCount to 0 so no cards are counted
		testGameState.handCount[i] = 0;
		//test bonus of 1
		updateCoins(i, &testGameState, 1);
		custom_assert(testGameState.coins == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);
		//test bonus of 0
		updateCoins(i, &testGameState, 0);
		custom_assert(testGameState.coins == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);

		//test bonus of negative numbers
		int result = updateCoins(i, &testGameState, -1);
		custom_assert(testGameState.coins == 0 || result == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);

		//test maximum bonus
		updateCoins(i, &testGameState, INT_MAX);
		custom_assert(testGameState.coins == INT_MAX, testName, __LINE__, SHOULD_ASSERT_FAIL);
	}
}


//used to test combination of bonus with coins
void testBonusWithCoins(){
	char *testName = "Test of updateCoins with bonuses and coins";
	struct gameState testGameState;
	//test all valid players with different bonus amounts
	int i;
	for(i = 0; i < MAX_PLAYERS; ++i){
		testGameState.handCount[i] = 3;
		testGameState.hand[i][0] = gold;
		testGameState.hand[i][1] = copper;
		testGameState.hand[i][2] = silver;
		
		//test with positive bonus
		updateCoins(i, &testGameState, 5);
		custom_assert(testGameState.coins == 11, testName, __LINE__, SHOULD_ASSERT_FAIL);

		//test to see if bonus causes overflow
		int result = updateCoins(i, &testGameState, INT_MAX);
		//test to see if returned error, or somehow remained positive
		custom_assert(testGameState.coins > 0 || result == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);

		//test to see if bonus allows coin count to dip below 0
		result = updateCoins(i, &testGameState, -7);
		//test to see if returned error, or allowed minimum of 0 coins
		custom_assert(testGameState.coins == 0 || result == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);
	}
}

//test to make sure correct player's coins are counted
void testCorrectPlayersCoinsCounted(){
	char *testName = "Test updateCoins is counting correct player's coins";
	struct gameState testGameState;
	int i;
	for(i = 0; i < MAX_PLAYERS - 1; ++i){
		//set coins of player we are counting
		testGameState.handCount[i] = 3;
		testGameState.hand[i][0] = silver;
		testGameState.hand[i][1] = gold;
		testGameState.hand[i][2] = copper;

		//set next player to different amount of coins
		testGameState.handCount[i+1] = 2;
		testGameState.hand[i+1][0] = copper;
		testGameState.hand[i+1][1] = copper;
		
		//make sure correct player's coins are being counted
		updateCoins(i, &testGameState, 0);
		//test to see if returned error, or allowed minimum of 0 coins
		custom_assert(testGameState.coins == 6, testName, __LINE__, SHOULD_ASSERT_FAIL);

		//change player's coins, since they will now be the previous player
		testGameState.handCount[i] = 1;
		testGameState.hand[i][0] = adventurer;

	}
	//test last player
	int lastPlayer = MAX_PLAYERS - 1;
	testGameState.handCount[lastPlayer] = 4;
	testGameState.hand[lastPlayer][0] = adventurer;
	testGameState.hand[lastPlayer][1] = adventurer;
	testGameState.hand[lastPlayer][2] = silver;
	testGameState.hand[lastPlayer][3] = silver;
	updateCoins(lastPlayer, &testGameState, 0);
	custom_assert(testGameState.coins == 4, testName, __LINE__, SHOULD_ASSERT_FAIL);
}

int main(int argc, char const *argv[]){
	//test coin counting for all valid players
	int i;
	for(i = 0; i < MAX_PLAYERS; ++i){
		testCoinCount(i);
	}
	testBonus();
	testBonusWithCoins();
	testCorrectPlayersCoinsCounted();

	return 0;
}