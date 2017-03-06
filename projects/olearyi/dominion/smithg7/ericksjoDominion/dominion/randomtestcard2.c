/***************************************
 CS362 - Assignment 4
 Gary Smith
 Random Card Test 2 - Village
***************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define TESTCARD "Village"
#define NUMTESTS 1000

int assertTrue(int firstValue, int secondValue);

int main(int argc, char** argv) {
	int i = 0, j = 0;
    int numPlayers = 2;
    int thisPlayer = 0;
    int testSuccess[9] = {0,0,0,0,0,0,0,0,0};
	struct gameState baseState, testedState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	printf("----------------- Beginning Random Tests for %s ----------------\n", TESTCARD);

	//Check command line argument
	if(argc != 2)
	{
		printf("A random seed must be provided.  Proper usage: 'randomtestadventurer <integer>'");
		return 0;
	}

  	SelectStream(1);
  	PutSeed((long)atoi(argv[1]));

  	for (i = 0; i < NUMTESTS; i++)
  	{
		/*************************************************************
			Set Random values for
				1.) Number of players (must have at least 2 players)
				2.) Coins (1-100)
				3.) Player's hand count
				4.) Player's hand (loop through hand count & set card value between 0 and 26)
				5.) Player's deck count
				6.) Player's Deck (loop through deck count & set card value between 0 and 26)
				7.) num Actions (0..4)
		*************************************************************/
		//Number of players
		numPlayers = 2+(int)floor(Random()*6);
		thisPlayer = (int)floor(Random()*numPlayers);

		initializeGame(numPlayers, k, atoi(argv[1]), &baseState);

		//Whose turn
		baseState.whoseTurn = thisPlayer;

		//Coins
		baseState.coins = (int)floor(Random()*100);

		//Player's hand & hand count
		baseState.handCount[thisPlayer] = (int)floor(Random()*MAX_HAND);
		for (j=0; j < baseState.handCount[thisPlayer]; j++)
		{
			baseState.hand[thisPlayer][j] = (int)floor(Random()*26);
		}
		//Set first card in hand to be the adventurer card (must have the card to play)
		baseState.hand[thisPlayer][0] = adventurer;


		//Player's deck & deck count
		baseState.deckCount[thisPlayer] = (int)floor(Random()*MAX_DECK);
		for (j=0; j < baseState.deckCount[thisPlayer]; j++)
		{
			baseState.deck[thisPlayer][j] = (int)floor(Random()*26);
		}

		//Num Actions (0,1)
		baseState.numActions = (int)floor(Random()*4);
		// initialize a game state and player cards

		baseState.hand[thisPlayer][0] = village;
		memcpy(&testedState, &baseState, sizeof(struct gameState));	

		//int handleAdventurer(int currentPlayer, struct gameState *state, int handPos, int drawntreasure, int* temphand)
		playVillage(&testedState, 0);

		testSuccess[0] += assertTrue(testedState.whoseTurn, baseState.whoseTurn);
		testSuccess[1] += assertTrue(testedState.handCount[thisPlayer], baseState.handCount[thisPlayer] + 0);
		testSuccess[2] += assertTrue(testedState.deckCount[thisPlayer], baseState.deckCount[thisPlayer]-1);
		testSuccess[3] += assertTrue(testedState.playedCardCount, baseState.playedCardCount +1);
		testSuccess[4] += assertTrue(testedState.handCount[1], baseState.handCount[1]);
		testSuccess[5] += assertTrue(testedState.deckCount[1], baseState.deckCount[1]);
		testSuccess[6] += assertTrue(testedState.discardCount[1], baseState.discardCount[1]);
		testSuccess[7] += assertTrue(testedState.numActions, baseState.numActions+2);
		testSuccess[8] += assertTrue(testedState.playedCardCount, baseState.playedCardCount+1);

	}


	printf("\n >>>>> SUCCESS: Random testing complete for %s <<<<<\n\n", TESTCARD);
	for (i = 0; i < 9; i++)
	{
		printf("Succesful runs of Test %i: %i; Failed runs of Test %i: %i \n", i+1, testSuccess[i], i+1, NUMTESTS-testSuccess[i]);
	}

	return 0;
}


/***************************************
Custom AssertTrue function to provide more info and prevent
the whole program from crashing
***************************************/
int assertTrue(int firstValue, int secondValue)
{
  if(firstValue == secondValue)
  {
    //printf("\tTEST PASSED SUCCESSFULLY: %s\n", message);
    return 1;
  }
  else
  {
    //printf("\tTEST FAILED: %s Actual value: %i; Expected Value: %i\n", message, firstValue, secondValue);
    return 0;
  }

}
