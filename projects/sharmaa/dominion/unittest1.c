/* 
test for 
int isGameOver(struct gameState *state) {
  int i;
  int j;
	
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
    {
      return 1;
    }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)
    {
      if (state->supplyCount[i] == 0)
	{
	  j++;
	}
    }
  if ( j >= 3)
    {
      return 1;
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
	printf("-----CURRENT TEST: isGameOver function-----\n");
	struct gameState currentgame; // create new game and set num players
	int numplayers = 2;
	int x;
	int randomseed = 777;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall}; // set kingdom cards array
	memset(&currentgame, 23, sizeof(struct gameState));
	int gameinit = initializeGame(numplayers, k, randomseed, &currentgame); // initialize the game

	if (isGameOver(&currentgame) == 1) // check if function works when game starts
	{
		printf("Test failed! Game just started and function said it was over.\n");
		exit(0);
	}
	else
	{
		printf("Test passed! Game just started.\n");
	}
	
	currentgame.supplyCount[province] = 0; // Test for when the provinces are all out
	if (isGameOver(&currentgame) == 1) 
	{
		printf("Test passed! All provinces are gone.\n");
	}
	else
	{
		printf("Test failed! Provinces are out but game still ended.\n");
		exit(0);
	}
	
	currentgame.supplyCount[province] = 4; 
	for (x = 0; x < 7;  x++)
    {
      currentgame.supplyCount[x] = 0;
	}
	if (isGameOver(&currentgame) == 0) // check if function works when 3 supplies are empty
	{
		printf("Test failed! 3 supply piles are empty and game is still not over.\n");
		exit(0);
	}
	else
	{
		printf("Test passed! Game is over properly, 3 supply piles are empty.\n");
	}	
	return 0;
}
