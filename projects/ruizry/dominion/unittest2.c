/*
unittest2.c Testing discardCard Function
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


  printf ("Starting discardCard Units Tests...\n\n");

  printf ("\nTesting for discardCard Being Used by Consecutive Players\n\n");

  initializeGame(4, k, 5, &G);

  int i=0;
  int j=0;

  for(i = 0; i < 4; i++) {

    printf("Player %d\n", i);
    discardCard(j, i, &G, 0);
    assertTrue(G.handCount[i] == 4, "Testing Single Discard Action");

    discardCard(j, i, &G, 0);
    discardCard(j, i, &G, 0);
    discardCard(j, i, &G, 0);
    assertTrue(G.handCount[i] == 1, "Testing Discard until 1 card left");

    discardCard(j, i, &G, 0);
    assertTrue(G.handCount[i] == 0, "Testing Discard until no cards left");

    endTurn(&G);
    printf("\n");
  }

  printf ("\ndiscardCard Unit Tests Complete\n\n");

  return 0;

}
