/* 
 *
 * unittest2.c isGameOver()
 * 
 */

  
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "isGameOver"

void cus_assert(int test)
{
	if (test == 0) {
		printf ("Test Failed");
	}
	return;
}

int main() {
	int num;
	int state;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int turn = 0;

// initialize a game state 
	initializeGame(numPlayers, k, seed, &G);
	

	printf("------------------------- Testing Unit: %s -----------------------\n", TESTCARD);
	

// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
		
	//Testing game over at initialization
	cus_assert(isGameOver(&G) == 0);
	//Test one supply slot empty , game should not end
	G.supplyCount[gold] = 10;
	G.supplyCount[mine] = 0;
	G.supplyCount[adventurer] = 2;
	cus_assert(isGameOver(&G) == 0);
	//Test two supply slot empty , game should not end
	G.supplyCount[gold] = 10;
	G.supplyCount[mine] = 0;
	G.supplyCount[adventurer] = 0;
	cus_assert(isGameOver(&G) == 0);
	//Test three supply slot empty , game should end
	G.supplyCount[gold] = 0;
	G.supplyCount[mine] = 0;
	G.supplyCount[adventurer] = 0;
	cus_assert(isGameOver(&G) == 1);
	//Test if providence cart stack is empty and check if game is over
	G.supplyCount[province] = 0;
	cus_assert(isGameOver(&G) == 1);
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);



	return 0;
	
	/*
	
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
}