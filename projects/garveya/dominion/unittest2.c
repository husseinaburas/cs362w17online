//test for dominion initializeGame function

#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "custom_assert.c"
#include <limits.h>

#define SHOULD_ASSERT_FAIL 0

//test to see if initializing gamestate with kingdom cards that
//contain duplicates causes error
//initializeGame should return -1 in this case
void testWithRepetitiveKindomCards(){
	char *testName = "Test initializeGame with repetitive kingdom cards";
	//create new gameState, as needed to test
	struct gameState* testGameState = newGame();
	int *testKingdomCards = kingdomCards(adventurer, adventurer, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy);

	//see if detects repeated kindomCards at first two indexes
	custom_assert(initializeGame(2, (int *) testKingdomCards, 1, testGameState) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);
	
	//swap duplicates
	testKingdomCards[1] = smithy;
	testKingdomCards[9] = adventurer;
	//see if detects repeated kindomCards at ends
	custom_assert(initializeGame(2, (int *) testKingdomCards, 1, testGameState) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test with duplicates in middle
	testKingdomCards[9] = gardens;
	testKingdomCards[5] = sea_hag;
	custom_assert(initializeGame(2, (int *) testKingdomCards, 1, testGameState) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	
	//test with duplicates at outer thirds
	testKingdomCards[5] = mine;
	testKingdomCards[6] = embargo;
	custom_assert(initializeGame(2, (int *) testKingdomCards, 1, testGameState) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);
	
	//test with 2 sets of duplicates
	testKingdomCards[2] = village;
	custom_assert(initializeGame(2, (int *) testKingdomCards, 1, testGameState) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//free memory allocated for gameState
	free(testGameState);
	//free memory from kindomCards
	free(testKingdomCards);
}


//test to see if it detects errors when kingdom cards are invalid
void testWithInvalidKindomCards(){
	char *testName = "Test initializeGame with invalid kingdom cards";
	//create new gameState, as needed to test
	struct gameState* testGameState = newGame();
	//test with kingdom card below range
	int *testKingdomCards = kingdomCards(adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, -1);
	custom_assert(initializeGame(2, (int *) testKingdomCards, 1, testGameState) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test with kingdom card above range
	testKingdomCards[9] = 27;
	custom_assert(initializeGame(2, (int *) testKingdomCards, 1, testGameState) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test with valid card that is not a kingdom card
	int i;
	for (i = 0; i <= 6; ++i){
		testKingdomCards[9] = i;
		custom_assert(initializeGame(2, (int *) testKingdomCards, 1, testGameState) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);
	}

	//free memory allocated for gameState
	free(testGameState);
	//free memory from kindomCards
	free(testKingdomCards);
}

//tests that initializeGame validates number of players
void testValidatePlayerCount(){
	char *testName = "Test initializeGame validates player count";

	//test with 1 player
	custom_assert(initializeGame(1, NULL, 1, NULL) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test with 0 players
	custom_assert(initializeGame(0, NULL, 1, NULL) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);
	
	//test with negative players
	custom_assert(initializeGame(-1, NULL, 1, NULL) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test above max players
	custom_assert(initializeGame(MAX_PLAYERS + 1, NULL, 1, NULL) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test with maximum integer value
	custom_assert(initializeGame(INT_MAX, NULL, 1, NULL) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test with minimum integer value
	custom_assert(initializeGame(INT_MIN, NULL, 1, NULL) == -1, testName, __LINE__, SHOULD_ASSERT_FAIL);
}

//tests whether gamestate's initial variables are set correctly
void testInitialVariables(){
	char *testName = "Test initializeGame set gameState variables correctly";
	//create new gameState, as needed to test
	struct gameState* testGameState = newGame();
	int *testKingdomCards = kingdomCards(adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy);

	initializeGame(2, (int *) testKingdomCards, 1, testGameState);

	//test number of players set
	custom_assert(testGameState->numPlayers == 2, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test outpost played count
	custom_assert(testGameState->outpostPlayed == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test phase set correctly
	custom_assert(testGameState->phase == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test num actions initialized correctly
	custom_assert(testGameState->numActions == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test num buys initialized correctly
	custom_assert(testGameState->numBuys == 1, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test played card count is initialized to 0
	custom_assert(testGameState->playedCardCount == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test whose turn is set to first player
	custom_assert(testGameState->whoseTurn == 0, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test that the handcount of first player is set to 5 cards
	custom_assert(testGameState->handCount[testGameState->whoseTurn] == 5, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//free memory allocated for gameState
	free(testGameState);
	//free memory from kindomCards
	free(testKingdomCards);
}

//test that supply is initialized correctly for given number of players
void testSupply(int numPlayers){
	char *testName = "Test initializeGame initializes supply correctly";
	int numCurses = 30;
	int numVictoryCards = 12;
	int numCopper = 60 - (7 * numPlayers);

	switch(numPlayers){
		case 2:
			testName = "Test initializeGame initializes supply correctly for 2 players";
			numCurses = 10;
			numVictoryCards = 8;
			break;
		case 3:
			testName = "Test initializeGame initializes supply correctly for 3 players";
			numCurses = 20;
			break;
		case 4:
			testName = "Test initializeGame initializes supply correctly for 4 players";
			break;
	}

	//create new gameState, as needed to test
	struct gameState* testGameState = newGame();
	int *testKingdomCards = kingdomCards(adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy);

	initializeGame(numPlayers, (int *) testKingdomCards, 1, testGameState);

	//test correct number of curses
	custom_assert(testGameState->supplyCount[curse] == numCurses, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test correct number of estates
	custom_assert(testGameState->supplyCount[estate] == numVictoryCards, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test correct number of duchies
	custom_assert(testGameState->supplyCount[duchy] == numVictoryCards, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test correct number of provinces
	custom_assert(testGameState->supplyCount[province] == numVictoryCards, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test correct number of copper
	custom_assert(testGameState->supplyCount[copper] == numCopper, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test correct number of silver
	custom_assert(testGameState->supplyCount[silver] == 40, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test correct number of gold
	custom_assert(testGameState->supplyCount[gold] == 30, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//free memory allocated for gameState
	free(testGameState);
	//free memory from kindomCards
	free(testKingdomCards);

}

int main(int argc, char const *argv[]){
	testWithRepetitiveKindomCards();
	testWithInvalidKindomCards();
	testValidatePlayerCount();
	testInitialVariables();
	//test supply for legal player counts
	//illegal counts are already tested in testValidatePlayerCount()
	int i;
	for(i = 2; i <= MAX_PLAYERS; ++i){
		testSupply(i);
	}
	return 0;
}