


/*Thomas Mathew
CS 362
Assignment 4
*/

/*
case village:
//+1 Card
drawCard(currentPlayer, state);

//+2 Actions
state->numActions = state->numActions + 2;

//discard played card from hand
discardCard(handPos, currentPlayer, state, 0);
return 0;
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include<time.h>

#define TESTCARD "village"

//newGame() always starts with player 0.

int main() {


	//Finally finally, need to randomize...maybe the kingdom starting cards?
	//the point of the random tester is to randomize different inputs and test different scenarios. 
	//Sometimes if you do not give a good range of the input such as the number of players, 
	//your random tester is going to cover a small part of the domain code/function/card. 
	//By looking at the code, you might find out the reason for not covering/testing the 
	//other parts. You need to go back to your random tester and either expand the range 
	//of the input, add a function call, or randomize an input, etc... 
	//It is going to be your decision how to modify your test structure to increase the coverage.

	//Finally finally finally, need to use refactored dominion with bugs...

	//seed rand
	srand(time(NULL));

	int cardsDrawn = 0;
	int moneyDrawn = 0;
	int handCounter = 0;
	int playerCount = 2;
	int seed = 1000;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int temphand[MAX_HAND];
	int initialKingdom[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };



	struct gameState testGame1;


	//Let's test +2 Actions

	//Randomize the number of tests

	int howManyTests = (rand() % 10);
	int ii = 0;

	for (ii; ii < howManyTests; ii++)
	{

		// initialize a game state and player cards
		initializeGame(playerCount, initialKingdom, seed, &testGame1);
		int currentPlayer = whoseTurn(&testGame1);

		printf("Starting test of Village \n");

		printf("Testing if the current player gains 2 actions \n");

		//How many cards are in the current player's hand?
		int curActions = testGame1.numActions;
		printf("cur action = %d\n", curActions);


		//Random: 50/50 shot to add 1 or 2 actions. (supposed to be 2)
		//int expectedActions = curActions + 1 + (rand() % 1);
		int expectedActions = curActions + 2;

		printf("expected = %d\n", expectedActions);


		//Now do cardEffect(Village)
		cardEffect(village, choice1, choice2, choice3, &testGame1, handpos, &bonus);

		printf("result = %d\n", testGame1.numActions);

		//Now actions compared
		assert(testGame1.numActions == expectedActions);


		printf("village test passed \n");
	}

	return 0;
}