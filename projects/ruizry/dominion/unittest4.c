/*
unittest4.c Testing updateCoins Function
*/
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

void assertTrue(int predicate, char *message)
{
	printf("%s: ", message);
	if(predicate)
		printf("PASSED\n");
	else
		printf("FAILED\n");
}

int main (int argc, char** argv) {
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           council_room, tribute, smithy};


  printf ("Starting updateCoins Units Tests...\n\n");


  initializeGame(4, k, 5, &G);

  int i=0;

    G.hand[i][0] = estate;
    G.hand[i][1] = estate;
    G.hand[i][2] = estate;
    G.hand[i][3] = estate;
    G.hand[i][4] = estate;

    updateCoins(i, &G, 0);
    assertTrue(G.coins == 0, "Testing if 0 Treasure cards are Calculated Correctly");

    G.hand[i][0] = copper;
    G.hand[i][1] = copper;
    G.hand[i][2] = copper;
    G.hand[i][3] = copper;
    G.hand[i][4] = copper;

    updateCoins(i, &G, 0);
    assertTrue(G.coins == 5, "Testing if 5 Coppers Counted Correctly");

    updateCoins(i, &G, 5);
    assertTrue(G.coins == 10, "Testing if 5 Bonus is added");

    updateCoins(i, &G, -5);
    assertTrue(G.coins == 0, "Testing results if negative 5 Bonus is applied");


  printf ("\nupdateCoins Unit Tests Complete\n\n");

  return 0;

}
