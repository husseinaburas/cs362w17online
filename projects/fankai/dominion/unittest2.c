/*test function int updateCoins(int player, struct gameState *state, int bonus)
{
  int i;

  //reset coin count
  state->coins = 0;

  //add coins for each Treasure card in player's hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == copper)
	{
	  state->coins += 1;
	}
      else if (state->hand[player][i] == silver)
	{
	  state->coins += 2;
	}
      else if (state->hand[player][i] == gold)
	{
	  state->coins += 3;
	}
    }

  //add bonus
  state->coins += bonus;

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
    int i;
    struct gameState G;
    int seed = 1000;
    int numPlayers =1;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    printf ("-----------------TESTING  updateCoins():-----------------\n");
	updateCoins(1, &G, 0);
	assert(G.coins == 0);
	G.handCount[0]=10;
    printf("Test add 10 copper  one by one to player hand\n");
	for (i = 1; i <= G.handCount[0]; i++)
	{
		G.hand[0][i-1] = copper;
        updateCoins(0, &G, 0);
        printf("current coins = %d, expected = %d\n",G.coins,i);
	}
    printf("Test remove copper one by one out of player hand\n");
	for (i = 1; i <= G.handCount[0]; i++)
	{
		G.hand[0][i-1] = ' ';
        updateCoins(0, &G, 0);
        printf("current coins = %d, expected = %d\n",G.coins,10-i);
	}
    printf("Test add 10 silver  one by one to player hand\n");
	for (i = 1; i <= G.handCount[0]; i++)
	{
		G.hand[0][i-1] = silver;
        updateCoins(0, &G, 0);
        printf("current coins = %d, expected = %d\n",G.coins,2*i);
	}
    printf("Test remove silver one by one out of player hand\n");
	for (i = 1; i <= G.handCount[0]; i++)
	{
		G.hand[0][i-1] = ' ';
        updateCoins(0, &G, 0);
        printf("current coins = %d, expected = %d\n",G.coins,20-2*i);
	}
    printf("Test add 10 gold  one by one to player hand\n");
	for (i = 1; i <= G.handCount[0]; i++)
	{
		G.hand[0][i-1] = gold;
        updateCoins(0, &G, 0);
        printf("current coins = %d, expected = %d\n",G.coins,3*i);
	}
    printf("Test add 10 bonus\n");
    updateCoins(0, &G, 10);
    printf("current coins = %d, expected = %d\n",G.coins,30+10);
    printf("Test remove all the treasures out of player hand\n");
	for (i = 1; i <= G.handCount[0]; i++)
	{
		G.hand[0][i-1] = ' ';
	}
    updateCoins(0, &G, 0);
    printf("current coins = %d, expected = %d\n",G.coins,0);
    printf ("-----------------TESTING  updateCoins(): END-----------------\n");
}
