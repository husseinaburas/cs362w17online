/*
test for
int shuffle(int player, struct gameState *state) {
 

  int newDeck[MAX_DECK];
  int newDeckPos = 0;
  int card;
  int i;

  if (state.deckCount[player] < 1)
    return -1;
  qsort ((void*)(state.deck[player]), state.deckCount[player], sizeof(int), compare); 
  /* SORT CARDS IN DECK TO ENSURE DETERMINISM! 

  while (state.deckCount[player] > 0) {
    card = floor(Random() * state.deckCount[player]);
    newDeck[newDeckPos] = state.deck[player][card];
    newDeckPos++;
    for (i = card; i < state.deckCount[player]-1; i++) {
      state.deck[player][i] = state.deck[player][i+1];
    }
    state.deckCount[player]--;
  }
  for (i = 0; i < newDeckPos; i++) {
    state.deck[player][i] = newDeck[i];
    state.deckCount[player]++;
  }

  return 0;
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
	printf("-----CURRENT TEST: Shuffle function-----\n");
	struct gameState currentgame; // create new game and set num players
	int numplayers = 2;
	int x, i, r, test, inc1, inc2;
	int old1[20];
	int old2[20];
	int randomseed = 477;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall}; // set kingdom cards array
	int gameinit = initializeGame(numplayers, k, randomseed, &currentgame); // initialize the game
	
	currentgame.deckCount[0] = 20; // create a deck for each player of size 20 (hard-coded in)
	currentgame.deckCount[1] = 20; 
	
	for (x = 0; x < 20; x++)
	{
		for(i = 0; i < 2; i++)
		{
			if (i == 0)
			{
				currentgame.deck[i][x] = x; // populate both decks with different cards (staggerd by 3)
				old1[x] = currentgame.deck[i][x];
			}
			else
			{
				currentgame.deck[i][x] = x + 3;
				old2[x] = currentgame.deck[i][x];
			}
		}
	}
	// shuffle the cards and check to make sure we have the same cards, as well as the right number.
	// This is the definition of a shuffled deck, as long as cards are in different order (chance of all 20 cards being in same order is very minimal)
	
	shuffle(0, &currentgame);	
	shuffle(1, &currentgame);
	int new1[20];
	int new2[20];
	if ((currentgame.deckCount[0] != 20) || (currentgame.deckCount[1] != 20))
	{
		printf("Test failed! There are now a different number of cards.\n");
	}
	for (x = 0; x < 20; x++)
	{
		for(i = 0; i < 1; i++)
		{
			if (i == 0)  // we are in the first deck, check if there are 20 cards, and are the first 20 we set prior
			{
				test = currentgame.deck[i][x];
				new1[x] = test;
				if ((test >= 0) && (test <= 20)) // make sure the value is between 1 and 20
				{
					continue;
				}
				else
				{
					printf("Test failed! The cards are different!%d\n", x);
					exit(0);
				}
			}
			else  // we are in second deck, check if there are 20 cards, numbers 3 through 23
			{
				test = currentgame.deck[i][x];
				new2[x] = test;
				if ((test >= 3) && (test <= 23)) // make sure the value is between 3 and 23
				{
					continue;
				}
				else
				{
					printf("Test failed! The cards are different!\n");
					exit(0);
				}
			}
		}
	}
	printf("Test passed! The cards are the same and have the same number of cards.\n");
	for(x = 0; x <20; x++)
	{
		if(old1[x] == new1[x])
		{
			inc1++;
		}
		if(old2[x] == new2[x])
		{
			inc2++;
		}
	}
	
	if ((inc1 == 20) || (inc2 == 20))
	{
		printf("Test failed! Cards are in the same order\n");
	}
	else
	{
		printf("Test passed! Cards are in a different order\n");
	}
	return 0;
}
	
	
	