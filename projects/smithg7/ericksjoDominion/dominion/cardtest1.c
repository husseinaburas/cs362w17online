/***************************************
 CS362 - Assignment 3
 Gary Smith
 Card Test 1 - Smithy
***************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Smithy"

void assertTrue(int firstValue, int secondValue, char* message);

int main() {
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState baseState, testedState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &baseState);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- Test 1: It is that player’s turn --------------
	
	printf("Test 1: It is that player’s turn\n");
	memcpy(&testedState, &baseState, sizeof(struct gameState));	

	testedState.hand[thisPlayer][0] = smithy;
	playSmithy(&testedState, 0);
	assertTrue(testedState.whoseTurn, baseState.whoseTurn, "It is player 0's turn.");


	// ----------- Test 2: 3 cards are added to the hand of that player --------------
	printf("Test 2: 3 cards are added to the hand of that player.\n");
	memcpy(&testedState, &baseState, sizeof(struct gameState));	

	testedState.hand[thisPlayer][0] = smithy;
	playSmithy(&testedState, 0);
	assertTrue(testedState.handCount[thisPlayer], baseState.handCount[thisPlayer] + 2, "Testing drawing 3 cards and discarding 1. ");


	// ----------- Test 3: No cards are added to any other pile --------------
	printf("Test 3: changes to other piles\n");
	memcpy(&testedState, &baseState, sizeof(struct gameState));	

	testedState.hand[whoseTurn(&testedState)][0] = smithy;
	playSmithy(&testedState, 0);
	assertTrue(testedState.deckCount[thisPlayer], baseState.deckCount[thisPlayer]-3, "Player 0's deck, (-3). ");
	assertTrue(testedState.handCount[thisPlayer], baseState.handCount[thisPlayer]+2, "Player 0's hand, (+2). ");
	assertTrue(testedState.playedCardCount, baseState.playedCardCount +1 , "Player 0's played card pile (+1). ");
	assertTrue(testedState.handCount[1], baseState.handCount[1], "Player 1's hand, no change. ");
	assertTrue(testedState.deckCount[1], baseState.deckCount[1], "Player 1's deck, no change. ");
	assertTrue(testedState.discardCount[1], baseState.discardCount[1], "Player 1's discard, no change. ");


	// ----------- Test 4: Actions are decreased by 1 --------------
	printf("Test 4: Actions are decreased by 1\n");
	memcpy(&testedState, &baseState, sizeof(struct gameState));	

	testedState.hand[thisPlayer][0] = smithy;
	playSmithy(&testedState, 0);
	assertTrue(testedState.numActions, baseState.numActions, "Player 0's actions are decreased by 1. ");
	

	// ----------- Test 5: Smithy card is discarded after use --------------
	printf("Test 5: Smithy card is added to the played card pile after use\n");
	memcpy(&testedState, &baseState, sizeof(struct gameState));	

	testedState.hand[thisPlayer][0] = smithy;
	playSmithy(&testedState, 0);
	assertTrue(testedState.playedCardCount, baseState.playedCardCount+1, "Player 0's played card count increases by 1. ");



	printf("\n >>>>> SUCCESS: Testing complete for %s <<<<<\n\n", TESTCARD);


	return 0;
}


/***************************************
Custom AssertTrue function to provide more info and prevent
the whole program from crashing
***************************************/
void assertTrue(int firstValue, int secondValue, char* message)
{
  if(firstValue == secondValue)
  {
    printf("\tTEST PASSED SUCCESSFULLY: %s\n", message);
  }
  else
  {
    printf("\tTEST FAILED: %s Actual value: %i; Expected Value: %i\n", message, firstValue, secondValue);
  }

}
