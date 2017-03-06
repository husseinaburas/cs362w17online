

/*Thomas Mathew
CS 362
Assignment 4
*/

/*
    case council_room:
	    //+4 Cards
	    for (i = 0; i < 4; i++)
	    {
		    drawCard(currentPlayer, state);
	    }

	    //+1 Buy
	    state->numBuys++;

	    //Each other player draws a card
	    for (i = 0; i < state->numPlayers; i++)
	    {
		    if (i != currentPlayer)
		    {
			    drawCard(i, state);
		    }
	    }
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include<time.h>

#define TESTCARD "council_room"

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

	//Randomize the number of tests
	int howManyTests = (rand() % 10);
	int ii = 0;

	for (ii; ii < howManyTests; ii++)
	{


		// initialize a game state and player cards
		initializeGame(playerCount, initialKingdom, seed, &testGame1);
		int currentPlayer = whoseTurn(&testGame1);

		printf("Starting test of Council Room \n");

		printf("Testing if the current player draws 4 cards \n");

		//How many cards are in the current player's hand?
		int curCards = testGame1.handCount[currentPlayer];

		//Random: 50/50 shot to add 3 cards, or 4 (supposed to be 4)
	//	int randAdd = 3 + (rand() % 1);
		int randAdd = 3;
		int expectedHandCount = randAdd + curCards;

		printf("expected = %d\n", expectedHandCount);


		//Now do cardEffect(council room)
		cardEffect(council_room, choice1, choice2, choice3, &testGame1, handpos, &bonus);

		printf("result = %d\n", testGame1.handCount[currentPlayer]);

		//Now hand cards should == expectedHandCount
		assert(testGame1.handCount[currentPlayer] == expectedHandCount);


		printf("4 cards were drawn, test passed \n");

	}

	return 0;
}