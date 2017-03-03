//test for isGameOver
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "dominion.h"
#include "custom_assert.c"

#define SHOULD_ASSERT_FAIL 0


//test when no provinces but still supply count
void testProvincesDepleted(){
	char *testName = "Test isGameOver when no provinces but still supply";
	struct gameState testGameState;
	int i;
	//test with supply 1
	for(i = 0; i < treasure_map+1; ++i){
		testGameState.supplyCount[i] = 1;
	}
	testGameState.supplyCount[province] = 0;
	custom_assert(isGameOver(&testGameState) == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test with supply 100
	for(i = 0; i < treasure_map+1; ++i){
		testGameState.supplyCount[i] = 100;
	}
	testGameState.supplyCount[province] = 0;
	custom_assert(isGameOver(&testGameState) == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test with supply negative
	for(i = 0; i < treasure_map+1; ++i){
		testGameState.supplyCount[i] = -1;
	}
	testGameState.supplyCount[province] = 0;
	custom_assert(isGameOver(&testGameState) == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);


}

//test when provinces, but at least 3 supply counts depleted
void testSupplyDepleted(){
	char *testName = "Test isGameOver when provinces but at least 3 supply piles empty";
	struct gameState testGameState;
	int i;
	//test with province 1 and all other 0
	for(i = 0; i < treasure_map+1; ++i){
		testGameState.supplyCount[i] = 0;
	}

	testGameState.supplyCount[province] = 1;
	custom_assert(isGameOver(&testGameState) == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test with province 1 and 3 other 0
	for(i = 0; i < treasure_map+1; ++i){
		testGameState.supplyCount[i] = 6;
	}
	testGameState.supplyCount[province+1] = 0;
	testGameState.supplyCount[province+2] = 0;
	testGameState.supplyCount[province+3] = 0;
	testGameState.supplyCount[province] = 1;
	custom_assert(isGameOver(&testGameState) == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

}

//test when provinces and supply depleted
void testProvincesAndSupplyDepleted(){
	char *testName = "Test isGameOver when no provinces and at least 3 supply piles empty";
	struct gameState testGameState;

	int i;
	//test with all 0
	for(i = 0; i < treasure_map+1; ++i){
		testGameState.supplyCount[i] = 0;
	}

	testGameState.supplyCount[province] = 0;
	custom_assert(isGameOver(&testGameState) == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test with province 0 and 3 others 0
	for(i = 0; i < treasure_map+1; ++i){
		testGameState.supplyCount[i] = 6;
	}
	testGameState.supplyCount[province+1] = 0;
	testGameState.supplyCount[province+2] = 0;
	testGameState.supplyCount[province+3] = 0;
	testGameState.supplyCount[province] = 0;
	custom_assert(isGameOver(&testGameState) == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

}

//test when neither provinces or supply depleted
void testGameNotEnded(){
	char *testName = "Test isGameOver when provinces and still supply";
	struct gameState testGameState;

	int i;
	//test with all 1
	for(i = 0; i < treasure_map+1; ++i){
		testGameState.supplyCount[i] = 1;
	}

	custom_assert(isGameOver(&testGameState) == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test with all max int
	for(i = 0; i < treasure_map+1; ++i){
		testGameState.supplyCount[i] = INT_MAX;
	}

	custom_assert(isGameOver(&testGameState) == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test with 2 piles empty
	//test with all 1
	for(i = 0; i < treasure_map+1; ++i){
		testGameState.supplyCount[i] = 1;
	}
	testGameState.supplyCount[province+1] = 0;
	testGameState.supplyCount[province+2] = 0;

	custom_assert(isGameOver(&testGameState) == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);

}


int main(int argc, char const *argv[]){
	testProvincesDepleted();
	testSupplyDepleted();
	testProvincesAndSupplyDepleted();
	testGameNotEnded();

	return 0;
}