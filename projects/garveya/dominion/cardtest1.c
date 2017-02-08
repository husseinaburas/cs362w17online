//test for smithy card
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

void testSmithyWithCardsInDeck(int playerNum){
	char *testName = "Test of smithy card when there are cards in deck";

	struct gameState testGameState;
	//initialize for discardCard
	testGameState.playedCardCount = 0;
	//initialize player hand and deck
	testGameState.handCount[playerNum] = 3;
	testGameState.hand[playerNum][0] = smithy;
	testGameState.hand[playerNum][1] = adventurer;
	testGameState.hand[playerNum][2] = copper;

	testGameState.deckCount[playerNum] = 3;
	testGameState.deck[playerNum][0] = silver;
	testGameState.deck[playerNum][1] = province;
	testGameState.deck[playerNum][2] = sea_hag;

	playSmithy(playerNum, &testGameState, 0);

	//test smithy is not in hand anymore
	custom_assert(testGameState.hand[playerNum][0] != smithy, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test hand has 2 more cards (+3 cards - smithy)
	custom_assert(testGameState.handCount[playerNum] == 5, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test that cards came from the deck and added to hand
	custom_assert(testGameState.hand[playerNum][2] == silver, testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(testGameState.hand[playerNum][3] == province, testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(testGameState.hand[playerNum][4] == sea_hag, testName, __LINE__, SHOULD_ASSERT_FAIL);
}

//test smithy when no cards in deck, but cards in discard
void testSmithyWithNoCardsInDeck(int playerNum){
	char *testName = "Test of smithy card when there are no cards in deck, but in discard";

	struct gameState testGameState;
	//initialize for discardCard
	testGameState.playedCardCount = 0;
	//initialize player hand and discard
	testGameState.handCount[playerNum] = 3;
	testGameState.hand[playerNum][0] = smithy;
	testGameState.hand[playerNum][1] = adventurer;
	testGameState.hand[playerNum][2] = copper;

	testGameState.deckCount[playerNum] = 0;

	testGameState.discardCount[playerNum] = 3;
	testGameState.discard[playerNum][0] = silver;
	testGameState.discard[playerNum][1] = province;
	testGameState.discard[playerNum][2] = sea_hag;

	playSmithy(playerNum, &testGameState, 0);

	//test smithy is not in hand anymore
	custom_assert(testGameState.hand[playerNum][0] != smithy, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test hand has 2 more cards (+3 cards - smithy)
	custom_assert(testGameState.handCount[playerNum] == 5, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test that cards came from the deck and added to hand
	//have to check whole hand, because it should be shuffled
	custom_assert(isInHand(playerNum, &testGameState, silver), testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(isInHand(playerNum, &testGameState, province), testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(isInHand(playerNum, &testGameState, sea_hag), testName, __LINE__, SHOULD_ASSERT_FAIL);
}

//test smithy with some cards in deck, and some in discard
void testSmithyWithSomeCardsInDeck(int playerNum){
	char *testName = "Test of smithy card when there are some cards in deck, and some in discard";

	struct gameState testGameState;
	//initialize for discardCard
	testGameState.playedCardCount = 0;
	//initialize player hand and discard
	testGameState.handCount[playerNum] = 3;
	testGameState.hand[playerNum][0] = smithy;
	testGameState.hand[playerNum][1] = adventurer;
	testGameState.hand[playerNum][2] = copper;

	testGameState.deckCount[playerNum] = 2;
	testGameState.deck[playerNum][0] = silver;
	testGameState.deck[playerNum][1] = province;

	testGameState.discardCount[playerNum] = 1;
	testGameState.discard[playerNum][0] = sea_hag;

	playSmithy(playerNum, &testGameState, 0);

	//test smithy is not in hand anymore
	custom_assert(testGameState.hand[playerNum][0] != smithy, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test hand has 2 more cards (+3 cards - smithy)
	custom_assert(testGameState.handCount[playerNum] == 5, testName, __LINE__, SHOULD_ASSERT_FAIL);

	//test that cards came from the deck and added to hand
	//have to check whole hand, because it should be shuffled
	custom_assert(isInHand(playerNum, &testGameState, silver), testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(isInHand(playerNum, &testGameState, province), testName, __LINE__, SHOULD_ASSERT_FAIL);
	custom_assert(isInHand(playerNum, &testGameState, sea_hag), testName, __LINE__, SHOULD_ASSERT_FAIL);
}



int main(int argc, char const *argv[]){
	int i;
	for(i = 0; i < MAX_PLAYERS; ++i){
		testSmithyWithCardsInDeck(i);
	}

	for(i = 0; i < MAX_PLAYERS; ++i){
		testSmithyWithNoCardsInDeck(i);
	}

	for(i = 0; i < MAX_PLAYERS; ++i){
		testSmithyWithSomeCardsInDeck(i);
	}
	return 0;
}