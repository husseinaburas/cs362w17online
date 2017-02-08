/*test function int isGameOver(struct gameState *state) {
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
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
int main() {
    struct gameState G;
    int seed = 1000;
    int numPlayers = 2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    printf ("-----------------TESTING isGameOver():-----------------\n");
    printf ("TESTING supplyCount[province] = 0\n");
    G.supplyCount[province] = 0;
    if(isGameOver(&G) == 1)
        printf("Passed,game should be over\n");
    else
        printf("Failed,game is not over\n");
    printf ("TESTING refill the province \n");
    G.supplyCount[province] = 1;
    if(isGameOver(&G) == 1)
        printf("Failed,game is over\n");
    else
        printf("Passed,game should be not over\n");

    printf ("TESTING three supply pile are 0, the game ends\n");
    G.supplyCount[adventurer] = 0;
    G.supplyCount[embargo] = 0;
    G.supplyCount[village] = 0;
    if(isGameOver(&G) == 1)
        printf("Passed,game should be over\n");
    else
        printf("Failed,game is not over\n");
    printf ("TESTING refill one of the pile\n");
    G.supplyCount[village] = 1;
    if(isGameOver(&G) == 1)
        printf("Failed,game is over\n");
    else
        printf("Passed,game should be not over\n");
    printf ("-----------------TESTING isGameOver(): END-----------------\n");
}
