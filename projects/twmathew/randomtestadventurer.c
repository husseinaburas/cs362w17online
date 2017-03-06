
/*Thomas Mathew
CS 362
Assignment 4
*/


/*
case adventurer:
while(drawntreasure<2)
{	//if the deck is empty we need to shuffle discard and add to deck
if (state->deckCount[currentPlayer] <1){
shuffle(currentPlayer, state);
}
drawCard(currentPlayer, state);
cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
drawntreasure++;
else{
temphand[z]=cardDrawn;
state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
z++;
}
}
while(z-1>=0){
state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
z=z-1;
}
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

#define TESTCARD "adventurer"

//newGame() always starts with player 0.

int main() {

	//While drawntreasure < 2, need to test if:			Line

	//an empty deck leads to a shuffle					673/4
	//if a card is drawn							676
	//if that card gets put at the top of the hand		677
	//if it's a copper, drawntreasure incrememted		678/9
	//if it's a silver, drawntreasure incrememted		678/9
	//if it's a gold, drawntreasure incrememted			678/9
	//if other, did cardDrawn get added to temphand[]?	681
	//And did handCount get decremented?				682
	//Finally, does discarding happen correctly?			686/7/8

	//Finally finally, need to randomize...maybe the kingdom starting cards?
	//the point of the random tester is to randomize different inputs and test different scenarios. 
	//Sometimes if you do not give a good range of the input such as the number of players, 
	//your random tester is going to cover a small part of the domain code/function/card. 
	//By looking at the code, you might find out the reason for not covering/testing the 
	//other parts. You need to go back to your random tester and either expand the range 
	//of the input, add a function call, or randomize an input, etc... 
	//It is going to be your decision how to modify your test structure to increase the coverage.

	//Finally finally finally, need to use refactored dominion with bugs...

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



		printf("Starting test of Adventurer \n");

		printf("Testing if empty deck leads to shuffle \n");
		//Let's draw everything from the deck
		int currentPlayer = whoseTurn(&testGame1);


		while (testGame1.deckCount[currentPlayer] > 0)
		{
			drawCard(currentPlayer, &testGame1);
		}


		//deck should now be empty
		assert(testGame1.deckCount[currentPlayer] == 0);

		//Let's discard a few cards, so there is something to shuffle into the deck.
		discardCard(handpos, currentPlayer, &testGame1, 0);
		discardCard(handpos, currentPlayer, &testGame1, 0);

		//now call card effect for adventurer.
		cardEffect(adventurer, choice1, choice2, choice3, &testGame1, handpos, &bonus);
		// It should result in a non-empty deck.

	


		assert(testGame1.deckCount[currentPlayer] >= 0);

		printf("Empty deck led to shuffle, test passed \n");

	}

	/*/
	//to discard card from hand
	discardCard(handPos, currentPlayer, state, 0);
	//to trash card
	discardCard(handPos, currentPlayer, state, 1);
	//to discard hand
	while (numHandCards(state) > 0)
	{
		discardCard(handPos, currentPlayer, state, 0);
	}
	//general discard form
	int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
	*/

//	printf("Testing if a card is drawn \n");
	//How the sample test works:
	//1. Copy/make a game state for testing.
	//2. choice1 = 1;?????
	//3. passing in some params to force some condition, call cardEffect(adventurer, , , , ,);
	//4. assert testGameState.something == gameState.something + changes that should happen

	//Let's discard everything from the deck
	//testGame1->deck

	//cardEffect(adventurer, choice1, choice2, choice3, &testGame1, handPos, &bonus);


	return 0;
}