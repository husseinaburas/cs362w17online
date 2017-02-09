/*
test for
int fullDeckCount(int player, int card, struct currentgame *state) {
  int i;
  int count = 0;

  for (i = 0; i < state.deckCount[player]; i++)
    {
      if (state.deck[player][i] == card) count++;
    }

  for (i = 0; i < state.handCount[player]; i++)
    {
      if (state.hand[player][i] == card) count++;
    }

  for (i = 0; i < state.discardCount[player]; i++)
    {
      if (state.discard[player][i] == card) count++;
    }

  return count;
}
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	printf("-----CURRENT TEST: fullDeckCount function-----\n");
	struct gameState currentgame; // create new game and set num players
	int numplayers = 2;
	int testcard = 9;
	int ret, x;
	int randomseed = 477;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall}; // set kingdom cards array
	int gameinit = initializeGame(numplayers, k, randomseed, &currentgame); // initialize the game
	
	// To test this function, we will create a situation where the deck is empty, the deck has/doesnt have
	// the card. The same tests follow for the hand and discard pile
	
	// At this point the players should just have the 7 coppers and 3 estates
	
	ret = fullDeckCount(x, testcard, &currentgame); // there should be 0
	if (ret != 0)
	{
		printf("Test failed! There should not be any of test card");
	}
	else
	{
		printf("Test passed! There is none of the testcard\n");
	}
	
	
	//Put the card into the deck (twice for each player) and not the other 2
	for(x = 0; x < 2; x++)
	{
		currentgame.deck[x][2] = testcard;
		currentgame.deck[x][3] = testcard; // 2 of the card in deck
		currentgame.handCount[x] = 0;
		currentgame.discardCount[x] = 0;
		ret = fullDeckCount(x, testcard, &currentgame);
		if (ret != 2)
		{
			printf("Test failed! Function (deck) did not count 2 cards.\n");
			exit(0);
		}
		else
		{
			printf("Test passed! Function (deck) did count 2 cards for player %d.\n" , x);
		}
	}
	
	for(x = 0; x < 2; x++)
	{
		currentgame.hand[x][0] = testcard;
		currentgame.hand[x][1] = testcard; // 2 of the card in hand
		currentgame.handCount[x] += 2;
		currentgame.deckCount[x] = 0;
		currentgame.discardCount[x] = 0;
		ret = fullDeckCount(x, testcard, &currentgame);
		if (ret != 2)
		{
			printf("Test failed! Function (hand) did not count 2 cards.\n");
			exit(0);
		}
		else
		{
			printf("Test passed! Function (hand) did count 2 cards for player %d.\n" , x);
		}
	}
	
	for(x = 0; x < 2; x++)
	{
		currentgame.discard[x][0] = testcard;
		currentgame.discard[x][1] = testcard; // 2 of the card in deck
		currentgame.discardCount[x] += 2;// update because there wasnt anything before
		currentgame.handCount[x] = 0;
		currentgame.deckCount[x] = 0;
		ret = fullDeckCount(x, testcard, &currentgame);
		if (ret != 2)
		{
			printf("Test failed! Function (discard) did not count 2 cards.\n");
			exit(0);
		}
		else
		{
			printf("Test passed! Function (discard) did count 2 cards for player %d.\n" , x);
		}
	}
	return 0;
}
	
