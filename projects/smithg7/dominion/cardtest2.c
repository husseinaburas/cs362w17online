/***************************************
 CS362 - Assignment 3
 Gary Smith
 Card Test 2 - Adventurer
***************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Adventurer"

void assertTrue(int firstValue, int secondValue, char* message);

int main() {
	int i = 0;
	int temphand[MAX_HAND];
    int seed = 1001;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState baseState, testedState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &baseState);
	
	//Set first card in hand to be the adventurer card.
	baseState.hand[thisPlayer][0] = adventurer;
	//Set the order of the deck.
	baseState.deck[thisPlayer][0] = estate;
	baseState.deck[thisPlayer][1] = gold;
	baseState.deck[thisPlayer][2] = estate;
	baseState.deck[thisPlayer][3] = copper;
	baseState.deck[thisPlayer][4] = estate;
	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- Test 1: It is that player’s turn --------------
	printf("Test 1: It is that player’s turn\n");
	memcpy(&testedState, &baseState, sizeof(struct gameState));	


	//int handleAdventurer(int currentPlayer, struct gameState *state, int handPos, int drawntreasure, int* temphand)
	handleAdventurer(thisPlayer, &testedState, 0, 0, temphand);
	assertTrue(testedState.whoseTurn, baseState.whoseTurn, "It is player 0's turn.");


	// ----------- Test 2: 2 treasure cards are added to that player’s hand. --------------
	printf("Test 2: 2 treasure cards are added to that player’s hand.\n");
	memcpy(&testedState, &baseState, sizeof(struct gameState));	

	handleAdventurer(thisPlayer, &testedState, 0, 0, temphand);
	int beforeTreasure = 0, afterTreasure = 0;
	for (i = 0; i < testedState.handCount[thisPlayer]; i++)
	{
		if (testedState.hand[thisPlayer][i] == gold || 
			testedState.hand[thisPlayer][i] == silver || 
			testedState.hand[thisPlayer][i] == copper)
			afterTreasure++;
	}
	for (i = 0; i < baseState.handCount[thisPlayer]; i++)
	{
		if (baseState.hand[thisPlayer][i] == gold || 
			baseState.hand[thisPlayer][i] == silver || 
			baseState.hand[thisPlayer][i] == copper)
			beforeTreasure++;
	}
	assertTrue(afterTreasure, beforeTreasure + 2, "Player 0's treasure count increased by 2.");


	// ----------- Test 3: Player's hand increases by 2 --------------
	printf("Test 3: Player's hand increases by 2.\n");
	memcpy(&testedState, &baseState, sizeof(struct gameState));	

	handleAdventurer(thisPlayer, &testedState, 0, 0, temphand);
	assertTrue(testedState.handCount[thisPlayer], baseState.handCount[thisPlayer]+2, "Player 0's hand increases by 2. ");


	// ----------- Test 4: Discard pile count increases by # of cards drawn --------------
	printf("Test 4: Discard card pile count increases by # of cards drawn\n");
	memcpy(&testedState, &baseState, sizeof(struct gameState));	


	handleAdventurer(thisPlayer, &testedState, 0, 0, temphand);
	assertTrue(testedState.discardCount[thisPlayer], 2, "Player 0's discard pile increased by 2 estate cards. ");


	// ----------- Test 5: Actions are decreased by 1 --------------
	printf("Test 5: Actions are decreased by 1\n");
	memcpy(&testedState, &baseState, sizeof(struct gameState));	

	handleAdventurer(thisPlayer, &testedState, 0, 0, temphand);
	assertTrue(testedState.numActions, baseState.numActions, "Player 0's actions are decreased by 1. ");
	

	// ----------- Test 6: Adventurer  card is discarded after use --------------
	printf("Test 6: Adventurer card is added to the played card pile after use\n");
	memcpy(&testedState, &baseState, sizeof(struct gameState));	

	handleAdventurer(thisPlayer, &testedState, 0, 0, temphand);
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
