/*
test for
int scoreFor (int player, struct gameState *state) {

  int i;
  int score = 0;
  //score from hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == curse) { score = score - 1; };
      if (state->hand[player][i] == estate) { score = score + 1; };
      if (state->hand[player][i] == duchy) { score = score + 3; };
      if (state->hand[player][i] == province) { score = score + 6; };
      if (state->hand[player][i] == great_hall) { score = score + 1; };
      if (state->hand[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  //score from discard
  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == curse) { score = score - 1; };
      if (state->discard[player][i] == estate) { score = score + 1; };
      if (state->discard[player][i] == duchy) { score = score + 3; };
      if (state->discard[player][i] == province) { score = score + 6; };
      if (state->discard[player][i] == great_hall) { score = score + 1; };
      if (state->discard[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  //score from deck
  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->deck[player][i] == curse) { score = score - 1; };
      if (state->deck[player][i] == estate) { score = score + 1; };
      if (state->deck[player][i] == duchy) { score = score + 3; };
      if (state->deck[player][i] == province) { score = score + 6; };
      if (state->deck[player][i] == great_hall) { score = score + 1; };
      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  return score;
}

}
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main()
{
	printf("-----CURRENT TEST: scoreFor function-----\n");
	struct gameState  currentgame; // create new game and set num players
	int numplayers = 2;
	int x;
	int randomseed = 477;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall}; // set kingdom cards array
	int gameinit = initializeGame(numplayers, k, randomseed, &currentgame); // initialize the game

	// As soon as the game starts, everyone should have 3 points, test this base case here.
	if ((scoreFor(0, &currentgame) != 3) || (scoreFor(1, &currentgame) != 3))
	{
		printf("Test failed! Score for both players should be 3\n");
		printf("Score 1: %d , Score 2: %d \n" , scoreFor(0, &currentgame) ,scoreFor(1, &currentgame) );
		// exit(0);
	}
	else
	{
		printf("Test passed! Both players have 3 points");
	}
	
	//Check for the discard pile, so empty the deck and hand and check accordingly
	currentgame.handCount[0] = 0;
	currentgame.handCount[1] = 0; 
	currentgame.deckCount[0] = 0;
	currentgame.deckCount[1] = 0;
	currentgame.discardCount[0] = 3;
	currentgame.discardCount[1] = 3;
	
	// populate the discard pile for both players with a testable value	
	currentgame.discard[0][0] = curse;
	currentgame.discard[0][1] = curse;
	currentgame.discard[0][2] = estate;// score should be -1(testing negatives as well)
	
	currentgame.discard[1][0] = duchy;
	currentgame.discard[1][1] = province;
	currentgame.discard[1][2] = estate; // score should be 10
	
	int score1 = scoreFor(0, &currentgame);
	int score2 = scoreFor(1, &currentgame);
	if((score1 != -1) || (score2 != 10))
	{
		printf("Test failed! Scores should be -1 and 10\n");
		// exit(0);
	}
	else
	{
		printf("Test passed! Scores should be -1 and 10\n");
	}
	
	// check for the deck pile, so empty the hand and discard
	currentgame.handCount[0] = 0;
	currentgame.handCount[1] = 0; 
	currentgame.discardCount[0] = 0;
	currentgame.discardCount[1] = 0;
	currentgame.deckCount[0] = 3;
	currentgame.deckCount[1] = 3;
	
	// populate the deck pile for both players with a testable value	
	currentgame.deck[0][0] = province;
	currentgame.deck[0][1] = province;
	currentgame.deck[0][2] = gardens; // should supply 0.
	
	currentgame.deck[1][0] = curse;
	currentgame.deck[1][1] = duchy;
	currentgame.deck[1][2] = province;
	
	score1 = scoreFor(0, &currentgame); // score should be 12
	score2 = scoreFor(1, &currentgame); // score should be 8
	
	if((score1 != 12) || (score2 != 8))
	{
		printf("Test failed! Scores should be 12 and 8\n");
		// exit(0);
	}
	else
	{
		printf("Test passed! Scores should be 12 and 8\n");
	}
	
	//check for the hand, so empty out the discard and deck.
	currentgame.deckCount[0] = 0;
	currentgame.deckCount[1] = 0; 
	currentgame.discardCount[0] = 0;
	currentgame.discardCount[1] = 0;
	currentgame.handCount[0] = 3;
	currentgame.handCount[1] = 3;
	
	// populate the hand for both players with a testable value	
	currentgame.hand[0][0] = duchy;
	currentgame.hand[0][1] = estate;
	currentgame.hand[0][2] = estate;
	
	currentgame.hand[1][0] = duchy;
	currentgame.hand[1][1] = curse;
	currentgame.hand[1][2] =province;
	
	score1 = scoreFor(0, &currentgame); // score should be 5
	score2 = scoreFor(1, &currentgame); // score should be 8
	
	if((score1 != 5) || (score2 != 8))
	{
		printf("Test failed! Scores should be 5 and 8\n");
		// exit(0);
	}
	else
	{
		printf("Test passed! Scores should be 5 and 8\n");
	}
	
	return 0;
}