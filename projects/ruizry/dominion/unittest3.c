/*
unittest3.c Testing gainCard Function
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


  printf ("Starting gainCard Units Tests...\n\n");

  printf ("\nTesting for gainCard Being Used by Consecutive Players\n\n");

  initializeGame(4, k, 5, &G);

  int i=0;
  int j=0;
  int supplyCounter = 10;

  for(i = 0; i < 4; i++) {

    printf("Player %d\n", i);
    gainCard(smithy, &G, 1, i);
    supplyCounter = supplyCounter - 1;
    assertTrue(supplyCount(smithy, &G) == supplyCounter, "Testing Gain Action on Smithy pile");

    discardCard(j, i, &G, 0);
    discardCard(j, i, &G, 0);
    discardCard(j, i, &G, 0);
    discardCard(j, i, &G, 0);
    discardCard(j, i, &G, 0);

    gainCard(smithy, &G, 1, i);
    supplyCounter = supplyCounter - 1;
    assertTrue(supplyCount(smithy, &G) == supplyCounter, "Testing Smithy Pile after Gain used with Empty Hand ");

    endTurn(&G);
    printf("\n");
  }

  gainCard(smithy, &G, 1, i);
  gainCard(smithy, &G, 1, i);
  assertTrue(supplyCount(smithy, &G) == 0, "Testing Smithy Pile after using Gain on last Card in Pile ");

  printf ("\ngainCard Unit Tests Complete\n\n");

  return 0;

}
